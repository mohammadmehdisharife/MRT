#include "./memory.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node_t *head = NULL;
node_t *tail = NULL;

void add_int(int value, char *name) {
  if (head == NULL) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    head = temp;           
    tail = temp;            
    temp->type = INT_TYPE;  
    temp->data.int_value = value;
    temp->next = NULL;
    temp->name = strdup(name);
  } else {
    node_t *temp = (node_t*)malloc(sizeof(node_t));  
    tail->next = temp;     
    tail = temp;            
    temp->type = INT_TYPE;  
    temp->data.int_value = value;
    temp->next = NULL;
    temp->name = strdup(name);
  }
}

void add_str(char *value, char *name) {
  if (head == NULL) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    head = temp;          
    tail = temp;            
    temp->type = STR_TYPE;  
    strcpy(temp->data.str_value, value); 
    temp->next = NULL;
    temp->name = strdup(name);
  } else {
    node_t *temp = (node_t*)malloc(sizeof(node_t));  
    tail->next = temp;      
    tail = temp;           
    temp->type = STR_TYPE;  
    strcpy(temp->data.str_value, value);  
    temp->next = NULL;
    temp->name = strdup(name);
  }
}

// just for test
void print_tail() {
  printf("tail_name: %s\n", tail->name);
}

void print_head() {
  printf("head->name: %s\n", head->name);
}

void print_memory() {
  node_t *temp = head;
  while (temp != NULL) {
    if (temp->type == INT_TYPE) {
      printf("name: %s | value: %d | type: INT_TYPE\n", temp->name, temp->data.int_value);
    } else if (temp->type == STR_TYPE) {
      printf("name: %s | value: %s | type: STR_TYPE\n", temp->name, temp->data.str_value);
    }
    print_head();
    print_tail();
    temp = temp->next;
  }
  printf("------------------------------------------\n");
}
