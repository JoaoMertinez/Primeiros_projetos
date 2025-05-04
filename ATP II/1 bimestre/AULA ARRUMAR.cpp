/*
Quando for void dentro do int main não precisa do return no final, mas quando for outra coisa dentro do int main
precisa do return 0;

getch não mostra a letra que voce digita, já o getche ele mostra a letra que você digitou
ambos não precisa do ENTER para receber, apenas de você clicar na tecla já vai e por isso não usa fflush
*/

//..:: IMPLEMENTAR ..::
//	..:: Mostrar o Menu e implementar as seguintes operações ::..
//		[A] Inserir Nomes em uma Lista (máximo 10)
//		     -> deve-se parar quando se pressionar <ENTER> ou 
//			    quando encher a Lista;
//		     -> Não deve ser possível cadastrar Nomes iguais.
//		[B] Exibir a Lista
//		[C] Ordenar a Lista
//		[D] Excluir Nomes da Lista até se pressionar <ENTER> ou a Lista
//		    estiver vazia
//		[E] Insere nomes em uma lista2
//		[F] Realizar a inserção de todos os nomes que começam com uma determinada letra em uma terceira lista
//  	[G] Realizar intersecção entre a lista3 e as lista 1 e 2, mostrando os nomes que satisfazem essa operação
//		[ESC] Sair


#include<stdio.h> //funções
#include<string.h> 
#include<stdlib.h> //atoi e atof
#include<conio.h> //getch e getche
#include<ctype.h> //toupper

#define TF 10

int main(void)
{
	char lista[TF][30], op, auxNome[30], lista2[TF][30], lista3[TF*2][30];
	
	int tl=0, i=0, pos=0, j=0; 
	
	do
	{
		system("cls");//limpando tela dos
		printf("[A] Inserir nomes na lista1:\n");
		printf("[B] Exibir lista:\n");
		printf("[C] Ordenar a lista:\n");
		printf("[D] Exclir nomes da lista:\n");
		printf("[E] Inserir nomes na lista2:\n");
		printf("[F] Realizar a insercao de nomes com a mesma letra:\n");
		printf("[G] Realizar intersecção entre as 3 lista, mostrar nomes que satisfazem essa operação:\n"); 
		printf("[ESC] Sair\n");
		printf("\nOpcao desejada: ");
		
		op = toupper(getche()); //recebendo a letra digitada já em maiusculo e armazenando na variavel op
		
		
		switch(op)
		{
			case 'A':
				printf("\n\n##Inserir nomes##\n");
				printf("Lista1 [%d]: ",tl);//entra lido
				fflush(stdin);
				gets(auxNome);
				
				while(tl<TF && strcmp(auxNome,"\0")!=0)
				{
					pos=0;
					while(pos<tl && strcmp(lista[pos],auxNome)!=0)//buscando para saber se já existe o nome
						pos++;
						
					if(pos<tl)//se o nome já existe entra nessa opção
					{
							printf("Esse nome ja existe!\n");
							printf("Digite outro nome: ");
							fflush(stdin);
							gets(auxNome);
					}
					
					strcpy(lista[tl],auxNome);//copiando nome recebido para lista
					tl++;
					if(tl<TF)
					{
						printf("\nLista [%d]: ",tl);//sai lido
						fflush(stdin);
						gets(auxNome);
					}
					else
						printf("Nao tem mais espaco!\n");	
				}
				getch();
				break;
				
			case 'B':
				printf("\n##Conteudo da lista##\n");
				
				if(tl==0)
					printf("Lista vazia!\n");
				else
				{
					printf("Lista1:\n");
					for(i=0; i<tl; i++)
						printf("Lista1 [%d]: %s\n",i, lista[i]);
					printf("Lista2:\n");
					for(i=0; i<tl; i++)
						printf("Lista2 [%d]: %s\n",i,lista2[i]);
				}
				getch();
				break;
				
			case 'C':
				printf("\n##Ordenar a lista##\n");
				for(i=0;i<tl;i++)
					for(j=i+1;j<tl;j++)
					{
						if(stricmp(lista[j],lista[i])<0)
						{
							strcpy(auxNome,lista[i]);
							strcpy(lista[i],lista[j]);
							strcpy(lista[j],auxNome);
						}
					}
				
				getch();
				break;
			case 'D':
				printf("\n##Excluir nomes da lista##\n");
				if(tl==0)
					printf("Vetor vazio!\n");
				else
				{
					printf("Digite o nome que deseja excluir: ");
					fflush(stdin);
					gets(auxNome);
					pos=0;
				
				
					while(pos<tl && strcmp(lista[pos],auxNome)!=0)//busca o nome
						pos++;
					
					if(pos<tl)
					{
						for(i=pos; i<tl-1; i++)
							strcpy(lista[i],lista[i+1]);
						tl--;
					}
					else
						printf("Nao foi encontrado o nome!\n");
				}
				
				getch();
				break;
			case 'E':
				tl=0;
				printf("\n##Inserir nomes lista2##\n");
				printf("Lista2 [%d]: ",tl);
				fflush(stdin);
				gets(auxNome);
				
				while(tl<TF && strcmp(auxNome,"\0")!=0)
				{
					pos=0;
					while(pos<tl && strcmp(lista2[pos],auxNome)!=0)//busca para ver se o nome já existe
						pos++;
						
					if(pos<tl)//se caso o nome já existe entra aqui
					{
						printf("Esse nome ja existe!\n");
						printf("Digite outro nome: ");
						fflush(stdin);
						gets(auxNome);
					}
					strcpy(lista2[tl],auxNome);
					tl++;
					
					if(tl<TF)//veifica se ainda tem espaço no vetor
					{
						printf("Lista2 [%d]: ",tl);
						fflush(stdin);
						gets(auxNome);
					}
					else
						printf("Nao tem mais espaco!\n");
				}
				getch();
				break;
			case 'F':
				printf("\n##Inserção de todos os nomes##\n");
				printf("Digite a letra que deseja: ");
				fflush(stdin);
				scanf("%c",&auxNome);
				pos=0;
				
				for(i=0; i<tl; i++)//buscando nomes com uma determinada letra na lista1
				{
					if(lista[i][0] == auxNome[0])
					{
						strcpy(lista3[pos],lista[i]);
						pos++;
					}
				}
				
				for(i=0; i<tl; i++)//buscando nomes com uma determinada letra na lista2
				{
					if(lista2[i][0] == auxNome[0])
					{
						strcpy(lista3[pos],lista2[i]);
						pos++;
					}
				}
				
				printf("\nLista3 com nomes que comecam com %c\n",auxNome[0]);
				for(i=0; i<tl; i++)	//exibindo a lista3 com os nomes
					printf("Lista3 [%d]: %s\n",i,lista3[i]);
				
				getch();
				break;
			case 'G':
				printf("\n## Interseccao entre as 3 listas##\n");
				tl=pos;
				
				for(i=0;i<tl;i++)
				{
					if(strcmp(lista3[i],lista[i])==0)
					{
						puts(lista[i]);
					}
					else
						pos++;	
					
					if(pos==tl)
						printf("\nesse nome nao esta em nenhuma lista");
					
				}
				
				
				
				
				getch();
				break;
		}
	}while(op != 27);
	if(op == 27)
		printf("\nPPrograma encerrado!\n");	
	return 0;
}
