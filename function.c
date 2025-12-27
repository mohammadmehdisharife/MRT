#include "./function.h"
#include "./memory.h"
#include "./log.h"
#include "./utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>


void print_function(char *args, int number_line)
{
    char *print_cmd = strtok(args, " ");
    if (print_cmd == NULL) return;

    char *message = make_string(NULL, number_line);
    if (message) {
        printf("%s\n", message);
        free(message);
    }
}

void shell_function(char *args, int number_line)
{
    char *shell_cmd = strtok(args, " ");
    if (shell_cmd == NULL) return;

    char *command = make_string(NULL, number_line);
    if (command) {
        system(command);
        free(command);
    }
}

void str_function(char *args, int number_line)
{
    char *name;
    char *value_str;

    char *str_cmd = strtok(args, " ");
    if (str_cmd == NULL) return;

    name = strtok(NULL, " ");
    value_str = strtok(NULL, "");

    if (name == NULL || value_str == NULL) {
        print_error("STR: Invalid syntax. Use: STR <name> <value>", number_line);
        return;
    }

    char *clean_value = value_str;
    if (value_str[0] == '"' || value_str[0] == '\'') {
        clean_value = value_str + 1;
        int len = strlen(clean_value);
        if (len > 0 && (clean_value[len-1] == '"' || clean_value[len-1] == '\'')) {
            clean_value[len-1] = '\0';
        }
    }

    char *string_value = make_string(clean_value, number_line);
    if (string_value) {
        add_str(string_value, name, number_line);
        free(string_value);
    }
}

void int_function(char *args, int number_line)
{
    char *name;
    char *value_str;
    int value;

    char *int_cmd = strtok(args, " ");
    if (int_cmd == NULL) return;

    name = strtok(NULL, " ");
    if (name == NULL) {
        print_error("INT: Variable name is required", number_line);
        return;
    }

    if (name[0] == '$') {
        print_error("INT: Variable name cannot start with '$'", number_line);
        return;
    }

    value_str = strtok(NULL, "");
    if (value_str == NULL) {
        print_error("INT: Value is required", number_line);
        return;
    }

    char *value_copy = strdup(value_str);
    if (value_copy == NULL) {
        print_error("INT: Memory allocation failed", number_line);
        return;
    }

    value = make_int(value_copy, number_line);
    add_int(value, name, number_line);
    free(value_copy);
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
        print_error("Unknown function.",number_line);
        exit(1);
    }
}
