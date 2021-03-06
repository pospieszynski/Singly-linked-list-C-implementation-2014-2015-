#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TEXT 20
#define ESC 27
#define ENTER 13
#define EXIT 10
#define CONTINUE 50

typedef struct node
{
    char *str;
    struct node *next;
} node;

node* init(node **coppied);
node* copy(node *src);
node* chooseHead(node *original, node *coppied);
node** chooseHeadRef(node **original, node **coppied);
bool push(node **head_ref);
bool append(node **head_ref);
char* pop(node **head_ref);
int memoryAllocationProblems(void);
int length(node *head);
void display(node *head);
void destroy(node **head_ref);
void sort(node *head);
void swapNode(node *head);
void reverse(node **head_ref);
void showParameters(node *original, node *coppied);
void viewMenu();

int main()
{
    unsigned int decision = 0;
    node *list = NULL;
    node *coppied = NULL;
    char *popped = NULL;
    int control = 0;


   while(decision != EXIT)
    {
	viewMenu();   
	do 
	{
		control = scanf("%u", &decision);
		 while(getchar() != '\n' );
	}
	while(control != 1 );
        
	switch(decision)
        {
        case 0:
            if(!list){
		  if(!(list = init(&coppied)))
		  {
		      decision = memoryAllocationProblems();
		  }
	    }  
	    else printf("The list has already been initialized.");  
            break;

        case 1:
	   if(list != NULL || coppied != NULL)
	   {
		if( push(chooseHeadRef(&list, &coppied)) )
		{
			destroy(&list);
			destroy(&coppied);
			decision = memoryAllocationProblems();
		}
	   }
	   break;

        case 2:
	if(list != NULL || coppied != NULL)
	{
       if( append(chooseHeadRef(&list, &coppied)) )
	   {
	      destroy(&list);
	      destroy(&coppied);
	      decision = memoryAllocationProblems();
	   }
	} 
            break;
        
	case 3:
	if(list != NULL || coppied != NULL)
	{
            if ( (popped = pop(chooseHeadRef(&list, &coppied))) )
	    {
		    printf("\n%s", popped);
		    free(popped);
	    }
	    else
	    {
			destroy(&coppied); destroy(&list);	
			decision = memoryAllocationProblems();	    
	    }

	}
	   break;
        
	case 4:
	  if(list != NULL || coppied != NULL)
            printf("\n %d", length(chooseHead(list, coppied)));
            break;
        case 5:
	  if(list != NULL || coppied != NULL)
            display(chooseHead(list, coppied));
            break;
        case 6:
            if(!coppied && list != NULL)
	    {
	      if( ! (coppied = copy(list) ) )
		decision = memoryAllocationProblems();
	    }
	    break;
        case 7:
	  if(list != NULL || coppied != NULL)
            sort(chooseHead(list, coppied));
            break;
        case 8:
	  if(list != NULL || coppied != NULL)
            reverse(chooseHeadRef(&list, &coppied));
            break;
        case 9:
	  if(list != NULL || coppied != NULL)
            destroy(chooseHeadRef(&list, &coppied));
            break;
        case 10:
            break;
        default:
            printf("\nImproper data! Type suitable character(from 1 to 7) and press enter.");
            break;
        };
    }

    destroy(&list);
    destroy(&coppied);
    printf("\n\n");
    return 0;
}

node *init(node** coppied)
{
    node* head = NULL;
    head = malloc(sizeof(node));
    
    if(!head)
    {
      destroy(coppied);
      return NULL;
    }
    
    head->str = malloc(MAX_TEXT * sizeof(char));
    
    if(!head->str)
    {
      destroy(coppied);
      free(head);
      return NULL;
    }
    
    strcpy(head->str, "setup_string");
    head->next = NULL;
    return head;
}

bool push(node **head_ref)
{
    node* new = malloc(sizeof(node));
    if(!new) return true;
    if( !( new->str = malloc(MAX_TEXT * sizeof(char))) ) return true;
    printf("Enter string: ");
    scanf("%19s", new->str);
    new->next = *head_ref;
    *head_ref = new;
    return false;
}

bool append(node** head_ref)
{
    node *current = *head_ref;
    while(current->next != NULL)
    {
        current=current->next;
    }
    if( !(current->next = malloc(sizeof(node)))) return true;
    if( !(current->next->str = malloc(sizeof(char) * MAX_TEXT)) ) return true;
    printf("String: ");
    scanf("%19s", current->next->str );
    current->next->next = NULL;
    return false;
}

