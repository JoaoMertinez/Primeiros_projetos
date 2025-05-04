#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#define TF 5

/*"r". Abrir um arquivo texto para leitura. O arquivo deve estar presente no disco

"w" Abrir um arquivo texto para grava��o. Se o arquivo estiver presente ele ser� destru�do 
e reinicializado. Se n�o existir, ele ser� criado.

"a" Abrir um arquivo texto para inclus�o (acr�scimo de informa��es). Os dados ser�o 
adicionados ao fim do arquivo existente, ou um novo arquivo ser� criado.

"r+" Abrir um arquivo texto para leitura e grava��o. O arquivo deve existir e pode ser 
atualizado.

"w+" Abrir um arquivo texto para leitura e grava��o. Se o arquivo existir ele ser� destru�do 
e reinicializado. Se n�o existir, ser� criado.

"a+" Abrir um arquivo texto para leitura e para adicionar dados ao fim do arquivo existente. 
Caso n�o exista, um novo arquivo ser� criado.

"rb" Abrir um arquivo bin�rio para leitura. O arquivo deve estar presente no disco.

"wb" Abrir um arquivo bin�rio para grava��o. Se o arquivo estiver presente ele ser� 
destru�do e reinicializado. Se n�o existir, ele ser� criado.

"ab" Abrir um arquivo bin�rio para inclus�o. Os dados ser�o adicionados ao fim do arquivo 
existente, ou um novo arquivo ser� criado. N�o permite leitura dos dados.

"rb+" Abrir um arquivo bin�rio para leitura e grava��o. O arquivo deve existir e pode ser 
atualizado.

"wb+" Abrir um arquivo bin�rio para leitura e grava��o. Se o arquivo existir ele ser� 
destru�do e reinicializado. Se n�o existir, ser� criado.

"ab+" Abrir um arquivo bin�rio para atualiza��es e para adicionar dados ao fim do arquivo 
existente ou um novo arquivo ser� criado. Possibilita a leitura dos dados existentes.*/


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
    int codigo;
    float nota;
};


void salvarAlunos(void) {
	
	int i;
	Aluno aluno;
	
    FILE *ptra = fopen("alunos1.bin", "ab");

   if (ptra == NULL) {
        printf("Erro ao abrir o arquivo de alunos.\n");
        return;
    }
    else
    {
    	printf("\ninforme o ra do aluno: ");
	    scanf("%d",&aluno.ra);
	    while(aluno.ra > 0)
		{
			printf("\ninforme o nome do aluno: ");
	    	fflush(stdin);
	    	gets(aluno.nome);
	    	
	    	
	    	fwrite(alunos, sizeof(struct Aluno),numAlunos+1, file);//numAlunos+1
	    	printf("\ninforme o ra do aluno: ");
	  		scanf("%d",&alunos.ra);
		}
		       
	    fclose(ptra); 	
	}   
}

void exibirAlunos(Aluno alunos[TF], int numAlunos) {
	int i=0;
	
    FILE *file = fopen("alunos1.bin","rb");

    if (file == NULL) {
        printf("Arquivo de alunos n�o encontrado\n");
        return;
    }

    fseek(file, 0, SEEK_SET);
	
	fread(&alunos[i], sizeof(struct Aluno), 1, file);
	
    for (i = 0; i < numAlunos; i++) {
    	if(!feof(file))
    	{
    		printf("Ra do aluno: %d\n", alunos[i].ra);
        	printf("Nome do aluno: %s\n", alunos[i].nome);
        
       	 fread(&alunos[i], sizeof(struct Aluno), 1, file);
		}
		else
			printf("Erro inesperado!"); 
    }

    fclose(file);
}

char menu(void)
{
	clrscr();
	printf("\n# # # #   M E N U   # # # #\n");
	printf("\n[A] - Cadastrar Alunos");
	printf("\n[B] - Exibir Alunos");
	printf("\n[C] - Consultar Funcionarios");
	printf("\n[D] - Alterar Funcionarios");
	printf("\n[E] - Ordenar Funcionarios");
	printf("\n[ESC] - Finalizar");
	printf("\nOpcao desejada: \n");
	return toupper(getche());
}

int main() {
  	Aluno alunos[TF];
    Disciplina disciplinas[TF];
    Boletim boletim[TF];
    
    char op;

    int numAlunos = 0;
    int numDisciplinas = 0;
    int numNotas = 0;
	
	
	do //nao esquecer ta repeti�ao
	{
		op = menu();
		switch(op)
		{
			case 'A':
				salvarAlunos(alunos,numAlunos);
				break;
				
			case 'B':
				exibirAlunos(alunos,numAlunos);			
				break;
		}	
	}while (op!=27);
    return 0;
}

