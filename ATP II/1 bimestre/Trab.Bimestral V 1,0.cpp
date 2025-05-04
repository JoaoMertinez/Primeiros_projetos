#include<stdio.h> // Biblioteca principal
#include<conio2.h> // Biblioteca para utilizar moldura
#include<string.h> // Biblioteca para manipulação de strings
#include<stdlib.h> // Biblioteca que converte string para numero
#include<ctype.h>

#define TF 20

/*	//Codigo para mostrar na barra de mensagens
	LimpaTela(); 
	gotoxy(13,23);
	printf("Mensagem");
	getch();
*/


//Struct com as datas de validade
struct TpValidade
{
	int dia, mes, ano;
};


//Struct com as datas de venda
struct TpData
{
	int dia, mes, ano;
};

//Struct com as informações dos produtos
struct TpProdutos
{
	int cod, estoque;
	char descr[30];
	float preco;
	
	TpValidade validade;
};

//Struct com as informações dos fornecedores
struct TpFornecedor
{
	int codForn;
	char nomeForn[30], cidade[30];
};

//Struct com as informações dos clientes
struct TpCliente
{
	int cpf, qtdeCompra;
	char nomeCliente[30];
	float valorTotCompr; 
};

//Struct com as informações das vendas
struct TpVendas
{
	int codVenda; //CodVenda tem que ser sequencial
	float totVenda;
};

//Struct com as informações das vendas dos produtos
struct TpVendaProd
{
	int qtde;
	float valorUni;
};


void LimpaTela(void)
{
	 int x,y;
	 //LIMPA QUADRADO
	 for(x=30;x<=78;x++)
	 {
		for(y=6;y<=20;y++)
		{
		   gotoxy(x,y);
		   printf(" ");
		}
	 }
	 //LIMPA MENSAGEM
	 for(x=13;x<78;x++)
	 {
	 	gotoxy(x,23);
		printf("  ");
	 }
}

