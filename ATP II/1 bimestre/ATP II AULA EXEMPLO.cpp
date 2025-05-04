/*
Quando for void dentro do int main não precisa do return no final, mas quando for outra coisa dentro do int main
precisa do return 0;

getch não mostra a letra que voce digita, já o getche ele mostra a letra que você digitou
ambos não precisa do ENTER para receber, apenas de você clicar na tecla já vai e por isso não usa fflush
*/

//..:: IMPLEMENTAR ..::
//	..:: Mostrar o Menu implementar as seguintes operações ::..
//		[A] Inserir Nomes em uma Lista (máximo 10)
//		     -> deve-se parar quando se pressionar <ENTER> ou 
//			    quando encher a Lista;
//		     -> Não deve ser possível cadastrar Nomes iguais.
//		[B] Exibir a Lista
//		[C] Ordenar a Lista
//		[D] Excluir Nomes da Lista até se pressionar <ENTER> ou a Lista
//		    estiver vazia
//		[ESC] Sair

#include<stdio.h> //funções
#include<string.h> 
#include<stdlib.h> //atoi e atof
#include<conio.h> //getch e getche
#include<ctype.h> //toupper

#define TF 50

int main(void)
{
	char lista[TF][30],lista2[TF][30],lista3[TF*2][30], op, auxNome[30],aux[30],letra;
	
	int tl=0, i=0, pos=0, j; 
	
	do
	{
		system("cls");//limpando tela dos
		printf("[A] Inserir nomes:\n");
		printf("[B] Exibir lista:\n");
		printf("[C] Ordenar a lista:\n");
		printf("[D] Exclir nomes da lista:\n");
		printf("[E] Adicionar nomes a lista 2:\n");
		printf("[F] Oganizar uma lista por letra:\n");
		printf("[ESC] Sair\n");
		printf("\nOpcao desejada: ");
		
		op = toupper(getche()); //recebendo a letra digitada já em maiusculo e armazenando na variavel op
		
		switch(op)
		{
			case 'A':
				printf("\n\n##Inserir nomes##\n");
				printf("Lista [%d]: ",tl);//entra lido
				fflush(stdin);
				gets(auxNome);
				
				while(tl<TF && strcmp(auxNome,"\0")!=0)
				{
					pos=0;
					while(pos<tl && strcmp(lista[pos],auxNome)!=0)
						pos++;
						
					if(pos<tl)
					{
							printf("Esse nome ja existe!\n");
							printf("Digite outro nome: ");
							fflush(stdin);
							gets(auxNome);
					}
					else
					{
						strcpy(lista[tl],auxNome);//copiando nome recebido para lista
						tl++;
						
					}		
					if(tl<TF)
					{
						printf("\nLista [%d]: ",tl);//sai lido
						fflush(stdin);
						gets(auxNome);
					}
					else
						printf("Nao tem mais espaco espaco!\n");	
				}
				getch();
				break;
				
			case 'B':
				printf("\n##Conteudo da lista##\n");
				if(tl==0)
					printf("Lista vazia!\n");
				else
					for(i=0; i<tl; i++)
						printf("Lista %d: %s\n",i, lista[i]);
				getch();
				break;
				
			case 'C':
				printf("\n##Lista ordenada##\n");
				for(j=0;j<tl;j++)
				  for(i=j+1;i<tl;i++)
				    {	
				       	if(strcmp(lista[i],lista[j])<0)
				       	{
				       		strcpy(aux,lista[j]);
				 	      	strcpy(lista[j],lista[i]);
				  	     	strcpy(lista[i],aux);		
						}  
				    }
				getch();
				break;
			case 'D':
				printf("\n##Excluir nomes da lista##\n");
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
				
				getch();
				break;
			
			case 'E':
				tl=0;
				printf("\n\n##Inserir nomes na lista 2##\n");
				printf("Lista [%d]: ",tl);//entra lido
				fflush(stdin);
				gets(auxNome);
				
				while(tl<TF && strcmp(auxNome,"\0")!=0)
				{
					pos=0;
					while(pos<tl && strcmp(lista2[pos],auxNome)!=0)
						pos++;
						
					if(pos<tl)
					{
							printf("Esse nome ja existe!\n");
							printf("Digite outro nome: ");
							fflush(stdin);
							gets(auxNome);
					}
					
					strcpy(lista2[tl],auxNome);//copiando nome recebido para lista
					tl++;
					if(tl<TF)
					{
						printf("\nLista [%d]: ",tl);//sai lido
						fflush(stdin);
						gets(auxNome);
					}
					else
						printf("Nao tem mais espaco espaco!\n");	
				}
				printf("\n##Conteudo da lista 2##\n");
				if(tl==0)
					printf("Lista vazia!\n");
				else
					for(i=0; i<tl; i++)
						printf("Lista %d: %s\n",i, lista2[i]);
				getch();
			
			    break;	
			    
			case 'F':
				printf("\n##Inserção de todos os nomes##\n");
				printf("Digite a letra que deseja: ");
				fflush(stdin);
				scanf("%c",&auxNome);
				pos=0;
				
				for(i=0; i<tl; i++)
				{
					if(lista[i][0] == auxNome[0])
					{
						strcpy(lista3[pos],lista[i]);
						pos++;
					}
				}
				
				for(i=0; i<tl; i++)
				{
					if(lista2[i][0] == auxNome[0])
					{
						strcpy(lista3[pos],lista2[i]);
						pos++;
					}
				}
				
				printf("\nLista3 com nomes que comecam com %c\n",auxNome[0]);
				for(i=0; i<pos; i++)	
					printf("Lista3 [%d]: %s\n",i,lista3[i]);
				
				getch();
			
					
			    break;
		}
	}while(op != 27);
	if(op == 27)
		printf("\nPPrograma encerrado!\n");	
	return 0;
}




