/*#include <stdio.h>
#include <string.h>
#define TF 50
struct TpAluno{
	int Ra;
	char nome;
};
     
int buscaAluno(TpAluno vet[TF], int tla,int aux)
{
	int pos=0;
	
	while(pos<tla && vet[pos].Ra!=aux)
		pos++;
		
	if(pos<tla)
		return pos;
	else
		return -1;	
		
}

void registro(TpAluno vet[TF], int &tla)
{
	int aux,pos;
	char Auxnome[40];
	
	printf("\n informe o RA do aluno[%d]: ",tla+1);
	scanf("%d",&aux);
	while(aux>0)
	{
		pos = buscaAluno(vet,tla,aux);
		if(pos<0)
		{
			vet[tla].Ra = aux;
			printf("\n informe o nome do aluno[%d]: ",tla+1);
			fflush(stdin);
			gets(vet[tla].nome);
			tla++;
		}
		else 
			printf("\nRA ja cadastrado!");
		
		printf("\n informe o RA do aluno[%d]: ",tla+1);
		scanf("%d",&aux);	
	}	
}
int main()
{
	TpAluno vetA;
	int tla=0;
	
	registro(vetA,tla);
	
}
*/




