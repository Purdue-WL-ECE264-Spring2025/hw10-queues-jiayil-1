#include "linked_list.h"

#include <stdlib.h>

struct list_node* new_node(size_t value) 
{ 
  struct list_node* newNode = malloc(sizeof(*newNode));
  newNode -> value = value;
  newNode -> next = NULL;
  return newNode;
}


void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node* new_head = new_node(value);
  if(list -> head != NULL)
  {
    new_head -> next = list -> head;
    list -> head = new_head;
  }
  else
  {
    list -> head = new_head;
  }
  return;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  // Create node to be inserted at tail
  struct list_node* new_tail = new_node(value);
  
  // find tail of list
  struct list_node* curr = list -> head;

  if(curr == NULL)
  {
    list -> head = new_tail;
  }
  else
  {
    while(curr -> next != NULL)
    {
      curr = curr -> next;
    }

    // curr is now pointing to tail node
    curr -> next = new_tail;
  }
  
}

size_t remove_from_head(struct linked_list *list) 
{ 
  struct list_node* old_head = list -> head;
  size_t old_head_value = old_head -> value;
  list -> head = list -> head -> next;
  free(old_head);
  return old_head_value;
}

size_t remove_from_tail(struct linked_list *list) 
{ 
  // Find tail of list
  struct list_node* curr = list -> head;
  while(curr -> next -> next != NULL)
  {
    curr = curr -> next;
  } 
  // curr now points to node before tail node
  struct list_node* old_tail = curr -> next;
  size_t old_tail_value = old_tail -> value;
  curr -> next = NULL;
  free(old_tail);
  return old_tail_value;
}

void free_list(struct linked_list list) 
{
  //need to free each node pointer 
  //first free tail, work backwards
  struct list_node* curr = list.head;
  
  while(list.head != NULL && list.head -> next != NULL)
  {
    curr = list.head;
    while(curr -> next != NULL && curr -> next -> next != NULL)
    {
      curr = curr -> next;
    }
    free(curr -> next);
    curr-> next = NULL;
  }

  free(list.head);
}


// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
