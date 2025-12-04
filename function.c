#include "./function.h"
#include "./memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* make_string(char *args, int number_line)
{
    char *string = NULL;
    char *token;
    while ((token = strtok(NULL, " ")) != NULL) {

        if (token[0] == '$') {
            int type = exist_variable(token + 1);

            if (type == -1) {
                printf("ERROR");
                exit(1);
            } else if (type == 0) {
                int int_value = load_int(token + 1);
                char value[20];
                sprintf(value, "%d", int_value);
                if (string == NULL) {
                    string = realloc(string, strlen(value) + 1);
                    strcpy(string, value);
                    strcat(string, " ");
                } else {
                    string = realloc(string, strlen(value) + 1);
                    strcat(string, value);
                    strcat(string, " ");
                }
            } else if (type == 1) {
                char *value = load_str(token + 1);
                if (string == NULL) {
                    string = realloc(string, strlen(value) + 1);
                    strcpy(string, value);
                    strcat(string, " ");
                } else {
                    string = realloc(string, strlen(value) + 1);
                    strcat(string, value);
                    strcat(string, " ");
                }
            }
        }

        else {
            if (string == NULL) {
                string = realloc(string, strlen(token) + 1);
                strcpy(string, token);
                strcat(string, " ");
            } else {
                string = realloc(string, strlen(string) + strlen(token) + 1);
                strcat(string, token);
                strcat(string, " ");
            }
        }

    }
    return string;
}

void print_function(char *args, int number_line)
{
    strtok(args, " ");
    printf("%s\n",make_string(args,number_line));
}

void shell_function(char *args, int number_line)
{
    char *space = strchr(args, ' ');
    char *command = make_string(space++, number_line);
    system(command);
}

void int_function(char *args, int number_line)
{
    char *name;
    int value;
    strtok(args, " ");
    name = strtok(NULL, " ");
    value = atoi(strtok(NULL, " "));
    add_int(value, name);
    // print_memory();
}

void str_function(char *args, int number_line)
{
    char *name;
    char *value;

    strtok(args, " ");
    name = strtok(NULL, " ");
    value = strtok(NULL, "");

    if (name == NULL || value == NULL) {
        printf("Error: Invalid syntax at line %d\n", number_line);
        return;
    }

    add_str(value, name);
    // print_memory();
}

void execute_command(char *function, char *args, int number_line)
{
    if (strcmp(function, "PRINT") == 0) {
        print_function(args, number_line);
    } else if (strcmp(function, "SHELL") == 0) {
        shell_function(args, number_line);
    } else if (strcmp(function, "INT") == 0) {
        int_function(args, number_line);
    } else if (strcmp(function, "STR") == 0) {
        str_function(args, number_line);
    } else {
        printf("\"%s\" is no a function | line <%d>\n", function, number_line);
        exit(1);
    }
}
