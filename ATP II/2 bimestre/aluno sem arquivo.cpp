#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_DISCIPLINAS 100
#define MAX_NOTAS 100

struct Aluno {
    int ra;
    char nome[50];
};

struct Disciplina {
    int codigo;
    char nome[50];
};

struct Boletim {
    int ra;
    char nome[50];
    float nota;
};

void cadastrarAluno(struct Aluno alunos[], int *numAlunos, int ra, char nome[]) {
    if (*numAlunos < MAX_ALUNOS) {
        alunos[*numAlunos].ra = ra;
        strcpy(alunos[*numAlunos].nome, nome);
        (*numAlunos)++;
        printf("Aluno cadastrado com sucesso!\n");
    } else {
        printf("Limite de alunos atingido!\n");
    }
}

void cadastrarDisciplina(struct Disciplina disciplinas[], int *numDisciplinas, int codigo, char nome[]) {
    if (*numDisciplinas < MAX_DISCIPLINAS) {
        disciplinas[*numDisciplinas].codigo = codigo;
        strcpy(disciplinas[*numDisciplinas].nome, nome);
        (*numDisciplinas)++;
        printf("Disciplina cadastrada com sucesso!\n");
    } else {
        printf("Limite de disciplinas atingido!\n");
    }
}

void cadastrarNota(struct Boletim boletim[], int *numNotas, struct Aluno alunos[], int numAlunos, int ra, float nota) {
    if (*numNotas < MAX_NOTAS) {
        int encontrado = 0;
        for (int i = 0; i < numAlunos; i++) {
            if (alunos[i].ra == ra) {
                strcpy(boletim[*numNotas].nome, alunos[i].nome);
                boletim[*numNotas].ra = ra;
                boletim[*numNotas].nota = nota;
                (*numNotas)++;
                printf("Nota cadastrada com sucesso!\n");
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("Aluno não encontrado!\n");
        }
    } else {
        printf("Limite de notas atingido!\n");
    }
}

void consultarAlunos(struct Aluno alunos[], int numAlunos) {
    printf("Lista de Alunos:\n");
    for (int i = 0; i < numAlunos; i++) {
        printf("RA: %d, Nome: %s\n", alunos[i].ra, alunos[i].nome);
    }
}

void consultarReprovados(struct Boletim boletim[], int numNotas, struct Aluno alunos[], int numAlunos) {
    printf("Alunos reprovados em 2 ou mais disciplinas:\n");
    for (int i = 0; i < numAlunos; i++) {
        int reprovacoes = 0;
        for (int j = 0; j < numNotas; j++) {
            if (boletim[j].ra == alunos[i].ra && boletim[j].nota < 6.0) {
                reprovacoes++;
            }
        }
        if (reprovacoes >= 2) {
            printf("RA: %d, Nome: %s\n", alunos[i].ra, alunos[i].nome);
        }
    }
}

void consultarAlunosPorLetra(struct Aluno alunos[], int numAlunos, char letra) {
    printf("Alunos com nomes que começam com a letra '%c':\n", letra);
    for (int i = 0; i < numAlunos; i++) {
        if (alunos[i].nome[0] == letra) {
            printf("RA: %d, Nome: %s\n", alunos[i].ra, alunos[i].nome);
        }
    }
}

void consultarDisciplinasComMediaAbaixoDe6(struct Boletim boletim[], int numNotas, struct Disciplina disciplinas[], int numDisciplinas) {
    printf("Disciplinas com média geral abaixo de 6.0:\n");
    for (int i = 0; i < numDisciplinas; i++) {
        int numNotasDisciplina = 0;
        float somaNotas = 0;
        for (int j = 0; j < numNotas; j++) {
            if (boletim[j].ra == disciplinas[i].codigo) {
                numNotasDisciplina++;
                somaNotas += boletim[j].nota;
            }
        }
        if (numNotasDisciplina > 0) {
            float media = somaNotas / numNotasDisciplina;
            if (media < 6.0) {
                printf("Disciplina: %s, Média: %.2f\n", disciplinas[i].nome, media);
            }
        }
    }
}

void gerarRelatorioCompleto(struct Aluno alunos[], int numAlunos, struct Boletim boletim[], int numNotas, struct Disciplina disciplinas[], int numDisciplinas) {
    printf("Relatório Completo:\n");
    for (int i = 0; i < numAlunos; i++) {
        printf("RA: %d, Nome: %s\n", alunos[i].ra, alunos[i].nome);
        printf("Disciplinas e Notas:\n");
        for (int j = 0; j < numNotas; j++) {
            if (boletim[j].ra == alunos[i].ra) {
                for (int k = 0; k < numDisciplinas; k++) {
                    if (boletim[j].ra == disciplinas[k].codigo) {
                        printf("Disciplina: %s, Nota: %.2f\n", disciplinas[k].nome, boletim[j].nota);
                    }
                }
            }
        }
    }
}

int main() {
    struct Aluno alunos[MAX_ALUNOS];
    struct Disciplina disciplinas[MAX_DISCIPLINAS];
    struct Boletim boletim[MAX_NOTAS];

    int numAlunos = 0;
    int numDisciplinas = 0;
    int numNotas = 0;

    int opcao;
    char letra;

    while (1) {
        printf("\nEscolha uma opção:\n");
        printf("1 - Cadastrar Aluno\n");
        printf("2 - Cadastrar Disciplina\n");
        printf("3 - Cadastrar Nota\n");
        printf("4 - Consultar Alunos\n");
        printf("5 - Consultar Alunos Reprovados\n");
        printf("6 - Consultar Alunos por Letra\n");
        printf("7 - Consultar Disciplinas com Média Abaixo de 6\n");
        printf("8 - Gerar Relatório Completo\n");
        printf("0 - Sair\n");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                int ra;
                char nomeAluno[50];
                printf("Informe o RA do aluno: ");
                scanf("%d", &ra);
                printf("Informe o nome do aluno: ");
                scanf("%s", nomeAluno);
                cadastrarAluno(alunos, &numAlunos, ra, nomeAluno);
                break;
            case 2:
                int codigo;
                char nomeDisciplina[50];
                printf("Informe o código da disciplina: ");
                scanf("%d", &codigo);
                printf("Informe o nome da disciplina: ");
                scanf("%s", nomeDisciplina);
                cadastrarDisciplina(disciplinas, &numDisciplinas, codigo, nomeDisciplina);
                break;
            case 3:
                int raAluno;
                float nota;
                printf("Informe o RA do aluno: ");
                scanf("%d", &raAluno);
                printf("Informe a nota: ");
                scanf("%f", &nota);
                cadastrarNota(boletim, &numNotas, alunos, numAlunos, raAluno, nota);
                break;
            case 4:
                consultarAlunos(alunos, numAlunos);
                break;
            case 5:
                consultarReprovados(boletim, numNotas, alunos, numAlunos);
                break;
            case 6:
                printf("Informe a letra: ");
                scanf(" %c", &letra);
                consultarAlunosPorLetra(alunos, numAlunos, letra);
                break;
            case 7:
                consultarDisciplinasComMediaAbaixoDe6(boletim, numNotas, disciplinas, numDisciplinas);
                break;
            case 8:
                gerarRelatorioCompleto(alunos, numAlunos, boletim, numNotas, disciplinas, numDisciplinas);
                break;
            case 0:
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}

