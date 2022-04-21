#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int counts[1000000];
    char characters[1000000];
    if (argc < 2)
    {
        printf("wunzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }
    FILE *stream;
    int index;
    for (int i = 0; i < argc - 1; i++)
    {
        index = 0;
        stream = fopen(argv[i + 1], "r");
        if (!stream)
        {
            printf("wunzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }
        while (fread(counts + index, 1, 4, stream) != 0)
        {
            fread(characters + index, 1, 1, stream);
            index++;
        }
        for (int i = 0; i < index; i++)
        {
            for (int t = 0; t < counts[i]; t++)
            {
                char c = characters[i];
                printf("%c", c);
            }
        }
        fclose(stream);
    }
    exit(EXIT_SUCCESS);
}