//Funçao que busca codigo do fornecedor
int buscaForn(TpFornecedor tab[TF], int tlf, int codProd)
{
	int pos=0;
	
	while(pos<tlf && codProd!=tab[pos].codForn)
		pos++;
		
	if(pos<tlf)
		return pos;
	else
		return - 1;	
	
}
//Função que faz a busca pelo codigo do produto
int buscaCod(TpProdutos Tab[TF], int tl, int codProd)
{
	int pos=0;
	
	while(pos<tl && codProd!=Tab[pos].cod)
		pos++;
	
	if(pos<tl)
		return pos;
	else
		return -1;
}
//Funcao que altera os dados do fornecedor
void alteraForn(TpFornecedor tabForn, int tlf)
{
    int resp,pos;
    
    char auxNome[30];
    
    LimpaTela();

    gotoxy(30,6);
    printf("* Alteraçao de dados *");
    gotoxy(30,8);
    printf("Digite o codigo do forncedor: ");
    scanf("%d",&resp);


    pos = buscaForn(tabForn[TF],tlf,resp);

    if(pos<0)//nao achou
    {
        LimpaTela(); 
        gotoxy(13,23);
        printf("Fornecedor nao encontrado!");
        getch();
    }
    else
    {
        LimpaTela();
        gotoxy(30,8);
        printf("Digite a opcao desejada: ");
        gotoxy(30,9);
        printf("1 - Codigo");
        gotoxy(30,10);
        printf("2 - Nome");
        gotoxy(30,11);
        printf("3 - Cidade");
        scanf("%d",&resp);
        
            switch(resp)
            {
                case 1:
                    LimpaTela();
                    gotoxy(30,6);
                    printf("Digite novo codigo para ser alterado: ");
                    gotoxy(30,7);
                    scanf("%d",&resp);
                    tabForn.codForn[pos]=resp;
                    
                    gotoxy(13,23);
                    printf("Alteracao feita com sucesso!");
                    getch();
                    break;

                case 2:
                    LimpaTela();
                    gotoxy(30,6);
                    printf("Digite novo nome para ser alterado: ");
                    fflush(stdin);
                    gotoxy(30,7);
                    gets(auxNome);
                    strcpy(tabForn[pos].nomeForn,auxNome);
                    
                    gotoxy(13,23);
                    printf("Alteracao feita com sucesso!");
                    getch();
                    break;
                    
                case 3:
                	LimpaTela();
                	gotoxy(30,6);
                	printf("Digite uma nova cidade para ser alterada: ");
                	fflush(stdin);
                	gotoxy(30,7);
                	gets(auxNome);
                	strcpy(tabForn[pos].cidade,auxNome);               	
                	gotoxy(13,23);
                	printf("Alteracao feita com sucesso!");
                	getch();
                	break;
			}
    }
}
//Funcao que cadastra o fornecedor
void cadFor(TpFornecedor tabForn[TF], int &tlf)
{
	int auxCod, pos;	
	LimpaTela();
	
	gotoxy(30,6);
	printf("*** Cadastro de Fornecedor ***");
	gotoxy(30,8);
	printf("Codigo do Fornecedor: ");
	scanf("%d",&auxCod);
	
	while(tlf<TF && auxCod>0)
	{
		pos = buscaForn(tabForn,tlf,auxCod);
		
		if(pos==-1)
		{
			tabForn[tlf].codForn=auxCod;
			gotoxy(30,9);
			printf("Nome do fornecedor:");
			fflush(stdin);
			gets(tabForn[tlf].nomeForn);
			gotoxy(30,10);
			printf("Cidade do fornecedor:");
			gets(tabForn[tlf].cidade);
			tlf++;
		}
		else
		{
			LimpaTela();
			gotoxy(13,23);
			printf("Codigo Cadastrado!");
			gotoxy(30,9);
			printf("Codigo[%d] - nome: [%s]",pos,tabForn[pos].nomeForn);
			getch();
		}
		
		LimpaTela();
		gotoxy(30,6);
		printf("** Cadastro de Fornecedor **");
		if(tlf<TF)
		{
			gotoxy(30,8);
			printf("Codigo do Fornecedor: ");
			scanf("%d",&auxCod);
		}
	}
	
		if(auxCod==0)//mostrando que nao pode
		{
			LimpaTela();
			gotoxy(13,23);
			printf("Codigo invalido");
			getch();	
			
		
		}
	
	//Se caso a tabela já estiver cheia e o usario tentar cadastrar denovo
	if(tlf==TF)
	{
		LimpaTela();
		gotoxy(13,23);
		printf("Tabela cheia!");
		getch();//para voltar ao menu
	}
}
//Função que cadastra o produto
void cadProd(TpProdutos TabProd[TF], int &tlp)
{
	int auxCod, pos;
	
	LimpaTela();
	
	gotoxy(30,6);
	printf("*** Cadastro de Produtos ***");
	gotoxy(30,8);
	printf("Codigo do Produto: ");
	scanf("%d",&auxCod);
	while(tlp<TF && auxCod>0)
	{
		pos = buscaCod(TabProd,tlp,auxCod);
		if (pos==-1)
		{
			TabProd[tlp].cod = auxCod;
			gotoxy(30,9);
			printf("Descricao do Produto: ");
			fflush(stdin);
			gets(TabProd[tlp].descr);
			gotoxy(30,10);
			printf("Quantidade em Estoque: ");
			scanf("%d",&TabProd[tlp].estoque);
			gotoxy(30,11);
			printf("Preco: ");
			scanf("%f",&TabProd[tlp].preco);
			gotoxy(30,12);
			printf("Data de Validade dd/mm/aa: ");
			scanf("%d",&TabProd[tlp].validade.dia);
			gotoxy(30,13);
			scanf("%d",&TabProd[tlp].validade.mes);
			gotoxy(30,14);
			scanf("%d",&TabProd[tlp].validade.ano);
			tlp++;
		}
		else
		{
			LimpaTela();
			gotoxy(13,23);
			printf("Produto Cadastrado!");
			gotoxy(30,9);
			printf("Produto[%d] - Descricao: [%s]",pos,TabProd[pos].descr);
			getch();
		}
		
		LimpaTela();
		gotoxy(30,6);
		printf("** Cadastro de Produtos **");
		if(tlp<TF)
		{
			gotoxy(30,8);
			printf("Codigo do Produto: ");
			scanf("%d",&auxCod);
		}
	}
	
	if(auxCod==0)//mostrando que nao pode
	{
		LimpaTela();
		gotoxy(13,23);
		printf("Codigo invalido");
		getch();
			
	}
	
	//Se caso a tabela já estiver cheia e o usario tentar cadastrar denovo
	if(tlp==TF)
	{
		LimpaTela();
		gotoxy(13,23);
		printf("Tabela cheia!");
		getch();//para voltar ao menu
	}
}

