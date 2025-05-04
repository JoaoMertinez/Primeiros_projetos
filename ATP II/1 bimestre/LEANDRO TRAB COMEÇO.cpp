#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio2.h>

#define TF 20

struct tpData
{
	int d,m,a;
};
	
struct tpProduto
{
	int Cod,Estoque;
	tpData Valid;
	char Descr[TF];
	float Preco;
};

char Menu(void)
{
	clrscr();
	printf("\n# # #  M E N U  # # #\n");
	printf("\n[A] Cadastrar Produtos");
	printf("\n[B] Relatorio de Produtos");
	printf("\n[C] Ordenar Produtos");
	printf("\n[D] Excluir Produtos");
	printf("\n[E] Vender Produtos");
	printf("\n[F] Comprar Produtos");
	printf("\n[G] Exibir Produtos que comecam com uma determinada letra");
	printf("\n[H] Ordenar Produtos pelo preco - Maior par Menor");
	printf("\n[I] Inserir Dados\n");
	printf("\n[ESC] Sair\n");
	printf("\n\nOpcao desejada: ");
	return toupper(getche());
}

void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
{
	int i;
	textcolor(CorT);
	textbackground(CorF);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CF,LF);
	printf("%c",188);
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI); printf("%c",205);
		gotoxy(i,LF); printf("%c",205);
	}
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i); printf("%c",186);
		gotoxy(CF,i); printf("%c",186);
	}
	
	textcolor(7);
	textbackground(0);
}

void MenuPrincipal(void)
{
	textcolor(15);
	gotoxy(3,7);
	printf("# #  M E N U  # #");
	gotoxy(3,9);
	printf("[P] Produtos");
	gotoxy(3,10);
	printf("[C] Clientes");
	gotoxy(3,11);
	printf("[F] Fornecedores");
	gotoxy(3,19);
	printf("[ESC] Sair");
}

void Formulario(void)
{
	system("cls");
	Moldura(1,1,80,25,10,5);
	gotoxy(27,3);
	textcolor(15);
	printf(" # # #  T I T U L O  # # #");
	
	Moldura(2,2,79,4,14,1);
	Moldura(2,5,27,21,12,7);
	MenuPrincipal();
	Moldura(2,22,79,24,11,4);
	gotoxy(4,23);
	textcolor(10);
	printf("Mensagem: ");

	Moldura(28,5,79,21,9,6);
}

void OrdenarProd(tpProduto T[TF], int TL)
{
	tpProduto RegAux;
	int a,b;
	if (TL==0)
		printf("\nNao ha dados para ordenar!\n");
	else
		{
			for(a=0; a<TL-1; a++)
				for(b=a+1; b<TL; b++)
					if(strcmp(T[a].Descr,T[b].Descr)>0)
					{
						RegAux = T[a];
						T[a] = T[b];
						T[b] = RegAux;
					}
					
			printf("\nProdutos ordenados!\n");
		}
	getch();
}

void Relatorio(tpProduto Tab[TF],int TL)
{
	int i;
	printf("\n# # #  Relatorio de Produtos  # # #\n");
	
	if (TL==0)
		printf("\nNao ha dados!\n");
	else
		{
			for(i=0;i<TL;i++)
			{	
				printf("\nCodigo do Produto: %d",Tab[i].Cod);
				printf("\nQuantidade em Estoque: %d",Tab[i].Estoque);
				printf("\nDescricao do Produto: %s",Tab[i].Descr);
				printf("\nPreco: R$ %.2f",Tab[i].Preco);
				printf("\nValidade: %d/%d/%d\n",Tab[i].Valid.d,Tab[i].Valid.m,Tab[i].Valid.a);
			}
			printf("-----------------------------------\n");
		}
	getch();
}

int BuscaCod(tpProduto Tab[TF], int TL, int CodProd)
{
	int a=0;
	while (a<TL && CodProd!=Tab[a].Cod)
				a++;
	
	if (a<TL)
		return a;
	else
		return -1;
}

