#include <stdlib.h>
#include <stdio.h>

void compactar(char *nom_file) {
    FILE *file = fopen(nom_file, "r+");
    // Archivo no existe
    if (file == NULL) {
        perror(nom_file);
        exit(1);
    }
    int i = 0, j = 0;
    char *L = malloc(20 + 1);
    while (fread(L, 20, sizeof(char), file) == 1) {
        fseek(file, i * 20, SEEK_SET);
        fread(L, 20, sizeof(char), file);
        fseek(file, i * 20, SEEK_SET);
        L[20] = 0;
        if (getc(file) != ' ') {
            fseek(file, j * 20, SEEK_SET);
            fwrite(L, 20, sizeof(char), file);
            j++;
        }
        i++;
        fseek(file, i * 20, SEEK_SET);
    }
    fseek(file, j * 20, SEEK_SET);
    fread(L, 20, sizeof(char), file);
    while (j < i - 1) {
        fwrite(L, 20, sizeof(char), file);
        j++;
    }
    free(L);
    fclose(file);
}

int main(int argc, char *argv[]) {
    compactar(argv[1]);
    return 0;
}