#include<stdio.h> // Biblioteca principal
#include<conio2.h> // Biblioteca para utilizar moldura
#include<string.h> // Biblioteca para manipulação de strings
#include<stdlib.h> // Biblioteca que converte string para numero
#include<ctype.h>

#define TF 100

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
	int cod, estoque, codForn;
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
	int qtdeCompra;
	char nomeCliente[30], cpf[11];
	float valorTotCompr;
	TpData data;
};

//Struct com as informações das vendas
struct TpVendas
{
	int codVenda; //CodVenda tem que ser sequencial
	float totVenda;
	char CPFCLI[11];
	TpData data;
	
};

//Struct com as informações das vendas dos produtos
struct TpVendaProd
{
	int codProd;
	int codVenda;
	int qtde;
	float valorUni;
};



//Funcao que valida cpf
int ValidaCPF(char CPF[11])
{
	 int vcpf[11], dig1, dig2, i, mult, soma=0, resto;
	 
	 for(i=0 ; i<11 ; i++)
		vcpf[i] = (CPF[i]-48);
		
	 for(i=0, mult=10 ; i<9 ; i++, mult--)//soma
		soma+=vcpf[i]*mult;
		
	 resto=soma%11;//pegando resto
	 dig1 = 11-resto;//descobrindo o primeiro digito
	 
	 if(dig1==11 || dig1==10)//se for 11 ou 10 o digito é 0
		dig1=0;
		
	 if(dig1==vcpf[9])//verifica se digito1 é valido
	 {
		  soma=0;
		  for(i=0, mult=11 ; i<10 ; i++, mult--)//repetindo para o digito2
		   soma+=vcpf[i]*mult;
		   
		  resto=soma%11;
		  dig2=11-resto;
		  
		  if(dig2==11 || dig2==10)
		   dig2=0;
		   
		  if(dig2==vcpf[10])//verifica se digito2 é valido
		   return 1;//verdadeiro(CPF VALIDO)
		   
		  else
		   return -1;//falso(CPF INVALIDO)
	 }
	 else
		return -1;//falso(CPF INVALIDO)
}

//Função que limpa a tela
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