char *pop(node** head_ref)
{
    node *current = *head_ref;
    node *new_tail = NULL;
    char* popped = NULL;
    
    if(current->next == NULL)
    {
      popped = malloc(MAX_TEXT * sizeof(char));
      strcpy(popped, current->str);
      free(current->str);
      free(current);
      *head_ref = NULL;
      return popped;
    }
    
    else{
      while(current->next != NULL)
      {
	  if (current->next->next == NULL) new_tail = current;
	  current = current->next;
      }
      popped = malloc(MAX_TEXT * sizeof(char));
      strcpy(popped, current->str);
      free(current->str);
      free(current);
      new_tail->next = NULL;
      return popped;
    }
 }

void destroy(node** head_ref)
{
    node *next = NULL;
    node* deleteMe = *head_ref;
    while (deleteMe)
    {
        next = deleteMe->next;
        free(deleteMe->str);
        free(deleteMe);
        deleteMe = next;
    }
    *head_ref = NULL;
}

void swap_node(node *head)
{
    char *temp = head ->str;
    head->str = (head->next)->str;
    (head->next)->str = temp;
}

void sort(node *head)
{
    unsigned int i, j;
    node *current = NULL;

    for (i = length(head); i > 1; --i)
    {
        for (current = head, j = 1; j < i; ++j, current = current->next)
        {
            if (strcmp(current->str, (current->next)->str) > 0)
            {
                swap_node(current);
            }
        }
    }
}

void reverse(node** head_ref)
{
    node* prev   = NULL;
    node* current = *head_ref;
    node* next = NULL;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

node* copy(node *src)
{
    node *head = NULL;
    node **dst = &head;
    while (src)
    {
        *dst = malloc (sizeof(node));
	
	if(!*dst)
	{
	  destroy(dst);
	 return NULL;
	}
	
	(*dst)->str = malloc(MAX_TEXT * sizeof(char));
        
	if( !((*dst)->str) )
	{
	  destroy(dst);
	  return NULL;
	}
	
	strcpy( (*dst)->str, src->str );
        (*dst)->next = NULL;
        src = src->next;
        dst = &((*dst)->next);
    }
    return head;
}

int length(node *head)
{
    int no = 0;
    node *current = head;

    if(current != NULL)
    {
        while(current->next != NULL)
        {
            current = current->next;
            no++;
        }
        no++;
    }
    return no;
}

void display(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf ("%s  ", current->str);
        current = current->next;
    }
}

node* chooseHead(node *original, node*coppied)
{
    unsigned int parameter = 0;
    int control = 0;
    bool error = 0;
    
    showParameters(original, coppied);

        do
        {
	    if(error) printf("\nWrong parameter, try again.");
            printf("\nList parameter: ");
            control = scanf("%u", &parameter);
	    while(getchar() != '\n' );
	    error = 1;
        }
        while(((!(original != NULL && parameter == 1)) && (!(coppied != NULL && parameter == 2))) || control == EOF );

        if(parameter == 1) return original;
        if(parameter == 2) return coppied;
	else return NULL;
  
}

void showParameters(node* original, node* coppied)
{
    printf("\nAvailable list parameters:");
    if(original) printf("\n1 - original list");
    if(coppied) printf("\n2 - coppied list");
}

node** chooseHeadRef(node** original, node** coppied)
{
    unsigned int parameter = 0;
    int control = 0;
    bool error = 0;
    
    showParameters(*original, *coppied);
    
        do
        {
	    if(error) printf("\nWrong parameter, try again.");
	    printf("\nList parameter: ");
	    control =scanf("%u", &parameter);
	    while(getchar() != '\n' );
	    error = 1;
        }
       while( ((!(*original != NULL && parameter == 1)) && (!(*coppied != NULL && parameter == 2))) || control == EOF );

        if(parameter == 1) return original;
        if(parameter == 2) return coppied;
	else return NULL;
}

int memoryAllocationProblems(void)
{
  int decision;
  printf("\nMemory allocation problems, press ENTER to continue or ESC to exit.");
  do
  {
    if(getchar() == ESC) decision = EXIT;
    else if(getchar() == ENTER) decision = CONTINUE;
  }while(decision != CONTINUE && decision != EXIT);
  return decision;
}

void viewMenu()
{
        system("clear");
        fflush(stdin);
        printf("\n\n0. initialize");
        printf("\n\n1. push");
        printf("\n\n2. append");
        printf("\n\n3. pop");
        printf("\n\n4. length");
        printf("\n\n5. display");
        printf("\n\n6. copy");
        printf("\n\n7. sort");
        printf("\n\n8. reverse");
        printf("\n\n9. destroy");
        printf("\n\n10. exit");
        printf("\n\nOperation no: ");

}
