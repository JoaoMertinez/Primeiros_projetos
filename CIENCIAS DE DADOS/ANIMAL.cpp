#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ANIMALS 150
#define MAX_NAME_LENGTH 30

typedef struct {
    char name[MAX_NAME_LENGTH];
    int hair, feathers, eggs, milk, airborne, aquatic, predator, toothed, backbone, breathes, venomous, fins, legs, tail, domestic, catsize, type;
} Animal;

int main() {
    FILE *file = fopen("zoo.txt", "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Animal animals[MAX_ANIMALS];

    int count = 0;

    while (fscanf(file, "%29s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                  animals[count].name, &animals[count].hair, &animals[count].feathers, &animals[count].eggs, &animals[count].milk,
                  &animals[count].airborne, &animals[count].aquatic, &animals[count].predator, &animals[count].toothed, &animals[count].backbone,
                  &animals[count].breathes, &animals[count].venomous, &animals[count].fins, &animals[count].legs, &animals[count].tail,
                  &animals[count].domestic, &animals[count].catsize, &animals[count].type) == 18) {
        count++;
        if (count >= MAX_ANIMALS) {
            printf("Atingido o limite máximo de animais. Ajuste o valor de MAX_ANIMALS.\n");
            break;
        }
    }

    fclose(file);

    // Exemplo: Imprimir informações sobre o primeiro animal
    printf("Nome: %s\n", animals[0].name);
    printf("Tipo: %d\n", animals[0].type);

    return 0;
}
