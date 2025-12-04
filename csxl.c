#include "./function.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usign: %s <filename>\n", argv[0]);
        return 0;
    }

    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "%s opening failed.\n", argv[1]);
    }

    char buffer[1024];
    char args[1024];
    char *function;
    int number_line = 1;

    while (fgets(buffer, sizeof(buffer), file)) {

        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(args, buffer);
        function = strtok(buffer, " ");

        if (function == NULL) {
            number_line++;
            continue;
        }
        if (strcmp(function, "#") == 0) {
            number_line++;
            continue;
        }

        /*
        printf("DEBUG: buffer='%s'\n", buffer);
        printf("DEBUG: args='%s'\n", args);
        printf("DEBUG: function='%s'\n", function);
        */

        execute_command(function, args, number_line);

        number_line++;
    }
    return 0;
}
