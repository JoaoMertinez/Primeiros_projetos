#include <stdio.h>

// Função para calcular a soma dos 3 maiores números
int MAIOR(int nota1, int nota2, int nota3, int nota4) {
    int notas[4] = {nota1, nota2, nota3, nota4};
    int soma = 0;

    // Ordenar as notas em ordem decrescente
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (notas[i] < notas[j]) {
                int temp = notas[i];
                notas[i] = notas[j];
                notas[j] = temp; 
            }
        }
    }

    // Somar as três maiores notas
    for (int i = 0; i < 3; i++) {
        soma += notas[i];
    }

    return soma;
}

// Função para determinar o conceito com base na nota final
char CONCEITO(int nota_final) {
    if (nota_final >= 90) {
        return 'A';
    } else if (nota_final >= 80) {
        return 'B';
    } else if (nota_final >= 70) {
        return 'C';
    } else if (nota_final >= 60) {
        return 'D';
    } else if (nota_final >= 40) {
        return 'E';
    } else {
        return 'F';
    }
}

int main() {
    int numero_aluno, nota1, nota2, nota3, nota4, nota_final;
    char conceito;

    for (int i = 0; i < 80; i++) {
        // Ler os dados do aluno
        scanf("%d %d %d %d %d %d", &numero_aluno, &nota1, &nota2, &nota3, &nota4, &nota_final);

        // Calcular a nota final
        int nota_final_calculada = MAIOR(nota1, nota2, nota3, nota4) + nota_final;

        // Determinar o conceito
        conceito = CONCEITO(nota_final_calculada);

        // Exibir os resultados
        printf("Aluno %d - Nota Final: %d - Conceito: %c\n", numero_aluno, nota_final_calculada, conceito);
    }

    return 0;
}