//Função que faz consulta do fornecedor atraves do codigo
void consultaForn(TpFornecedor tabForn[TF], int tlf)
{
	int auxCod, pos;
	
	LimpaTela();
	gotoxy(30,7);
	printf("*** Consulta de Fornecedor ***");
	
	gotoxy(30,9);
	printf("Digite o codigo para consulta: ");
	scanf("%d",&auxCod);
	
	pos = buscaForn(tabForn,tlf,auxCod);
	
	if(pos == -1)
	{
		LimpaTela(); 
		gotoxy(13,23);
		printf("Codigo nao encontrado");
		getch();
	}
	else
	{
		LimpaTela();
		gotoxy(30,8);
		printf("Codigo do fornecedor: %d",tabForn[pos].codForn);
		gotoxy(30,9);
		printf("Nome do fornecedor: %s",tabForn[pos].nomeForn);
		gotoxy(30,10);
		printf("Cidade do fornecedor: %d",tabForn[pos].cidade);
		gotoxy(30,11);
		getch();
		LimpaTela();
		
	}
	
}
//Função que faz consulta do produto atraves do codigo
void ConsultaProd(TpProdutos TabProd[TF], int tlp)
{
	int auxCod, pos;
	
	LimpaTela();
	gotoxy(30,7);
	printf("*** Consulta de produto ***");
	
	gotoxy(30,9);
	printf("Digite o codigo para consulta: ");
	scanf("%d",&auxCod);
	
	pos = buscaCod(TabProd,tlp,auxCod);
	
	if(pos == -1)
	{
		gotoxy(13,23);
		printf("O produto nao foi encontrado!");
		getch();
		LimpaTela();
	}
	else
	{
		LimpaTela();
		gotoxy(30,8);
		printf("Codigo do produto: %d",TabProd[pos].cod);
		gotoxy(30,9);
		printf("Descricao: %s",TabProd[pos].descr);
		gotoxy(30,10);
		printf("Estoque: %d",TabProd[pos].estoque);
		gotoxy(30,11);
		printf("Preco: %.2f",TabProd[pos].preco);
		gotoxy(30,12);
		printf("validade: %d/%d/%d",TabProd[pos].validade.dia,TabProd[pos].validade.mes,TabProd[pos].validade.ano);
		getch();
		LimpaTela();
	}
}

//Função da moldura
void moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
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

//Função com o menu principal
void menuPrincipal(void)
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

//Função que passa os valores da moldura
void Formulario(void)
{
	system("cls");
	moldura(1,1,80,25,10,5);
	gotoxy(27,3);
	textcolor(15);
	printf(" # # #  T I T U L O  # # #");
	
	moldura(2,2,79,4,14,1);
	moldura(2,5,27,21,12,7);
	menuPrincipal();
	moldura(2,22,79,24,11,4);
	gotoxy(4,23);
	textcolor(10);
	printf("Mensagem: ");

	moldura(28,5,79,21,9,6);
}

