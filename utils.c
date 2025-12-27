#include "./utils.h"
#include "./memory.h"
#include "./log.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

char* make_string(char *args, int number_line)
{
    char *string = NULL;
    char *token;

    static char *saveptr = NULL;
    char *input;

    if (args != NULL) {
        input = strdup(args);
        if (input == NULL) {
            print_error("Memory allocation failed", number_line);
            return NULL;
        }
        token = strtok(input, " ");
    } else {
        token = strtok(NULL, " ");
    }

    if (token == NULL && args != NULL) {
        free(input);
        return NULL;
    }

    while (token != NULL) {
        if (token[0] == '$') {
            int type = exist_variable(token + 1);

            if (type == -1) {
                print_error("variable is not exist.", number_line);
                if (args != NULL) free(input);
                free(string);
                return NULL;
            } else if (type == 0) {
                int int_value = load_int(token + 1);
                char value[20];
                sprintf(value, "%d", int_value);

                if (string == NULL) {
                    string = malloc(strlen(value) + 2);
                    if (string) {
                        strcpy(string, value);
                        strcat(string, " ");
                    }
                } else {
                    size_t new_len = strlen(string) + strlen(value) + 2;
                    char *temp = realloc(string, new_len);
                    if (temp) {
                        string = temp;
                        strcat(string, value);
                        strcat(string, " ");
                    }
                }
            } else if (type == 1) {
                char *value = load_str(token + 1);
                if (value == NULL) {
                    print_error("Failed to load string variable", number_line);
                    if (args != NULL) free(input);
                    free(string);
                    return NULL;
                }

                if (string == NULL) {
                    string = malloc(strlen(value) + 2);
                    if (string) {
                        strcpy(string, value);
                        strcat(string, " ");
                    }
                } else {
                    size_t new_len = strlen(string) + strlen(value) + 2;
                    char *temp = realloc(string, new_len);
                    if (temp) {
                        string = temp;
                        strcat(string, value);
                        strcat(string, " ");
                    }
                }
            }
        } else {
            if (string == NULL) {
                string = malloc(strlen(token) + 2);
                if (string) {
                    strcpy(string, token);
                    strcat(string, " ");
                }
            } else {
                size_t new_len = strlen(string) + strlen(token) + 2;
                char *temp = realloc(string, new_len);
                if (temp) {
                    string = temp;
                    strcat(string, token);
                    strcat(string, " ");
                }
            }
        }

        token = strtok(NULL, " ");
    }

    if (args != NULL) {
        free(input);
    }

    if (string && strlen(string) > 0) {
        size_t len = strlen(string);
        if (string[len-1] == ' ') {
            string[len-1] = '\0';
        }
    }

    return string;
}

int make_int(char *args, int number_line)
{
    int result = 0;
    int current_value;
    char *token;
    int is_first_token = 1;

    if ((token = strtok(args, " ")) != NULL) {
        if (token[0] == '$') {
            int type = exist_variable(token + 1);

            if (type == -1) {
                print_error("variable is not exist.", number_line);
                return 0;
            } else if (type == 0) {
                result = load_int(token + 1);
            } else if (type == 1) {
                char *value_str = load_str(token + 1);
                while (*value_str == ' ') value_str++;

                if (strlen(value_str) > 9) {
                    print_error("Value must be a valid integer",number_line);
                    return 0;
                }

                char *endptr;
                errno = 0;
                result = strtol(value_str, &endptr, 10);

                if (endptr == value_str || *endptr != '\0') {
                    print_error("Value must be a valid integer", number_line);
                    return 0;
                }

                if (errno == ERANGE) {
                    print_error("Number is too large or too small", number_line);
                    return 0;
                }
            }
        } else {
            if (strlen(token) > 9) {
                print_error("Value must be a valid integer",number_line);
                return 0;
            }

            char *endptr;
            errno = 0;
            result = strtol(token, &endptr, 10);

            if (endptr == token || *endptr != '\0') {
                print_error("Value must be a valid integer", number_line);
                return 0;
            }

            if (errno == ERANGE) {
                print_error("Number is too large or too small", number_line);
                return 0;
            }
        }
        is_first_token = 0;
    } else {
        print_error("No value provided", number_line);
        return 0;
    }

    while ((token = strtok(NULL, " ")) != NULL) {
        if (token[0] == '$') {
            int type = exist_variable(token + 1);

            if (type == -1) {
                print_error("variable is not exist.", number_line);
                return result;

            } else if (type == 0) {
                current_value = load_int(token + 1);

            } else if (type == 1) {
                char *value_str = load_str(token + 1);
                while (*value_str == ' ') value_str++;

                if (strlen(value_str) > 9) {
                    print_error("Value must be a valid integer",number_line);
                    return result;
                }

                char *endptr;
                errno = 0;
                current_value = strtol(value_str, &endptr, 10);

                if (endptr == value_str || *endptr != '\0') {
                    print_error("Value must be a valid integer", number_line);
                    return result;
                }

                if (errno == ERANGE) {
                    print_error("Number is too large or too small", number_line);
                    return result;
                }
            }
        } else {
            if (strlen(token) > 9) {
                print_error("Value must be a valid integer",number_line);
                return result;
            }

            char *endptr;
            errno = 0;
            current_value = strtol(token, &endptr, 10);

            if (endptr == token || *endptr != '\0') {
                print_error("Value must be a valid integer", number_line);
                return result;
            }

            if (errno == ERANGE) {
                print_error("Number is too large or too small", number_line);
                return result;
            }
        }

        result = current_value;
    }

    return result;
}
