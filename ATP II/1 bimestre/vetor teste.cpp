#include <stdio.h>
#define TF 50
int main()
{
	
	int a,b,cont=0,num,vetor[TF],valor,tl=0,maior=0,numaior=0;
	
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
	printf("\nO numero que mais repetiu foi o %d",numaior);
	printf("\n O numero de vezes que esse numero repetiu foi de:%d",maior);
	
	
		
}
