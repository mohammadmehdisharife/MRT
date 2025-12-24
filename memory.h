#ifndef MEMORY_H
#define MEMORY_H

struct node {
  char *name;

  enum { INT_TYPE, STR_TYPE } type;
  
  union {
    int int_value;
    char str_value[100];
  } data;

  struct node *next;
};

typedef struct node node_t;

extern node_t *head;
extern node_t *tail;

void add_int(int value,char *name, int number_line);
void add_str(char *value,char *name, int number_line);

int exist_variable(char *name);
int load_int(char *name);
char* load_str(char *name);

// just for test
void print_memory();

#endif