//Função do menu de opção para o usuario escolher
char menu(void)
{
	LimpaTela();
	gotoxy(30,6);
	printf("# # #  M E N U  # # #\n");
	gotoxy(30,8);
	printf("[A] Cadastrar Produtos");
	gotoxy(30,9);
	printf("[B] Consultar Produtos");
	gotoxy(30,10);
	printf("[C] Excluir Produtos");
	gotoxy(30,11);
	printf("[D] Alteracao de Dados");
	gotoxy(30,12);
	printf("[E] Relatorio de Produtos");
	gotoxy(30,13);
	printf("[F] Vender Produtos");
	gotoxy(30,14);
	printf("[G] Insercao dos dados");
	gotoxy(30,15);
	printf("[H] Aumento de preco por fornecedor");
	gotoxy(30,16);
	printf("[I] Exclusao de Vendas");
	gotoxy(30,17);
	printf("[J] Inserir dados");
	gotoxy(30,18);
	printf("[ESC] Sair\n");
	gotoxy(30,20);
	printf("Opcao desejada: ");
	return toupper(getche());
}

//Funçao do menu de fornecedor
char menuForn(void)
{
	LimpaTela();
	gotoxy(30,6);
	printf("# # #  M E N U  # # #\n");
	gotoxy(30,8);
	printf("[A] Cadastrar novo fornecedor");
	gotoxy(30,9);
	printf("[B] Consultar Fornecedores");
	gotoxy(30,10);
	printf("[C] Excluir fornecedores");
	gotoxy(30,11);
	printf("[D] Alteracao de Dados");
	gotoxy(30,12);
	printf("[E] Aumento de preco por fornecedor");
	gotoxy(30,13);
	printf("[F] Relatorio de dados");
	gotoxy(30,14);
	printf("[ESC] Sair\n");
	gotoxy(30,17);
	printf("Opcao desejada: ");
	return toupper(getche());
	
}

//Dados para teste
void Inseredados(TpProdutos TabProd[TF],int &TLP)
{
	TabProd[TLP].cod = 5000;
	strcpy(TabProd[TLP].descr,"Arroz");
	TabProd[TLP].estoque = 40;
	TabProd[TLP].preco = 35;
	TabProd[TLP].validade.dia = 19;
	TabProd[TLP].validade.mes = 8;
	TabProd[TLP].validade.ano = 2025;
	TLP++;
	
	TabProd[TLP].cod = 4000;
	strcpy(TabProd[TLP].descr,"Feijao");
	TabProd[TLP].estoque = 20;
	TabProd[TLP].preco = 15;
	TabProd[TLP].validade.dia = 15;
	TabProd[TLP].validade.mes = 8;
	TabProd[TLP].validade.ano = 2025;
	TLP++;
	
	TabProd[TLP].cod = 6000;
	strcpy(TabProd[TLP].descr,"Merda");
	TabProd[TLP].estoque = 10;
	TabProd[TLP].preco = 105;
	TabProd[TLP].validade.dia = 5;
	TabProd[TLP].validade.mes = 8;
	TabProd[TLP].validade.ano = 2023;
	TLP++;
	
	LimpaTela(); 
	gotoxy(13,23);
	printf("Dados inseridos");
	getch();
}

