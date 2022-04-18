#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    char buf[512];
    if (argc < 2) {
        exit(0);
    }
    for (int i = 0; i < argc - 1; i++) {
        FILE *fp = fopen(argv[1 + i], "r");
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        while (fgets(buf, 512, fp) != NULL) {
            printf("%s", buf);
        }
        fclose(fp);
    }
    exit(0);

}