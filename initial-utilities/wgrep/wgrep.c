#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(char *term, char *source)
{
    char dest[strlen(term) + 1];
    for (int i = 0; i < (strlen(source) - strlen(term)); i++)
    {
        strncpy(dest, source + i, strlen(term));
        dest[strlen(term)] = '\0';
        if (strcmp(term, dest) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char buf[512];
    if (argc == 1)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(EXIT_FAILURE);
    }
    if (argc == 2)
    {
        while (fgets(buf, 512, stdin) != NULL)
        {
            if (search(argv[1], buf) == 0)
            {
                printf("%s", buf);
            }
        }
        fclose(stdin);
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < argc - 2; i++)
    {
        stream = fopen(argv[i + 2], "r");
        if (stream == NULL)
        {
            printf("wgrep: cannot open file\n");
            exit(EXIT_FAILURE);
        }
        while ((nread = getline(&line, &len, stream)) != -1)
        {
            if ((nread - 1) < strlen(argv[1])) {
               continue;
            }
            if (search(argv[1], line) == 0)
            {
                printf("%s", line);
            }
        }
        free(line);
        fclose(stream);
    }
    exit(EXIT_SUCCESS);
}