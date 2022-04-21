#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int counts[100000000];
char characters[100000000];
int m = 0;

void compress(char *line)
{
    int count;
    for (int i = 0; i < strlen(line); i += count)
    {
        count = 0;
        int j = i;
        char c = line[i];
        while (c == line[j])
        {
            count++;
            j++;
        }
        if (m > 0 && c == characters[m - 1])
        {
            counts[m - 1] += count;
        }
        else
        {
            counts[m] = count;
            characters[m] = c;
            m++;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    for (int i = 0; i < argc - 1; i++)
    {
        stream = fopen(argv[i + 1], "r");
        if (stream == NULL)
        {
            printf("wzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }
        while ((nread = getline(&line, &len, stream)) != -1)
        {
            compress(line);
        }
        free(line);
        fclose(stream);
    }
    for (int i = 0; i < m; i++)
    {
        fwrite(counts + i, 4, 1, stdout);
        fwrite(characters + i, 1, 1, stdout);
    }
    exit(EXIT_SUCCESS);
}