void InserirDados(tpProduto TabProd[TF], int &TLP)
{
	TabProd[TLP].Cod = 5000;
	strcpy(TabProd[TLP].Descr,"Arroz");
	TabProd[TLP].Estoque = 20;
	TabProd[TLP].Preco = 25;
	TabProd[TLP].Valid.d = 15;
	TabProd[TLP].Valid.m = 8;
	TabProd[TLP].Valid.a = 2025;
	TLP++;
	
	TabProd[TLP].Cod = 9000;
	strcpy(TabProd[TLP].Descr,"Feijao");
	TabProd[TLP].Estoque = 15;
	TabProd[TLP].Preco = 10.56;
	TabProd[TLP].Valid.d = 18;
	TabProd[TLP].Valid.m = 11;
	TabProd[TLP].Valid.a = 2024;
	TLP++;
	
	TabProd[TLP].Cod = 7000;
	strcpy(TabProd[TLP].Descr,"Leite");
	TabProd[TLP].Estoque = 150;
	TabProd[TLP].Preco = 3.99;
	TabProd[TLP].Valid.d = 23;
	TabProd[TLP].Valid.m = 10;
	TabProd[TLP].Valid.a = 2023;
	TLP++;
	
	printf("\n*** Dados inseridos! ***\n");
	getch();
}

void ExcProd(tpProduto TabProd[TF], int &TLP)
{
	int AuxCod, pos;
	
	clrscr();
	printf("\n** Exclusao de Produtos **\n");
	printf("\nCodigo do Produto a excluir: ");
	scanf("%d",&AuxCod);
	while (TLP>0 && AuxCod>0)
	{
		pos = BuscaCod(TabProd,TLP,AuxCod);
		if (pos==-1)
			printf("\nProduto nao Cadastrado!\n");
		else
			{
				printf("\n*** Detalhes do Produto ***\n");
				printf("Codigo: %d\n",TabProd[pos].Cod);
				printf("Descricao: %s\n",TabProd[pos].Descr);
				printf("Estoque: %d\n",TabProd[pos].Estoque);
				printf("Preco: R$ %.2f\n",TabProd[pos].Preco);
				printf("Data de Validade: %d/%d/%d\n\n",TabProd[pos].Valid.d, TabProd[pos].Valid.m, TabProd[pos].Valid.a);
				
				printf("\nConfirma Exclusao (S/N)? ");
				if (toupper(getche())=='S')
				{
					for( ; pos<TLP-1; pos++)
						TabProd[pos] = TabProd[pos+1];
					
					TLP--;
						
					printf("\nProduto deletado!\n");
				}
			}
		
		getch();
		printf("\nCodigo do Produto a excluir: ");
		scanf("%d",&AuxCod);
	}	
}

void CadProd(tpProduto TabProd[TF],int &TLP)
{
	int AuxCod, pos;
	
	clrscr();
	printf("\n** Cadastro de Produtos **\n");
	printf("\nCodigo do Produto: ");
	scanf("%d",&AuxCod);
	while(TLP<TF && AuxCod>0)
	{
		pos = BuscaCod(TabProd,TLP,AuxCod);
		if (pos==-1)
		{
			TabProd[TLP].Cod=AuxCod;
			printf("\nDescricao do Produto: ");
			fflush(stdin);
			gets(TabProd[TLP].Descr);
			printf("\nQuantidade em Estoque: ");
			scanf("%d",&TabProd[TLP].Estoque);
			printf("\nPreco: ");
			scanf("%f",&TabProd[TLP].Preco);
			printf("\nData de Validade[dd mm aa]: ");
			scanf("%d %d %d",&TabProd[TLP].Valid.d,&TabProd[TLP].Valid.m,&TabProd[TLP].Valid.a);
			TLP++;
		}
		else
			{
				printf("\nProduto Cadastrado!\n");
				printf("Produto[%d] - Descricao: [%s]\n\n",pos,TabProd[pos].Descr);
			}
		
		if(TLP<TF)
		{
			printf("\nCodigo do Produto: ");
			scanf("%d",&AuxCod);
		}
		else
			{
				printf("\nTabela Cheia!\n");
				getch();
			}
	}
}

int main(void)
{
	tpProduto Prods[TF];
	
	int TL=0;
	char opcao;
	
	Formulario();
	getch();
	
	do
	{
		opcao = Menu();
		switch(opcao)
		{
			case 'A': CadProd(Prods,TL);
					  break;
					  
			case 'B': Relatorio(Prods,TL);
					  break;
					  
			case 'C': OrdenarProd(Prods,TL);
					  break;
			
			case 'D': ExcProd(Prods,TL);
					  break;
					  
			case 'I': InserirDados(Prods,TL);
					  break;
		}
	}while(opcao!=27);
	
	return 0;
}
