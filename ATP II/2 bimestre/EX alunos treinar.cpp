#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#define TF 5

/*"r". Abrir um arquivo texto para leitura. O arquivo deve estar presente no disco

"w" Abrir um arquivo texto para gravação. Se o arquivo estiver presente ele será destruído 
e reinicializado. Se não existir, ele será criado.

"a" Abrir um arquivo texto para inclusão (acréscimo de informações). Os dados serão 
adicionados ao fim do arquivo existente, ou um novo arquivo será criado.

"r+" Abrir um arquivo texto para leitura e gravação. O arquivo deve existir e pode ser 
atualizado.

"w+" Abrir um arquivo texto para leitura e gravação. Se o arquivo existir ele será destruído 
e reinicializado. Se não existir, será criado.

"a+" Abrir um arquivo texto para leitura e para adicionar dados ao fim do arquivo existente. 
Caso não exista, um novo arquivo será criado.

"rb" Abrir um arquivo binário para leitura. O arquivo deve estar presente no disco.

"wb" Abrir um arquivo binário para gravação. Se o arquivo estiver presente ele será 
destruído e reinicializado. Se não existir, ele será criado.

"ab" Abrir um arquivo binário para inclusão. Os dados serão adicionados ao fim do arquivo 
existente, ou um novo arquivo será criado. Não permite leitura dos dados.

"rb+" Abrir um arquivo binário para leitura e gravação. O arquivo deve existir e pode ser 
atualizado.

"wb+" Abrir um arquivo binário para leitura e gravação. Se o arquivo existir ele será 
destruído e reinicializado. Se não existir, será criado.

"ab+" Abrir um arquivo binário para atualizações e para adicionar dados ao fim do arquivo 
existente ou um novo arquivo será criado. Possibilita a leitura dos dados existentes.*/

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

int buscaRA(FILE *ptra,int ral)
{
	Aluno r;
	
	rewind(ptra);
	fread(&r,sizeof(Aluno),1,ptra);
	while(!feof(ptra) && ral!=r.ra)	
		fread(&r,sizeof(Aluno),1,ptra);
		
	if(!feof(ptra))
		return ftell(ptra) - sizeof(Aluno);			//sizeof é a variavel local e nao o ponteiro	//ftell conta os bits ate onde ta o PONTEIRO
	else 
		return -1;
	
}


void salvarAlunos()
{
	long int pos=0;
	Aluno r;//declarar a struct para manipular
	FILE * ptra = fopen("arquivo.jc","ab");//colocar o "nome" , "tipo" de abertura
	
	if(ptra == NULL)
		printf("Erro ao abrir o arquivo");
	else
	{
		printf("\ninforme o ra do aluno: ");
	    scanf("%d",&r.ra);
	    while(r.ra>0) //nao estou usando um vetor entao nao preciso de []
		{
			printf("a");
			pos = buscaRA(ptra,r.ra);
			if(pos<0)
			{
				printf("\ninforme o nome do aluno: ");
	    		fflush(stdin);
	    		gets(r.nome);
	    		fwrite(&r,sizeof(Aluno),1,ptra); //sizeof(x) x = pode ser a variavel ou o tipo , //ja salva tudo de uma vez
	    		printf("\ninforme o ra do aluno: ");
		   		scanf("%d",&r.ra);		
			}
			else
			{
				printf("\nRA ja cadastrado");
				getch();		
			}
		}
		fclose(ptra);
	}	
	getch();
}

void salvarDisciplina()
{
	Disciplina D;
	
	FILE *ptrd = fopen("materias.dat","ab");
	
	if(ptrd == NULL)
		printf("\nERRO!");
	
	printf("\nInforme o codigo da disciplina: ");
	scanf("%d",D.codigo);
	while(D.codigo>0)
	{
		printf("\nInforme o nome da disciplina: ");
		fflush(stdin);
		gets(D.nome);
		fwrite(&D,sizeof(Disciplina),1,ptrd);
		printf("\nInforme o codigo da disciplina: ");
		scanf("%d",&D.codigo);
		
	}
	fclose(ptrd);
	getch();
}

void exibirDisciplinas()
{
	Disciplina D;
	
	FILE *ptrd = fopen("materias.dat","rb");
	
	if(ptrd == NULL)
		printf("ERRO!");
	else
	{
		fread(&D,sizeof(Disciplina),1,ptrd);
		while(!feof(ptrd))
		{
			printf("\nCodigo da materia: %d\n",D.codigo);
			printf("\nNome da materia: %s\n",D.nome);
			fread(&D,sizeof(Disciplina),1,ptrd);
		}
		fclose(ptrd);
	}	
	
	getch();
}

void exibirAlunos()
{
	Aluno r;
	FILE *ptre = fopen("arquivo.jc","rb");
	
	if(ptre == NULL)
		printf("Erro ao abrir o arquivo");
	else
	{
		fread(&r,sizeof(Aluno),1,ptre);
		while(!feof(ptre)) //se chegou no final do arquivo (!feof(prte))
		{
			printf("\nRa do aluno: %d",r.ra);
			printf("\nNome do aluno: %s\n",r.nome);
			fread(&r,sizeof(Aluno),1,ptre);
		}
		fclose(ptre);//fechar dentro do else	
	}
	
	getch();
}

void ordenarMat ()
{
	Disciplina A,B;
	int qtda;
	int i,j;
	
	FILE *ptr=fopen("materias.dat","rb+");
	
	if(ptr==NULL)
		printf("\nERRO!");
	else
	{
		fseek(ptr,0,2);//joga o ponteiro para o final
		qtda = ftell(ptr)/sizeof(Disciplina);
		for(i=0;i<qtda-1;i++)//-1 pois o ultimo é o eof
			for(j=i+1;j<qtda-1;j++)
			{
				fseek(ptr,i*sizeof(Disciplina),0);
				fread(&A,sizeof(Disciplina),1,ptr);
				fseek(ptr,j*sizeof(Disciplina),0);
				fread(&B,sizeof(Disciplina),1,ptr);
				
				if(A.codigo>B.codigo)
				{
					fseek(ptr,i*sizeof(Disciplina),0);	
					fwrite(&B,sizeof(Disciplina),1,ptr);
					fseek(ptr,j*sizeof(Disciplina),0);	
					fread(&A,sizeof(Disciplina),1,ptr);
				}
			} 
			
		printf("\nArquivo de disciplina ordenado");
		fclose(ptr);
	}
	getch();	
}

char menu(void)
{
	clrscr();
	printf("\n# # # #   M E N U   # # # #\n");
	printf("\n[A] - Cadastrar Alunos");
	printf("\n[B] - Exibir Alunos");
	printf("\n[C] - Cadastrar disciplinas");
	printf("\n[D] - Exibir disciplinas");
	printf("\n[E] - Ordenar disciplinas");
	printf("\n[ESC] - Finalizar");
	printf("\nOpcao desejada: \n");
	return toupper(getche());
}

int main() {
    char op;

	do //nao esquecer ta repetiçao
	{
		op = menu();
		switch(op)
		{
			case 'A':
				salvarAlunos();
				break;
				
			case 'B':
				exibirAlunos();			
				break;
				
			case 'C':
				salvarDisciplina();
				break;
				
			case 'D':
				exibirDisciplinas();
				break;
			
			case 'E':
				ordenarMat();
				break;
		}	
	}while (op!=27);
    return 0;
}

