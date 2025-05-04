#include <stdio.h>
#include <string.h>

struct Pessoa {
    char nome[50];
    int idade;
};

int main() {
    FILE *arquivo;

    // Abrindo um arquivo binário para escrita
    arquivo = fopen("pessoas.bin", "wb");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Escrevendo dados no arquivo binário
    struct Pessoa pessoa1;
    strcpy(pessoa1.nome, "carlos");
    pessoa1.idade = 25;

    fwrite(&pessoa1, sizeof(struct Pessoa), 1, arquivo);

    // Fechando o arquivo
    fclose(arquivo);

    // Abrindo o arquivo binário para leitura
    arquivo = fopen("pessoas.bin", "rb+");
    
    int aux;
    scanf("%d",&aux);

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lendo os dados do arquivo binário
    struct Pessoa pessoa_lida;

    fread(&pessoa_lida, sizeof(struct Pessoa), 1, arquivo);

    printf("Nome: %s\n", pessoa_lida.nome);
    printf("Idade: %d\n", pessoa_lida.idade);

    // Fechando o arquivo
    fclose(arquivo);

    return 0;
}

