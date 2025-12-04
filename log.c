#include "./log.h"
#include <stdio.h>
#include <stdlib.h>

void print_error(char *msg, int number_line)
{
    printf("Line <%d> | %s\n",msg,number_line);
    exit(1);
}