//Funcao que exclui o fornecedor
void excForn(TpFornecedor tabForn[TF],int &tlf)
{
	int  i,auxCod,pos;
	
	LimpaTela();
	gotoxy(30,7);
	printf("Exclusao");
	gotoxy(30,8);
	printf("Digite o codigo do fornecedor que deseja excluir");
	gotoxy(30,9);
	scanf("%d",&auxCod);
	
	pos=buscaForn(tabForn,tlf,auxCod);
	
	if(pos<0)//nao achou
	{
		LimpaTela(); 
		gotoxy(13,23);
		printf("Fornecedor nao cadastrado");
		getch();	
	}
	else
	{
		gotoxy(30,6);
		printf("*** Detalhes do Produto ***");
		gotoxy(30,7);
		printf("Codigo: %d",tabForn[pos].codForn);
		gotoxy(30,8);
		printf("Nome: %c",tabForn[pos].nomeForn);
		gotoxy(30,9);
		printf("cidade: %c",tabForn[pos].cidade);
		
		gotoxy(13,23);
		printf("Confirma Exclusao (S/N)? ");
		
			if (toupper(getche())=='S')
			{
				for( i=pos; i<tlf-1; i++)
					tabForn[i] = tabForn[i+1];
					
				tlf--;
				
				LimpaTela(); 
				gotoxy(13,23);
				printf("Produto deletado!");
				getch();
			}

	}
	
} 
//Funcao que exclui o produto
void excProd(TpProdutos TabProd[TF], int &TL)
{
	int j,l,auxCod,pos;
	
	LimpaTela();
	gotoxy(30,7);
	printf("Exclusao");
	gotoxy(30,8);
	printf("Digite o codigo do produto que deseja excluir");
	gotoxy(30,9);
	scanf("%d",&auxCod);
	
	pos=buscaCod(TabProd,TL,auxCod);
	
	if(pos<0)//nao achou
	{
		LimpaTela(); 
		gotoxy(13,23);
		printf("Produto nao cadastrado");
		getch();	
	}
	else //achou
	{
		gotoxy(30,6);
		printf("*** Detalhes do Produto ***");
		gotoxy(30,7);
		printf("Codigo: %d",TabProd[pos].cod);
		gotoxy(30,8);
		printf("Descricao: %s",TabProd[pos].descr);
		gotoxy(30,9);
		printf("Estoque: %d",TabProd[pos].estoque);
		gotoxy(30,10);
		printf("Preco: R$ %.2f",TabProd[pos].preco);
		gotoxy(30,11);
		printf("Data de Validade: %d/%d/%d",TabProd[pos].validade.dia, TabProd[pos].validade.mes, TabProd[pos].validade.ano);
		
		gotoxy(13,23);
		printf("Confirma Exclusao (S/N)? ");
		
			if (toupper(getche())=='S')
			{
				for( ; pos<TL-1; pos++)
					TabProd[pos] = TabProd[pos+1];
					
				TL--;
				
				LimpaTela(); 
				gotoxy(13,23);
				printf("Produto deletado!");
				getch();
			}

	}	
		
}



//Main onde o código vai começar
int main(void)
{
	//Declarando a struct de produto
	TpProdutos prod[TF];
	TpFornecedor forn[TF];
	
	int tl=0,tlf=0;
	char op;
	
	Formulario();
	
	do
	{
		//Repetição para que obrigue o usario a digitar uma das opções
		op = toupper(getch());
		while(op != 'P' && op != 'C' && op != 'F' && op != 27)
			op = toupper(getch());
		switch(op)
		{
			case 'P':
				op = menu();
				switch(op)
				{
					case 'A':
						cadProd(prod,tl);
						break;
				
					case 'B':
						ConsultaProd(prod,tl);
						break;
						
					case 'C':
						excProd(prod,tl);
						break;
						
					case 'J':
					Inseredados(prod,tl);
					break;
				
				}
				break;
			
			case 'F':
				op = menuForn();
				switch(op)
				{
					case 'A':
						cadFor(forn,tlf);
						break;
					case 'B':
						consultaForn(forn,tlf);
						break;
					case 'C':
						excForn(forn,tlf);
						break;
					case 'D':
						alteraForn(forn,tlf);
						break;
						
				}
				break;
				
			//Mensagem para quando o usario quiser sair do programa
			case 27:
				gotoxy(13,23);
				printf("Programa encerrado!");
				getch();
				break;
		}
	}while(op!=27);
	
	
	return 0;
}
