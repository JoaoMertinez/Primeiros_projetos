#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<math.h>
#include <ctype.h>

#define TF 50

char menu (void)
{
	clrscr();
	printf("\n##MENU##");
	printf("\n [A] Converte decimal para binario");
	printf("\n [B] Converte binario para decimal");
	printf("\n [C] Insere numeros em um vetor");
	printf("\n [D] Exibe conteudo de um vetor");
	printf("\n [E] Exercicio 1 da lista 2");
	printf("\n [ESC] Sair\n");
	
	return toupper(getche());
}

///VETOR///
void Levetor (int vetor[TF],int &tl) //scanf(" tipo = (%d)",&valor);//
{
	int valor;
	printf("\nDigite um numero para inserir no vetor:\n");
	printf("\nDigite [0] para encerrar: [%d]: ",tl);
	scanf("%d",&valor);
	while (tl<TF && valor>0)
	{	
		vetor[tl]=valor;
		tl++;
		
		printf("\nDigite [0] para encerrar [%d]: ",tl);
		scanf("%d",&valor);
	}	
}

void Exibevetor (int vetor[TF],int tl) 
{
	int i;

	if(tl==0)
		printf("\nvetor vazio");
	else
		for(i=0;i<tl;i++)
			printf("\nvetor[%d] %d",i,vetor[i]);
	getch();
}

void Contavetor (int vetor[TF], int tl, int &numaior, int &maior)
{
	int a,b,cont=0,num;
	
	if(tl=0)
		printf("\nVetor vazio");
	else
	{
		for(a=0;a<tl;a++)
		{
			num=vetor[a];
			cont=0;
			
			for(b=a;b<tl;b++)
			{
				if(vetor[b]==num);
				cont++;
				
				if(cont>maior)
				{
					maior=cont;
					numaior=num;
				}
			}
		}
		
	}
}

void Exibemaior (int maior, int numaior)
{
	printf("\nO numero que mais repetiu foi o %d",numaior);
	printf("\n O numero de vezes que esse numero repetiu foi de:%d",maior);
}


///VETOR///


///DECIMAL E BINARIO///
int DecToBin(int decimal)
{	
	int binario=0,mult=1,div,resto=0,i=1;
	while(decimal>1)
	{
	  div=decimal % 2;
	  binario=binario + mult*div;
	  decimal=decimal/2;
	  mult=mult*10;
	}
	binario=binario + mult*decimal;
		
	return binario;
}

int DecToDec(int binario)
{
	
	 int decimal=0, i, resto;
	 for(i=0; binario>=10; i++)
	 {
	  resto = binario % 10;
	  binario = binario / 10;
	  decimal = decimal + resto * pow(2,i);
	 }
	 
	 decimal = decimal + binario * pow(2,i);
	 return decimal;
 
}

int LeValor(void)
{
	int valor;
	
	printf("\nDigite um valor para ser convertido: ");
	scanf("%d",&valor);
	return valor;
}

void ExibeResultado(int resto)
{
	printf("\nResultado: %d\n",resto);
	getch();
}
///DECIMAL E BINARIO///
		

int executar(void)
{
	int vetor[TF],tam=0,var,ver;
	char op;
	
	do
	{
		op=menu();
		
		switch(op)
		{
			case 'A':printf("\nConverte decimal para binario:\n");
					 ExibeResultado(DecToBin(LeValor()));
					 break;
					 
			case 'B':printf("\nConverte binario para decimal:\n");
					 ExibeResultado(DecToDec(LeValor()));
					 break;
					 
			case 'C':printf("\nInsere numeros em um vetor:\n");
					 Levetor(vetor,tam);
					 break;
					 
			case 'D':printf("\nExibe numeros em um vetor\n");
					 Exibevetor(vetor,tam);
					 break;
					 
			case 'E':printf("\nValor do vetor que aparece com mais frequencia");
					 Exibemaior(Contavetor(vetor,tam));
					 break;
					 			
		}
		
	}while(op != 27);
	
}
int main(void)
{
	 executar();
	 
 return 0;
}

