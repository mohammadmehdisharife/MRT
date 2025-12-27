#include "./memory.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./log.h"

node_t *head = NULL;
node_t *tail = NULL;

int exist_variable(char *name)
{
    node_t *temp = head;
    int type = -1; // int = 0, str = 1, not_exist = -1
    while(temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (temp->type == INT_TYPE) {
                return 0;
            } else if (temp->type == STR_TYPE) {
                return 1;
            }
        }
        temp = temp->next;
    }
    return -1;
}

int load_int(char *name)
{
    node_t *temp = head;
    int value;
    while(temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            value = temp->data.int_value;
        }
        temp = temp->next;
    }
    return value;
}

char* load_str(char *name)
{
    node_t *temp = head;
    char *value;
    while(temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            value = temp->data.str_value;
        }
        temp = temp->next;
    }
    return value;
}


void add_int(int value, char *name, int number_line)
{
    if (exist_variable(name) != -1) {
        print_error("variable befor is exist.", number_line);
        exit(1);
    }
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

void add_str(char *value, char *name, int number_line)
{
    if (exist_variable(name) != -1) {
        print_error("variable befor is exist.", number_line);
        exit(1);
    }
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
void print_tail()
{
    printf("tail_name: %s\n", tail->name);
}

void print_head()
{
    printf("head->name: %s\n", head->name);
}

void print_memory()
{
    node_t *temp = head;
    while (temp != NULL) {
        if (temp->type == INT_TYPE) {
            printf("name: %s | value: %d | type: INT_TYPE\n", temp->name, temp->data.int_value);
        } else if (temp->type == STR_TYPE) {
            printf("name: %s | value: %s | type: STR_TYPE\n", temp->name, temp->data.str_value);
        }
        temp = temp->next;
    }
    print_head();
    print_tail();
}