//Função que Limpa Mensagem
void LimpaMensagem(void)
{
	int x,y;
	
	for(x=13;x<78;x++)
	 {
	 	gotoxy(x,23);
		printf("  ");
	 }
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

//Função que faz a busca da venda
int buscaVenda(TpVendas tabVenda[TF],int tlv, int aux)
{
	int pos=0;
	
	while(pos<tlv && aux!=tabVenda[pos].codVenda)
		pos++;
		
	if(pos<tlv)
		return pos;
	else
		return -1;
	
}

//Função que busca o codigo do fornecedor no produto
int buscaProdForn(TpProdutos TabProd[TF], int tlp, int auxCod, int &pos)
{	
	while(pos<tlp && auxCod!=TabProd[pos].codForn)
		pos++;
	
	if(pos<tlp)
		return pos;
	else
		return -1;
}

//Função que faz a busca pelo codigo do fornecedor
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

//Função que faz a busca pelo cpf do cliente
int buscaCpf(TpCliente TabCliente[TF], int tlc, char auxCpf[11])
{
	int pos=0;
	
	while(pos<tlc && strcmp(TabCliente[pos].cpf,auxCpf)!=0)
		pos++;
		
	if(pos<tlc)
		return pos;
	else
		return -1;
}

//Função que cadastra os dados do cliente
void cadCliente(TpCliente TabCliente[TF], int &tlc)
{
	int pos=0, busca=0;
	
	
	char auxCpf[11];
	
	LimpaTela();
	gotoxy(30,6);
	printf("*** Cadastrando cliente ***");
	gotoxy(30,8);
	printf("Digite o cpf: ");
	fflush(stdin);
	gets(auxCpf);
	
	ValidaCPF(auxCpf);
	
		while(auxCpf[0] != 48 && strlen(auxCpf) > 0)
		{
			if(ValidaCPF(auxCpf) == 1)
			{
				pos = buscaCpf(TabCliente,tlc,auxCpf);
				if(pos == -1)
				{
					strcpy(TabCliente[tlc].cpf,auxCpf);
						
					gotoxy(30,9);
					printf("Nome do cliente: ");
					fflush(stdin);
					gets(TabCliente[tlc].nomeCliente);
					tlc++;
						
					LimpaTela();
					gotoxy(13,23);
					printf("Cliente cadastrado com sucesso!");
					getch();
				}
				else
				{
					LimpaTela();
					gotoxy(13,23);
					printf("Cpf ja existente!");
					getch();
				}
				
			}
			else
			{
				gotoxy(13,23);
				printf("Cpf invalido!");
				getch();
			}
			LimpaTela();
			gotoxy(30,6);
			printf("*** Cadastrando cliente ***");
			gotoxy(30,8);
			printf("Digite o cpf: ");
			fflush(stdin);
			gets(auxCpf);
		}
		if(strlen(auxCpf) == 0)
		{
			gotoxy(13,23);
			printf("Nao pode cSpf nulo!");
			getch();	
		}
		LimpaTela();
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

//Função que faz a consulta do cliente atraves do cpf
void ConsultaCliente(TpCliente TabCliente[TF], int tlc)
{
	int pos;
	
	char auxCpf[11];
	
	LimpaTela();
	gotoxy(30,6);
	printf("*** Consulta de cliente ***");
	
	gotoxy(30,8);
	printf("Digite o cpf do cliente: ");
	fflush(stdin);
	gets(auxCpf);
	
	pos = buscaCpf(TabCliente,tlc,auxCpf);
	
	if(pos == -1)
	{
		gotoxy(13,23);
		printf("O cliente nao foi encontrado!");
		getch();
		LimpaTela();
	}
	else
	{
		LimpaTela();
		gotoxy(30,8);
		printf("Cpf do cliente: %s",TabCliente[pos].cpf);
		gotoxy(30,9);
		printf("Nome do cliente: %s",TabCliente[pos].nomeCliente);
		/*
		gotoxy(30,10);
		printf("Quatidade de compras do cliente: %d",TabCliente[pos].qtdeCompra);
		gotoxy(30,11);
		printf("Valor total comprado: %.2f",TabCliente[pos].valorTotCompr);
		*/
		getch();
		LimpaTela();
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
		printf("Cidade do fornecedor: %s",tabForn[pos].cidade);
		gotoxy(30,11);
		getch();
		LimpaTela();
		
	}
	
}

//Função que cadastra o produto
void cadProd(TpProdutos TabProd[TF], int &tlp, TpFornecedor TabForn[TF], int tlf)
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
			gotoxy(30,15);
			printf("Digite o codigo do fornecedor");
			scanf("%d",&auxCod);
			pos = buscaForn(TabForn,tlf,auxCod);			
			if(pos>0)
				TabProd[tlp].codForn=auxCod;
			else
			{
				LimpaTela();
				gotoxy(13,23);
				printf("Fornecedor nao encontrado");
				/*slepy(5);*/
				cadFor(TabForn,tlf);
			}
			
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

//Função que faz consulta do produto atraves do codigo
void ConsultaProd(TpProdutos TabProd[TF], int tlp)
{
	int auxCod, pos;
	
	LimpaTela();
	gotoxy(30,6);
	printf("*** Consulta de produto ***");
	
	gotoxy(30,8);
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
	textcolor(12);
	textbackground(3);
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
	printf(" # # #  MERCADO DO LUDIMILO  # # #");
	
	moldura(2,2,79,4,14,1);
	moldura(2,5,27,21,12,7);
	menuPrincipal();
	moldura(2,22,79,24,11,4);
	gotoxy(4,23);
	textcolor(12);
	printf("Mensagem: ");

	moldura(28,5,79,21,9,6);
}

//Função do menu de opção para o usuario escolher (PRODUTOS)
char menuProd(void)
{
	LimpaTela();
	gotoxy(30,6);
	printf("# # #  M E N U  P R O D U T O S  # # #\n");
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
	printf("[F] Relatorio de vendas");
	gotoxy(30,14);
	printf("[G] Vender Produtos");
	gotoxy(30,15);
	printf("[H] Insercao de estoque");
	gotoxy(30,16);
	printf("[I] Inserir dados");
	gotoxy(30,17);
	printf("[J] Exclusao de Vendas");
	gotoxy(30,18);
	printf("[0] Sair\n");
	gotoxy(30,20);
	printf("Opcao desejada: ");
	return toupper(getch());
}

//Função do menu de opção para o usuario escolher (CLIENTES)
char menuCliente(void)
{
	LimpaTela();
	gotoxy(30,6);
	printf("# # #  M E N U  C L I E N T E S  # # #\n");
	gotoxy(30,8);
	printf("[A] Cadastrar Cliente");
	gotoxy(30,9);
	printf("[B] Consultar Cliente pelo cpf");
	gotoxy(30,10);
	printf("[C] Excluir cliente");
	gotoxy(30,11);
	printf("[D] Alteracao de Dados");
	gotoxy(30,12);
	printf("[E] Relatorio de clientes");
	gotoxy(30,13);
	printf("[F] Insere dados");
	gotoxy(30,14);
	printf("[0] Sair\n");
	gotoxy(30,16);
	printf("Opcao desejada: ");
	return toupper(getche());
}

//Funçao do menu de fornecedor
char menuForn(void)
{
	LimpaTela();
	gotoxy(30,6);
	printf("# # #  M E N U  F O R N E C E D O R  # # #\n");
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
	printf("[G] Insere dados");
	gotoxy(30,15);
	printf("[0] Sair\n");
	gotoxy(30,17);
	printf("Opcao desejada: ");
	return toupper(getche());
	
}

//Dados para teste
void Inseredados(TpProdutos TabProd[TF], TpFornecedor TabForn[TF], TpCliente TabCliente[TF],int &TLP, int &tlf, int &tlc)
{
	LimpaTela();
	
	//Inserindo na tabela produtos
	TabProd[TLP].cod = 1000;
	strcpy(TabProd[TLP].descr,"Arroz");
	TabProd[TLP].estoque = 40;
	TabProd[TLP].preco = 35;
	TabProd[TLP].validade.dia = 19;
	TabProd[TLP].validade.mes = 8;
	TabProd[TLP].validade.ano = 2025;
	TabProd[TLP].codForn = 1111;
	TLP++;
	
	TabProd[TLP].cod = 2000;
	strcpy(TabProd[TLP].descr,"Feijao");
	TabProd[TLP].estoque = 20;
	TabProd[TLP].preco = 15;
	TabProd[TLP].validade.dia = 15;
	TabProd[TLP].validade.mes = 8;
	TabProd[TLP].validade.ano = 2025;
	TabProd[TLP].codForn = 1111;
	TLP++;
	
	TabProd[TLP].cod = 3000;
	strcpy(TabProd[TLP].descr,"Milho");
	TabProd[TLP].estoque = 10;
	TabProd[TLP].preco = 105;
	TabProd[TLP].validade.dia = 5;
	TabProd[TLP].validade.mes = 8;
	TabProd[TLP].validade.ano = 2023;
	TabProd[TLP].codForn = 2222;
	TLP++;
	
	TabProd[TLP].cod = 4000;
	strcpy(TabProd[TLP].descr,"Oleo");
	TabProd[TLP].estoque = 20;
	TabProd[TLP].preco = 28;
	TabProd[TLP].validade.dia = 8;
	TabProd[TLP].validade.mes = 11;
	TabProd[TLP].validade.ano = 2025;
	TabProd[TLP].codForn = 3333;
	TLP++;
	
	TabProd[TLP].cod = 5000;
	strcpy(TabProd[TLP].descr,"Farinha");
	TabProd[TLP].estoque = 11;
	TabProd[TLP].preco = 42;
	TabProd[TLP].validade.dia = 21;
	TabProd[TLP].validade.mes = 9;
	TabProd[TLP].validade.ano = 2025;
	TabProd[TLP].codForn = 2222;
	TLP++;
	
	//Inserindo na tabela Clientes
	strcpy(TabCliente[tlc].cpf,"35733261889");
	strcpy(TabCliente[tlc].nomeCliente,"Guilherme");
	tlc++;
	
	strcpy(TabCliente[tlc].cpf,"42328232043");
	strcpy(TabCliente[tlc].nomeCliente,"Joao");
	tlc++;
	
	strcpy(TabCliente[tlc].cpf,"16199795008");
	strcpy(TabCliente[tlc].nomeCliente,"Leandro");
	tlc++;
	
	strcpy(TabCliente[tlc].cpf,"06366226067");
	strcpy(TabCliente[tlc].nomeCliente,"Gustavo");
	tlc++;
	
	strcpy(TabCliente[tlc].cpf,"40190176032");
	strcpy(TabCliente[tlc].nomeCliente,"Mateus");
	tlc++;
	
	strcpy(TabCliente[tlc].cpf,"01979684065");
	strcpy(TabCliente[tlc].nomeCliente,"Vinicius");
	tlc++;
	
	//Inserindo na tebela de fornecedor
	TabForn[tlf].codForn = 1111;
	strcpy(TabForn[tlf].cidade,"Venceslau");
	strcpy(TabForn[tlf].nomeForn,"Ludimilo");
	tlf++;
	
	TabForn[tlf].codForn = 2222;
	strcpy(TabForn[tlf].cidade,"Bernardes");
	strcpy(TabForn[tlf].nomeForn,"Vidoco");
	tlf++;
	
	TabForn[tlf].codForn = 3333;
	strcpy(TabForn[tlf].cidade,"Prudente");
	strcpy(TabForn[tlf].nomeForn,"Cnpjoto");
	tlf++;
	
	TabForn[tlf].codForn = 4444;
	strcpy(TabForn[tlf].cidade,"Machado");
	strcpy(TabForn[tlf].nomeForn,"Tilapio");
	tlf++;
	
	TabForn[tlf].codForn = 5555;
	strcpy(TabForn[tlf].cidade,"Anastacio");
	strcpy(TabForn[tlf].nomeForn,"Netflixo");
	tlf++;
	
	
	gotoxy(13,23);
	printf("Dados inseridos com sucesso!");
	getch();
	LimpaTela();
}

//Função que exclui cliente
void excCliente(TpCliente TabCliente[TF], int &tlc)
{
	int i, j, pos;
	
	char auxCpf[11];
	
	LimpaTela();
	
	if(tlc == 0)
	{
		gotoxy(13,23);
		printf("Nao tem clientes cadastrado!");
		getch();
	}
	else
	{
		gotoxy(30,6);
		printf("*** Exclusao de cliente ***");
		gotoxy(30,8);
		printf("Digite o cpf do cliente que deseja excluir: ");
		fflush(stdin);
		gotoxy(30,9);
		gets(auxCpf);
		
		pos = buscaCpf(TabCliente,tlc,auxCpf);
		
		if(pos == -1) //Não achou o cpf
		{
			LimpaTela();
			gotoxy(13,23);
			printf("Cliente nao cadastrado");
			getch();
		}
		else //Achou
		{
			LimpaTela();
			gotoxy(30,6);
			printf("*** Detalhes do cliente ***");
			gotoxy(30,8);
			printf("Cpf do cliente: %s",TabCliente[pos].cpf);
			gotoxy(30,9);
			printf("Nome do cliente: %s",TabCliente[pos].nomeCliente);
			/*
			gotoxy(30,10);
			printf("Quantidade de compras do cliente: %d",TabCliente[pos].qtdeCompra);
			gotoxy(30,11);
			printf("Valor total comprado: %.2f",TabCliente[pos].valorTotCompr);
			*/
			
			gotoxy(13,23);
			printf("Confirma a exclusao?(S/N) ");
			
			if(toupper(getche()) == 'S')
			{
				for( ; pos<tlc-1; pos++)
					TabCliente[pos] = TabCliente[pos+1];
					
				tlc--;
					
				LimpaTela();
				gotoxy(13,23);
				printf("Cliente excluido com sucesso!");
				getch();
			}
			else
			{
				LimpaTela();
				gotoxy(13,23);
				printf("Voce nao autorizou a exclusao!");
				getch();
			}
		}
	}
	LimpaTela();
}

//Funcao que exclui o fornecedor
void excForn(TpFornecedor tabForn[TF],int &tlf)
{
	int  i,auxCod,pos;
	
	LimpaTela();
	if(tlf == 0)
	{
		gotoxy(13,23);
		printf("Nao tem fornecedores cadastrado!");
		getch();
	}
	else
	{
		gotoxy(30,6);
		printf("*** Exclusao do fornecedor ***");
		gotoxy(30,8);
		printf("Codigo do fornecedor que deseja excluir: ");
		gotoxy(30,9);
		scanf("%d",&auxCod);
		
		pos=buscaForn(tabForn,tlf,auxCod);
		
		if(pos<0)//nao achou
		{
			LimpaTela(); 
			gotoxy(13,23);
			printf("Fornecedor nao cadastrado!");
			getch();	
		}
		else
		{
			LimpaTela();
			gotoxy(30,6);
			printf("*** Detalhes do Fornecedor ***");
			gotoxy(30,7);
			printf("Codigo: %d",tabForn[pos].codForn);
			gotoxy(30,8);
			printf("Nome: %s",tabForn[pos].nomeForn);
			gotoxy(30,9);
			printf("cidade: %sf",tabForn[pos].cidade);
			
			gotoxy(13,23);
			printf("Confirma Exclusao (S/N)? ");
			
				if (toupper(getche())=='S')
				{
					for( i=pos; i<tlf-1; i++)
						tabForn[i] = tabForn[i+1];
						
					tlf--;
					
					LimpaTela(); 
					gotoxy(13,23);
					printf("Fornecdor excluido com sucesso!");
					getch();
				}
				else
				{
					LimpaTela();
					gotoxy(13,23);
					printf("Voce nao autorizou a exclusao!");
					getch();
				}
	
		}
	}
	LimpaTela();	
} 

//Funcao que exclui o produto
void excProd(TpProdutos TabProd[TF], int &TL)
{
	int j,l,auxCod,pos;
	
	LimpaTela();
	if(TL == 0)
	{
		gotoxy(13,23);
		printf("Nao tem produtos cadastrado!");
		getch();
	}
	else
	{
		gotoxy(30,6);
		printf("*** Exclusao de produto ***");
		gotoxy(30,8);
		printf("Digite o codigo do produto que deseja excluir: ");
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
			LimpaTela();
			gotoxy(30,6);
			printf("*** Detalhes do Produto ***");
			gotoxy(30,8);
			printf("Codigo: %d",TabProd[pos].cod);
			gotoxy(30,9);
			printf("Descricao: %s",TabProd[pos].descr);
			gotoxy(30,10);
			printf("Estoque: %d",TabProd[pos].estoque);
			gotoxy(30,11);
			printf("Preco: R$ %.2f",TabProd[pos].preco);
			gotoxy(30,12);
			printf("Data de Validade: %d/%d/%d",TabProd[pos].validade.dia, TabProd[pos].validade.mes, TabProd[pos].validade.ano);
			
			gotoxy(13,23);
			printf("Confirma Exclusao?(S/N) ");
			
				if(toupper(getche())=='S')
				{
					for( ; pos<TL-1; pos++)
						TabProd[pos] = TabProd[pos+1];
						
					TL--;
					
					LimpaTela(); 
					gotoxy(13,23);
					printf("Produto excluido com sucesso!");
					getch();
				}
				else
				{
					LimpaTela();
					gotoxy(13,23);
					printf("Voce nao autorizou a exclusao!");
					getch();
				}
		}
	}
	LimpaTela();
		
}

//Função que altera os dados dos clientes
void alteraCliente(TpCliente TabCliente[TF], int tlc)
{
	int pos, resp;
	
	char auxNome[30], auxCpf[11];
	
	LimpaTela();
	gotoxy(30,6);
	printf("*** Alteracao de dados do cliente ***");
	gotoxy(30,8);
	printf("Digite o cpf do cliente: ");
	fflush(stdin);
	gotoxy(30,9);
	gets(auxCpf);
	
	pos = buscaCpf(TabCliente,tlc,auxCpf);
	
	if(pos == -1) //Não achou
	{
		LimpaTela();
		gotoxy(13,23);
		printf("Cliente nao encontrado!");
		getch();
	}
	else
	{
		LimpaTela();
		gotoxy(30,6);
		printf("*** Alteracao de dados do cliente ***");
		gotoxy(30,8);
		printf("Digite a opcao desejada: ");
		gotoxy(30,9);
		printf("1 - CPF");
		gotoxy(30,10);
		printf("2 - Nome");
		gotoxy(30,11);
		scanf("%d",&resp);
		
		if(resp == 1)
		{
			LimpaTela();
			gotoxy(30,6);
			printf("Digite o novo cpf para ser alterado: ");
			fflush(stdin);
			gotoxy(30,7);
			gets(auxCpf);
			
			if(buscaCpf(TabCliente,tlc,auxCpf) == -1)
			{
				strcpy(TabCliente[pos].cpf,auxCpf);
				
				gotoxy(13,23);
				printf("Alteracao feita com sucesso!");
				getch();
			}
			else
			{
				LimpaTela();
				gotoxy(13,23);
				printf("Esse cpf ja foi cadastrado");
				getch();
			}
		}
		else
		if(resp == 2)
		{
			LimpaTela();
			gotoxy(30,6);
			printf("Digite um novo nome para ser alterado: ");
			fflush(stdin);
			gotoxy(30,7);
			gets(auxNome);
			
			strcpy(TabCliente[pos].nomeCliente,auxNome);
			
			gotoxy(13,23);
			printf("Alteracao feita com sucesso!");
			getch();
		}
		else
		{
			LimpaTela();
			gotoxy(13,23);
			printf("Nao tem essa opcao!");
			getch();
		}
	}
	LimpaTela();
}

//Função que altera os dados dos produtos
void alteraProd(TpProdutos TabProd[TF], int tlp)
{
	int pos, resp, auxCod, auxDia, auxMes, auxAno;
	
	char auxDescr[30];
	
	float auxPreco;
	
	LimpaTela();
	gotoxy(30,6);
	printf("*** Alteracao de dados dos produtos ***");
	gotoxy(30,8);
	printf("Digite o codigo do produto: ");
	scanf("%d",&auxCod);
	
	pos = buscaCod(TabProd,tlp,auxCod);
	
	if(resp == -1)
	{
		gotoxy(13,23);
		printf("Codigo do produto nao encontrado!");
		getch();
	}
	else
	{
		LimpaTela();
		gotoxy(30,6);
		printf("*** Alteracao de dados dos produtos ***");
		gotoxy(30,8);
		printf("Digite a opcao desejada: ");
		gotoxy(30,9);
		printf("1 - Codigo");
		gotoxy(30,10);
		printf("2 - Descricao");
		gotoxy(30,11);
		printf("3 - Estoque");
		gotoxy(30,12);
		printf("4 - Preco");
		gotoxy(30,13);
		printf("5 - Data de validade");
		gotoxy(30,14);
		scanf("%d",&resp);
		
		if(resp == 1)
		{
			LimpaTela();
			gotoxy(30,6);
			printf("Digite o novo codigo para ser alterado: ");
			gotoxy(30,7);
			scanf("%d",&auxCod);
			
			if(buscaCod(TabProd,tlp,auxCod) == -1)
			{
				TabProd[pos].cod = auxCod; 
				
				gotoxy(13,23);
				printf("Alteracao feita com sucesso!");
				getch();
			}
				
			else
			{
				gotoxy(13,23);
				printf("Esse codigo ja foi cadastrado!");
				getch();
			}
		}
		else
		if(resp == 2)
		{
			LimpaTela();
			gotoxy(30,6);
			printf("Digite a nova descricao do produto: ");
			fflush(stdin);
			gotoxy(30,7);
			gets(auxDescr);
			
			strcpy(TabProd[pos].descr,auxDescr);
			
			gotoxy(13,23);
			printf("Alteracao feita com sucesso!");
			getch();
		}
		else
		if(resp == 3)
		{
			LimpaTela();
			gotoxy(30,6);
			printf("Digite a nova quantidade de estoque: ");
			gotoxy(30,7);
			scanf("%d",&auxCod);
			
			TabProd[pos].estoque = auxCod;
			
			gotoxy(13,23);
			printf("Alteracao feita com sucesso!");
			getch();
		}
		else
		if(resp == 4)
		{
			LimpaTela();
			gotoxy(30,6);
			printf("Digite o novo preco do produto: ");
			gotoxy(30,7);
			scanf("%f",&auxPreco);
			
			TabProd[pos].preco = auxPreco;
			
			gotoxy(13,23);
			printf("Alteracao feita com sucesso!");
			getch();
		}
		else
		if(resp == 5)
		{
			LimpaTela();
			gotoxy(30,6);
			printf("Digite a nova data e validade xx/xx/xxxx: ");
			gotoxy(30,7);
			printf("Dia: ");
			scanf("%d",&auxDia);
			gotoxy(30,8);
			printf("Mes: ");
			scanf("%d",&auxMes);
			gotoxy(30,9);
			printf("Ano: ");
			scanf("%d",&auxAno);
			
			TabProd[pos].validade.dia = auxDia;
			TabProd[pos].validade.mes = auxMes;
			TabProd[pos].validade.ano = auxAno;
			
			gotoxy(13,23);
			printf("Alteracao feita com sucesso!");
			getch();
		}
		else
		{
			LimpaTela();
			gotoxy(13,23);
			printf("Nao tem essa opcao!");
			getch();
		}
	}
	LimpaTela();
}

//Funcao que altera os dados do fornecedor
void alteraForn(TpFornecedor tabForn[TF], int tlf)
{
    int pos,resp;
    
    char auxNome[30];
    
    LimpaTela();

    gotoxy(30,6);
    printf("*** Alteracao de dados ***");
    gotoxy(30,8);
    printf("Digite o codigo do forncedor: ");
    scanf("%d",&resp);


    pos = buscaForn(tabForn,tlf,resp);

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
        switch(getch())
        {
            case 1:
                LimpaTela();
                gotoxy(30,6);
                printf("Digite novo codigo para ser alterado: ");
                gotoxy(30,7);
                scanf("%d",&resp);
                tabForn[pos].codForn=resp;
                
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

//Função que faz relatorio dos clientes
void relatorioForn(TpFornecedor tabForn[TF], int tlf)
{
	 int i=9, pos=0;
	 LimpaTela();
	 gotoxy(30,6);
	 printf("*** Relatorio de fornecedor ***");
	 if(tlf == 0)
	 {
	 	gotoxy(13,23);
	 	printf("Nao tem forncedor cadastrado!");
	 	getch();
	 }
	 else
	 {
		while(pos<tlf)
		{
			gotoxy(30,8);
			printf("CODIGO");
			gotoxy(30,i);
			printf("%d",tabForn[pos].codForn);
			gotoxy(43,8);
			printf("NOME");
			gotoxy(43,i);
			puts(tabForn[pos].nomeForn);
			gotoxy(56,8);
			printf("CIDADE");
			gotoxy(56,i);
			puts(tabForn[pos].cidade);
			i = i + 2;
			/*
			gotoxy(30,i);
			printf("Quantide de compras: %d",TabCliente[pos].qtdeCompra);
			gotoxy(30,i);
			printf("Valor total comprado: %.2f",TabCliente[pos].valorTotCompr);
			*/
			pos++;
			if(i==20)
			{
			   getch();
			   LimpaTela();
			   gotoxy(30,6);
			   printf("* Relatorio de Clientes *");
			   i=9;
			}
			
			if(pos==tlf)
			{
				gotoxy(13,23);
				printf("Relatorio finalizado!");
				getch();
			}	
		 }
	 }
	LimpaTela();
}

//Função que faz o relatorio de produtos
void relatorioProd(TpProdutos TabProd[TF], int tlp)
{
	int pos=0, i=9;
	
	LimpaTela();
	gotoxy(30,6);
	printf("*** Relatorio de produtos ***");
	
	if(tlp == 0)
	{
		gotoxy(13,23);
		printf("Nao tem produtos cadastrados!");
		getch();
	}
	else
	{
		while(pos<tlp)
		{
			gotoxy(30,8);
			printf("COD.");
			gotoxy(30,i);
			printf("%d",TabProd[pos].cod);
			gotoxy(38,8);
			printf("DESCR.");
			gotoxy(38,i);
			puts(TabProd[pos].descr);
			gotoxy(48,8);
			printf("ETQ.");
			gotoxy(48,i);
			printf("%d",TabProd[pos].estoque);
			gotoxy(56,8);
			printf("PRECO");
			gotoxy(56,i);
			printf("%.2f",TabProd[pos].preco);
			gotoxy(65,8);
			printf("VALIDADE");
			gotoxy(65,i);
			printf("%d/%d/%d",TabProd[pos].validade.dia,TabProd[pos].validade.mes,TabProd[pos].validade.ano);
			
			i = i + 2;
			pos++;
			
			if(i>=20)
			{
				getch();
				LimpaTela();
				gotoxy(30,6);
				printf("*** Relatorio de Produtos ***");
				i=9;
			}
			
			if(pos == tlp)
			{
				gotoxy(13,23);
				printf("Relatorio finalizado!");
				getch();
			}
			
		}
	}
	
	LimpaTela();
}


//Função que faz o relatorio de clientes
void relatorioCliente(TpCliente TabCliente[TF], int tlc, int tlv)
{
	int pos=0, i=8;
	
	LimpaTela();
	gotoxy(30,6);
	printf("*** Relatorio de Clientes ***");
	
	if(tlc == 0)
	{
		gotoxy(13,23);
		printf("Nao tem clientes cadastrado!");
		getch();
	}
	else
	{
		while(pos<tlc)
		{
			gotoxy(30,i);
			printf("CPF: %s",TabCliente[pos].cpf);
			i++;
			gotoxy(30,i);
			printf("NOME: %s",TabCliente[pos].nomeCliente);
			if(pos<tlv)
			{	
				i++;
				gotoxy(30,i);
				printf("QTDE COMPRAS: %d",TabCliente[pos].qtdeCompra);
				i++;
				gotoxy(30,i);
				printf("VALOR TOTAL COMPRADO: %.2f",TabCliente[pos].valorTotCompr);
			}
			else
			{
				i++;
				gotoxy(30,i);
				printf("QTDE COMPRAS: 0");
				i++;
				gotoxy(30,i);
				printf("VALOR TOTAL COMPRADO: 0");
			}
			i = i + 2;
			gotoxy(30,i);
			printf("---------------------------------------");
			i = i + 2;
			pos++;
			
			if(i>=18)
			{
				gotoxy(13,23);
				printf("Aperte enter para aparecer o restante do relatorio");
				getch();
				LimpaTela();
				gotoxy(30,6);
				printf("*** Relatorio de Clientes ***");
				i=8;
			}
			
			if(pos==tlc)
			{
				gotoxy(13,23);
				printf("Relatorio finalizado!");
				getch();
			}	
		}
	}
	LimpaTela();
}

//Função que vai fazer a inserção de produtos
void insercaoProd(TpProdutos TabProd[TF], int &tlp)
{
	int pos, auxCod, auxEst;
	
	LimpaTela();
	
	gotoxy(30,6);
	printf("*** Insercao de dados ***");
	
	gotoxy(30,8);
	printf("Digite o codigo que deseja: ");
	gotoxy(30,9);
	scanf("%d",&auxCod);
	
	pos = buscaCod(TabProd,tlp,auxCod);
	
	if(pos == -1)
	{
		gotoxy(13,23);
		printf("Produto nao foi encontrado!");
		getch();
	}
	else
	{
		gotoxy(30,11);
		printf("Estoque atual: %d",TabProd[pos].estoque);
		gotoxy(30,13);
		printf("Quantidade que deseja aumentar do estoque:");
		gotoxy(30,14);
		scanf("%d",&auxEst);
		
		TabProd[pos].estoque = TabProd[pos].estoque + auxEst;
		
		gotoxy(30,16);
		printf("Estoque apos a insercao: %d",TabProd[pos].estoque);
		
		gotoxy(13,23);
		printf("Insercao de estoque realizada com sucesso!");
		getch();
	}
	
	LimpaTela();
}

//Função que faz o aumento dos preços dos fornecedor
void aumentaForn(TpFornecedor TabForn[TF], TpProdutos TabProd[TF], int tlf, int tlp)
{
	int posF, posP, auxForn, porc, valor, i, posaux, pos=11;
	
	LimpaTela();
	
	gotoxy(30,6);
	printf("*** Alteracao de preco por fornecedor ***");
	
	gotoxy(30,8);
	printf("Digite o codigo do fornecedor: ");
	gotoxy(30,9);
	scanf("%d",&auxForn);
	
	posF = buscaForn(TabForn,tlf,auxForn);
	
	if(posF == -1) //nao achou
	{
		gotoxy(13,23);
		printf("Fornecedor nao cadastrado!");
		getch();
	}
	else
	{
		gotoxy(13,23);
		printf("Fornecedor encontrado!");
		
		gotoxy(30,pos);
		printf("Qual a porcentagem que deseja aumentar: ");
		pos++;
		gotoxy(30,pos);
		scanf("%d",&porc);
		
		i=0;
		while(i<tlp)
		{
			posaux = TabProd[i].codForn;
			if(posaux == auxForn)
			{
				
				LimpaMensagem();
				
				pos = pos + 2;
				gotoxy(30,pos);
				printf("Produto: %d",TabProd[i].cod);
				pos++;
				gotoxy(30,pos);
				printf("Descricao: %s",TabProd[i].descr);
				pos++;
				gotoxy(30,pos);
				printf("Preco antes do aumento: %.2f",TabProd[i].preco);
				
				TabProd[i].preco = TabProd[i].preco * porc / 100 + TabProd[i].preco;
				
				pos++;
				gotoxy(30,pos);
				printf("Preco apos o aumento: %.2f",TabProd[i].preco);
				
				
				if(pos == 17)
				{
					LimpaMensagem();
					gotoxy(13,23);
					printf("Pressione enter para continuar aumentando!");
					getch();
					LimpaTela();
					gotoxy(30,6);
					printf("*** Alteracao de preco por fornecedor ***");
					pos=11;		
				}
				
			}
			
			i++;		
		}
		
		LimpaMensagem();
		gotoxy(13,23);
		printf("Valores atualizados!");
		getch();	
	}
	LimpaTela();
}

//Funçao que faz as vendas
   void Venderprod(TpVendas tabVenda[TF], int &tlv,TpProdutos tabProd[TF], int tlp,TpCliente cliente[TF],int tlc,TpVendaProd tabVendaP[TF], int &tlvp, TpFornecedor tabForn[TF], int tlf, int &p)
{
	int	auxCod, pos, qtda, posc, posf, i, l=10, somaQtde=0;
	
	float valort;
	
	char auxCpf[11], op;
	
	LimpaTela();
	
	gotoxy(30,6);
	printf("*** Vender produtos ***");

	
	gotoxy(30,8);
	printf("Digite o cpf do cliente: ");
	fflush(stdin);
	gets(auxCpf);
	posc = buscaCpf(cliente,tlc,auxCpf);
	if(strcmp(cliente[posc].cpf,auxCpf) == 0)
	{
		LimpaMensagem();
		gotoxy(13,23);
		printf("Cpf Valido!");
		getch();
		
		gotoxy(13,23);
		printf("Digite 0 para encerrar!");
		gotoxy(30,8);//entra lido
		printf("Digite o codigo do Produto para ser vendido: ");
		gotoxy(30,9);
		scanf("%d",&auxCod);
		while(auxCod>0)
		{
			pos = buscaCod(tabProd,tlp,auxCod);
			if(pos==-1) //chamar a funçao de cadastro de produto caso nao exista (sim ou nao)
			{	
				LimpaMensagem(); 
				gotoxy(13,23);
				printf("Produto nao cadastrado!");
				getch();
				LimpaTela();
			}
			else
			{
				LimpaTela();
				gotoxy(13,23);
				printf("Produto encontrado!");
				gotoxy(30,7);
				printf("*** Venda de produto ***");
				gotoxy(30,9);
				printf("Preco unitario do produto: %.2f",tabProd[pos].preco);
				gotoxy(30,10);
				printf("Quantidade atual deste produto: %d",tabProd[pos].estoque);
				gotoxy(30,11);
				printf("Digite a quantidade que deseja comprar: ");	
				gotoxy(30,12);  
				scanf("%d",&qtda);
				 
				if(qtda>tabProd[pos].estoque)
				{
					LimpaMensagem();
					gotoxy(13,23);
					printf("Estoque insuficiente!");
					getch();	
				}
				else
				{
					strcpy(tabVenda[tlv].CPFCLI,cliente[posc].cpf);
					tabVenda[tlv].codVenda=tlv+1;
					
					valort=tabProd[pos].preco * qtda;
					gotoxy(30,14);
					printf("Valor total da venda: %.2f",valort);
					
					LimpaMensagem();
					gotoxy(13,23);
					printf("Deseja finalizar a venda? (S/N)");
					op = toupper(getch());
					
					if(op == 'S')
					{
						tabVendaP[tlvp].codVenda = tlv+1;
						tabVendaP[tlvp].codProd = auxCod;
						tabVendaP[tlvp].qtde = qtda;
						tabVendaP[tlvp].valorUni = valort;
						
						tabProd[pos].estoque = tabProd[pos].estoque - qtda;
						
						tabVenda[tlv].totVenda=valort + tabVenda[tlv].totVenda;
						
						somaQtde = somaQtde + qtda;
						//cliente[tlv].valorTotCompr =valort + cliente[tlv].valorTotCompr;
						
						tlvp++;
						
						LimpaMensagem();
						gotoxy(13,23);
						printf("Venda feita com sucesso!");
						getch();	
					}
					else
					{
						LimpaMensagem();
						gotoxy(13,23);
						printf("Venda finalizada!");
						getch();
					}			
				}	
			}
			LimpaTela();
			
			gotoxy(30,6);
			printf("*** Vender produtos ***");
			
			gotoxy(13,23);
			printf("Digite 0 para encerrar!");
			gotoxy(30,8);//entra lido
			printf("Digite o codigo do Produto para ser vendido: ");
			gotoxy(30,9);
			scanf("%d",&auxCod);
		}
		
		pos = buscaCod(tabProd,tlp,auxCod);
		
		if(tlvp>0 && op == 'S')
		{
			
		
			gotoxy(30,11);
			printf("Data da venda dd/mm/aa: ");
			scanf("%d",&tabVenda[tlv].data.dia);
			gotoxy(30,12);
			scanf("%d",&tabVenda[tlv].data.mes);
			gotoxy(30,13);
			scanf("%d",&tabVenda[tlv].data.ano);
			
			LimpaMensagem();
			gotoxy(13,23);
			printf("Aperte enter para emitir a nota fiscal!");
			getch();
			
			LimpaTela();
			gotoxy(30,6);
			printf("*** Nota Fiscal ***");
			gotoxy(30,8);
			printf("Codigo da venda: %d",tlv+1);
			gotoxy(30,9);
			printf("DADOS DA VENDA:");
			
			l=10;
			gotoxy(30,l);
			printf("COD.");
			gotoxy(37,l);
			printf("DESCR.");
			gotoxy(47,l);
			printf("QTDE.");
			gotoxy(55,l);
			printf("PRECO");
			gotoxy(68,l);
			printf("NOME FORN.");
			l++;
			for(; p<tlvp; p++)
			{
				pos = buscaCod(tabProd,tlp,tabVendaP[p].codProd);
				posf = buscaForn(tabForn,tlf,tabProd[pos].codForn);
				gotoxy(30,l);
				printf("%d",tabVendaP[p].codProd);
				gotoxy(37,l);
				printf("%s",tabProd[pos].descr);
				gotoxy(48,l);
				printf("%d",tabVendaP[p].qtde);
				gotoxy(55,l);
				printf("R$%.2f",tabVendaP[p].valorUni);
				gotoxy(68,l);
				printf("%s",tabForn[posf].nomeForn);
				l++;
				if(l>=21)
				{
					if(p==tlvp-1)
					{
						LimpaMensagem();
						gotoxy(13,23);
						printf("Pressione enter para contiuar mostrando a nota fiscal");
						getch();
						LimpaTela();
						l=10;	
					}
					else
					{
						LimpaMensagem();
						gotoxy(13,23);
						printf("Pressione enter para contiuar mostrando a nota fiscal");
						getch();
						LimpaTela();
						l=10;
						gotoxy(30,6);
						printf("*** Nota fiscal ***");
						gotoxy(30,8);
						printf("Codigo da venda: %d",tlv+1);
						gotoxy(30,9);
						printf("DADOS DA VENDA:");
						
						gotoxy(30,l);
						printf("COD.");
						gotoxy(37,l);
						printf("DESCR.");
						gotoxy(47,l);
						printf("QTDE.");
						gotoxy(55,l);
						printf("PRECO");
						gotoxy(68,l);
						printf("NOME FORN.");
						l++;
					}
				}
			
			}
			
			if(l>=16)
			{
				LimpaMensagem();
				gotoxy(13,23);
				printf("Aperte enter para continuar a nota fiscal!");
				getch();
				
				LimpaTela();
				gotoxy(30,6);
				printf("*** Nota Fiscal ***");
				l=8;
			}
				gotoxy(30,l);
				printf("TOTAL: %.2f",tabVenda[tlv].totVenda);
				l++;
				gotoxy(30,l);
				printf("DATA DA VENDA:");
				gotoxy(45,l);
				printf("%d/%d/%d",tabVenda[tlv].data.dia,tabVenda[tlv].data.mes,tabVenda[tlv].data.ano);
				
				l++;					
				gotoxy(30,l);
				printf("DADOS CLIENTE: ");
				l++;
				gotoxy(30,l);
				printf("CPF: %s",cliente[posc].cpf);
				gotoxy(52,l);
				printf("Nome: %s",cliente[posc].nomeCliente);
		}
		
									
									
		LimpaMensagem();
		gotoxy(13,23);
		printf("Nota fiscal emitida!");
		getch();
	}
	else //chamar a funçao de cadastro de cliente caso nao exista (sim ou nao)
	{
		LimpaMensagem();
		gotoxy(13,23);
		printf("Cpf nao encontrado!");
		getch();
	}
		
	cliente[tlv].qtdeCompra = somaQtde;
	cliente[tlv].valorTotCompr = tabVenda[tlv].totVenda;
	tabVenda[tlv].codVenda = tlv+1;
	
	tlv++;
	LimpaTela();
	
}

//Função que faz o relatorio de vendas
void relatorioVendas(TpProdutos tabProd[TF], TpFornecedor tabForn[TF], TpCliente tabCliente[TF], TpVendas tabVendas[TF], TpVendaProd tabVendasP[TF], int tlp, int tlf, int tlc, int tlv, int tlvp)
{
	int i, l=8, pos=0, posp, posf, j=0,auxCod, posc;
	
	char auxCpf[11], auxNome[30];
	
	LimpaTela();
	gotoxy(30,6);
	printf("*** Relatorio de vendas ***");
	
	if(tlvp == 0)
	{
		LimpaMensagem();
		gotoxy(13,23);
		printf("Tabela vazia!");
	}
	else
	{
			
		while(pos < tlv)
		{
			gotoxy(30,l);
			printf("Codigo da venda: %d",pos+1);
			l++;
			gotoxy(30,l);
			printf("COD.");
			gotoxy(37,l);
			printf("DESCR.");
			gotoxy(47,l);
			printf("QTDE.");
			gotoxy(55,l);
			printf("PRECO");
			gotoxy(68,l);
			printf("NOME FORN.");
			l++;
			
			auxCod=tabVendas[pos].codVenda;
			i=0;
			while(i<tlvp)
			{
				if(auxCod == tabVendasP[i].codVenda)
				{
					posp = buscaCod(tabProd,tlp,tabVendasP[i].codProd);
					posf = buscaForn(tabForn,tlf,tabProd[posp].codForn);
					gotoxy(30,l);
					printf("%d",tabVendasP[i].codProd);
					gotoxy(37,l);
					printf("%s",tabProd[posp].descr);
					gotoxy(48,l);
					printf("%d",tabVendasP[i].qtde);
					gotoxy(55,l);
					printf("R$%.2f",tabVendasP[i].valorUni);
					gotoxy(68,l);
					printf("%s",tabForn[posf].nomeForn);
					l++;
					
					if(l>=19)
					{
						LimpaMensagem();
						gotoxy(13,23);
						printf("Aperte enter para contiuar mostrando o relatorio");
						getch();
						LimpaTela();
						l=8;
						gotoxy(30,6);
						printf("*** Relatorio de vendas ***");
					}
				}
				if(l>=19)
				{
					LimpaMensagem();
					gotoxy(13,23);
					printf("Aperte enter para contiuar mostrando o relatorio");
					getch();
					LimpaTela();
					l=8;
					gotoxy(30,6);
					printf("*** Relatorio de vendas ***");
				}
				i++;
			}
				
				gotoxy(30,l);
				printf("TOTAL: %.2f",tabVendas[pos].totVenda);
				l++;
				gotoxy(30,l);
				printf("DATA DA VENDA:");
				gotoxy(45,l);
				printf("%d/%d/%d",tabVendas[pos].data.dia,tabVendas[pos].data.mes,tabVendas[pos].data.ano);
				
				l++;					
				gotoxy(30,l);
				printf("DADOS CLIENTE: ");
				l++;
				
				
				
				strcpy(auxCpf,tabVendas[pos].CPFCLI);
				posc = buscaCpf(tabCliente,tlc,auxCpf);
				
				strcpy(auxNome,tabCliente[posc].nomeCliente);
				gotoxy(30,l);
				printf("CPF: %s",tabCliente[posc].cpf);
				gotoxy(52,l);
				printf("Nome: %s",tabCliente[posc].nomeCliente);
				l++;
				gotoxy(30,l);
				printf("---------------------------------------");
				l++;
				
				LimpaMensagem();
				gotoxy(13,23);
				printf("Aperte enter para continuar o relatorio!");
				getch();
				LimpaTela();
				l=8;
				gotoxy(30,6);
				printf("*** Relatorio de vendas ***");
				
			pos++;
		}
		if(pos == tlv)
		{
			LimpaMensagem();
			gotoxy(13,23);
			printf("Relatorio finalizado!");
		}
	}
	getch();
	LimpaTela();
}

//Funçao que exclui as vendas e tudo necessario
void excluiVenda(TpVendas tabVenda[TF], int &tlv,TpVendaProd tabVendaP[TF],int &tlvp,TpCliente clientes[TF],int &tlc)
{
	int auxVenda,pos,i,qtda=0,posc;
	
	char auxCpf[11];
	
	float totalV;
	
	LimpaTela();
	
	
	gotoxy(30,6);
	printf("*** Excluir vendas ***");
	
	if(tlv==0)
	{
		LimpaTela();
		gotoxy(13,23);
		printf("Nenhuma venda cadastrada!");
		getch();
		
	}
	else
	{
		gotoxy(30,8);
		printf("Digite o codigo da venda para ser excluida");
		gotoxy(30,9);
		scanf("%d",&auxVenda);
		
		pos = buscaVenda(tabVenda,tlv,auxVenda);
		
		if(pos==-1)
		{
			LimpaTela();
			gotoxy(13,23);
			printf("Codigo de venda nao encontrado!");
			getch();
			
		}
		else
		{
			strcpy(auxCpf,tabVenda[pos].CPFCLI);
			totalV=tabVenda[pos].totVenda;
			LimpaTela();
			gotoxy(30,6);
			printf("*** Detalhes da venda ***");
			gotoxy(30,8);
			printf("Codigo da venda: %d",tabVenda[pos].codVenda);
			gotoxy(30,9);
			printf("CPF do cliente: %s",tabVenda[pos].CPFCLI);
			gotoxy(30,10);
			printf("Data da venda:");
			gotoxy(30,11);
			printf("%d/%d/%d",tabVenda[pos].data.dia,tabVenda[pos].data.mes,tabVenda[pos].data.ano);
			//TESTANDO
			gotoxy(30,12);
			printf("Total venda auxiliar: %.2f",totalV);
			
			
			LimpaMensagem();
			gotoxy(13,23);
			printf("Confirma Exclusao (S/N)? ");
			
			if (toupper(getche())=='S')
			{
				for( i=pos; i<tlv-1; i++)
					tabVenda[i] = tabVenda[i+1];
				
				for(i=0;i<tlvp-1;i++)
				{
					if(tabVendaP[i].codProd == auxVenda)
					{
						tabVendaP[i] = tabVendaP[i+1];
						qtda=qtda+tabVendaP[i].qtde;
					}		
				}
				
				posc = buscaCpf(clientes,tlc,auxCpf);
				clientes[posc].qtdeCompra = clientes[posc].qtdeCompra - qtda;
				clientes[posc].valorTotCompr = clientes[posc].valorTotCompr - totalV;
				
					
				tlv--;
				
				LimpaTela(); 
				gotoxy(13,23);
				printf("Venda excluida com sucesso!");
				getch();
			}
			else
			{
				LimpaTela();
				gotoxy(13,23);
				printf("Voce nao autorizou a exclusao!");
				getch();
			}
			
		}	
	}
	LimpaMensagem();
}

//Main onde o código vai começar
int main(void)
{
	//Declarando a struct de produto
	TpProdutos prod[TF];
	
	//Declarando a struct de clientes
	TpCliente cliente[TF];
	
	//Declarando a struct de fornecedor
	TpFornecedor forn[TF];
	
	//Declarando a struct de vendas
	TpVendas vender[TF];
	
	//Declarando a struct de vendas prod
	TpVendaProd vendas[TF];
	
	int tlp=0, tlc=0, tlf=0, tlv=0, tlvp=0, p=0;
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
				//Repetição para que obrigue o usario a digitar uma das opções
				op = menuProd();
				while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'E' && op != 'F' && op != 'G' && op != 'H' && op != 'I' && op != 'J' && op != 48)
					op = toupper(getch());
				switch(op)
				{
					case 'A':
						cadProd(prod,tlp,forn,tlf);
						
						break;
				
					case 'B':
						ConsultaProd(prod,tlp);
						
						break;
						
					case 'C':
						excProd(prod,tlp);
						
						break;
						
					case 'D':
						alteraProd(prod,tlp);
						
						break;
					
					case 'E':
						relatorioProd(prod,tlp);
						
						break;
						
					case 'F':
						relatorioVendas(prod,forn,cliente,vender,vendas,tlp,tlf,tlc,tlv,tlvp);
						
						break;
						
					case 'G':
						Venderprod(vender,tlv,prod,tlp,cliente,tlc,vendas,tlvp,forn,tlf,p);
						
						break;
						
					case 'H':
						insercaoProd(prod,tlp);
						
						break;
					
					case 'I':
						Inseredados(prod,forn,cliente,tlp,tlf,tlc);
						
						break;
						
					case 'J':
						excluiVenda(vender,tlv,vendas,tlvp,cliente,tlc);
						
						break;
					
					case 48:
						LimpaTela();
						
						break;
				}
				
				if(op == 48)
				{
					LimpaTela();
	
					gotoxy(38,10);
					printf("*** Selecione a opcao desejada ***");
					getch();
					
				}
				break;
				
			case 'C':
				//Repetição para que obrigue o usario a digitar uma das opções
				op = menuCliente();
				while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'E' && op != 'F' && op != 48)
					op = toupper(getch());
				switch(op)
				{
					case 'A':
						cadCliente(cliente,tlc);
						
						break;
						
					case 'B':
						ConsultaCliente(cliente,tlc);
						
						break;
						
					case 'C':
						excCliente(cliente,tlc);
						
						break;
						
					case 'D':
						alteraCliente(cliente,tlc);
						
						break;
					
					
					case 'E':
						relatorioCliente(cliente,tlc,tlv);
						
						break;
						
						
					case 'F':
						Inseredados(prod,forn,cliente,tlp,tlf,tlc);
						
						break;
						
					case 48:
						LimpaTela();
						
						break;
				}
				
				if(op == 48)
				{
					LimpaTela();
	
					gotoxy(38,10);
					printf("*** Selecione a opcao desejada ***");
					getch();
					
				}
				
				
				break;
				
			case 'F':
				//Repetição para que obrigue o usario a digitar uma das opções
				op = menuForn();
				while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'E' && op !='F' && op != 'G' && op != 48)
					op = toupper(getch());
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
					
					case 'E':
						aumentaForn(forn,prod,tlf,tlp);
						
						break;
						
					case 'F':
						relatorioForn(forn,tlf);
						
						break;
						
					case 'G':
						Inseredados(prod,forn,cliente,tlp,tlf,tlc);
						
						break;
						
					case 48:
						LimpaTela();
						
						break;
				}
				if(op == 48)
				{
					LimpaTela();
	
					gotoxy(38,10);
					printf("*** Selecione a opcao desejada ***");
					getch();		
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
