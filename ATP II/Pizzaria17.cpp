#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>
#include<string.h>
#include<ctype.h>

struct TpData{
	int d,m,a;	
};

struct TpClientes{
	char Nome[30], Endereco[30],Cidade[30], Telefone[12], Status;
	int  CEP;
};

struct TpPedidos{
	int NumPedido,CodPizza,Situacao;
	char Telefone[12],CPF[12], Status;
	TpData datapedido;
};

struct TpPizzas{
	int Cod, quant;
	float Valor;
	char Desc [30], Status;
};

struct TpMotoqueiros{
	char Telefone[12],CPF[12],Endereco[30], Nome[30], Status;
	TpData data;
};


int BuscaC(FILE*PtrC, char aux[12]){
	
	TpClientes cli;
	rewind(PtrC);
	fread(&cli,sizeof(TpClientes),1,PtrC);
	while(!feof(PtrC) && !(strcmp(cli.Telefone, aux)== 0 && cli.Status=='A'))
		fread(&cli,sizeof(TpClientes),1,PtrC);
	if(!feof(PtrC))
		return ftell(PtrC)-sizeof(TpClientes);
	else
		return -1;
}

void CadastroClientes(void){
	
	int pos;
	char num;
	clrscr();
	TpClientes cli;
	FILE*PtrC=fopen("ArqCli.dat","ab+");
	if(PtrC==NULL)
		printf("ERRO\n");
	else
	{
		printf("Qual o numero de telefone?\n");
		fflush(stdin);
		gets(cli.Telefone);
		while(strcmp(cli.Telefone,"0")!=0)
		{
			pos = BuscaC(PtrC,cli.Telefone);
			if(pos==-1)
			{
				printf("Qual o nome do Cliente?\n");
				fflush(stdin);
				gets(cli.Nome);
				printf("Qual o endereco?\n");
				fflush(stdin);
				gets(cli.Endereco);
				printf("Qual a cidade?\n");
				fflush(stdin);
				gets(cli.Cidade);
				printf("Qual o CEP?\n");
				scanf("%d",&cli.CEP);
				cli.Status = 'A';
				fseek(PtrC,0,2);
				fwrite(&cli,sizeof(TpClientes),1,PtrC);
			}
			else
				printf("Cliente ja cadastrado\n");
			printf("Qual o numero de telefone?(0 para sair)\n");
			fflush(stdin);
			gets(cli.Telefone);
		}
		fclose(PtrC);
		getch();
	}
}

int buscaP(FILE*PtrP, int aux)
{
	TpPizzas pizza;
	rewind(PtrP);
	fread(&pizza, sizeof(TpPizzas),1,PtrP);
	while (!feof(PtrP) && (pizza.Cod != aux || pizza.Status!= 'A'))
		fread(&pizza, sizeof(TpPizzas),1,PtrP);
	if (!feof(PtrP))
		return ftell(PtrP)-sizeof(TpPizzas);
	else
		return -1;
}

/*int buscaP(FILE* PtrP, int aux) {
    TpPizzas pizza1;

    fseek(PtrP, 0, SEEK_END);
    int qtde = ftell(PtrP) / sizeof(TpPizzas);

    // Adiciona sentinela
    TpPizzas sentinela;
    sentinela.Cod = aux;
    sentinela.Status = 'A';
    fseek(PtrP, 0, SEEK_END);
    fwrite(&sentinela, sizeof(TpPizzas), 1, PtrP);

    fseek(PtrP, 0, SEEK_SET);

    // Procura o elemento
    int posicao = 0;
    while (fread(&pizza1, sizeof(TpPizzas), 1, PtrP) && (pizza1.Cod != aux || pizza1.Status != 'A')) {
        posicao++;
    }

    // Verifica se encontrou o elemento
    if (posicao < qtde) {
        // Retorna a posição do registro encontrado
        return posicao;
    } else {
        // Não encontrou o registro
        return -1;
    }
}*/

void SelecaoDiretaPizza(FILE *Ptr) {
    TpPizzas FM, FP, temp;
    int p, f = ftell(Ptr) / sizeof(TpPizzas), pos;

    while (f > 0) {
        pos = 0;
        rewind(Ptr);
        fread(&FM, sizeof(TpPizzas), 1, Ptr);

        for (p = 1; p < f; p++) {
            fseek(Ptr, p * sizeof(TpPizzas), 0);
            fread(&FP, sizeof(TpPizzas), 1, Ptr);
            if (FP.Cod > FM.Cod) {
                temp = FM;
                FM = FP;
                FP = temp;
                pos = p;
                getch();
            }
        }
        if (pos < f) {
            fseek(Ptr, pos * sizeof(TpPizzas), 0);
            fwrite(&FP, sizeof(TpPizzas), 1, Ptr);

            fseek(Ptr, (f - 1) * sizeof(TpPizzas), 0);
            fwrite(&FM, sizeof(TpPizzas), 1, Ptr);
        }

        f--;
    }
    fseek(Ptr, 0, 2);
}

void OrdeBolhas(FILE *Ptr)
{
	TpPizzas FA,FB; 
	fseek(Ptr,0,2);
	int p,f=ftell(Ptr)/sizeof(TpPizzas),flag=1;
	
	while(f>0 && flag > 0)
	{
		flag=0;
		for(p=0;p <f-1;p++)
		{
			fseek(Ptr,p*sizeof(TpPizzas),0);
			fread(&FA,sizeof(TpPizzas),1,Ptr);
			
			fseek(Ptr,(p+1)*sizeof(TpPizzas),0);
			fread(&FB,sizeof(TpPizzas),1,Ptr);
			
			if(FA.quant > FB.quant)
			{
				fseek(Ptr,p*sizeof(TpPizzas),0);
				fwrite(&FB,sizeof(TpPizzas),1,Ptr);
				
				fseek(Ptr,(p+1)*sizeof(TpPizzas),0);
				fwrite(&FA,sizeof(TpPizzas),1,Ptr);
				
				flag = 1;
			}
		}
		f--;
	}
	
	fseek(Ptr,0,2);
}


void CadastroPizzas(void){ //ordenado com a seleção direta
	int pos;
	clrscr();
	TpPizzas pizza;
	FILE*PtrP=fopen("ArqP.dat","ab+");
	if (PtrP==NULL)
		printf("ERRO\n");
	else
		{
			printf("Codigo da pizza:\n");
			scanf ("%d",&pizza.Cod);
			while(pizza.Cod!=0)
			{
				pos=buscaP(PtrP,pizza.Cod);
				if (pos==-1)
				{
					printf("Sabor da pizza:\n");
					fflush(stdin);
					gets(pizza.Desc);
					printf("Preco da pizza:\n");
					scanf("%f",&pizza.Valor);
					pizza.Status = 'A';
					pizza.quant=0;
					//SelecaoDiretaPizza(PtrP);
					fseek(PtrP,0,2);
					fwrite(&pizza,sizeof(TpPizzas),1,PtrP);
					
				}
				else				
					printf("Ja esta cadastrado!\n");
					
				getch();
				printf("Codigo da pizza:\n");
				scanf("%d",&pizza.Cod);	
			}
			fclose(PtrP);
			getch();
		}
}

int ValidaCPF(char CPF[12])
{
	int vcpf[12], dig1, dig2, i, mult, soma=0, resto;
	
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
			return 0;//falso(CPF INVALIDO)
	}
	else
		return 0;//falso(CPF INVALIDO)
}

int BuscaCPF(FILE*PtrM, char aux[12])
{
    TpMotoqueiros moto;
    rewind(PtrM);
    fread(&moto, sizeof(TpMotoqueiros), 1, PtrM);
    while (!feof(PtrM) && !(strcmp(moto.CPF,aux)== 0 && moto.Status=='A'))
        fread(&moto, sizeof(TpMotoqueiros), 1, PtrM);
    if (!feof(PtrM))
        return ftell(PtrM) - sizeof(TpMotoqueiros);
    return -1;
}



void CadastroMoto(void)
{
	TpMotoqueiros moto;
	int pos,VCPF;
	char CPF[12];
	FILE*PtrM=fopen("ArqMoto.dat","ab+");
	printf("\nQual o CPF do motoqueiro?\n");
	scanf("%s",&moto.CPF);
	while(strcmp(moto.CPF, "0") != 0)
	{
		pos=BuscaCPF(PtrM,moto.CPF);
		if(pos==-1)
		{
			VCPF=ValidaCPF(moto.CPF);
			if(VCPF==0)
				printf("CPF invalido!!\n");
			else
			{
				printf("Qual o seu nome?\n");
				fflush(stdin);
				gets(moto.Nome);
				printf("Qual o endereco?\n");
				fflush(stdin);
				gets(moto.Endereco);
				printf("Qual o telefone?");
				fflush(stdin);
				gets(moto.Telefone);
				printf("Qual a data de admissao?\n");
				scanf("%d %d %d",&moto.data.d,&moto.data.m,&moto.data.a);
				moto.Status = 'A';
				fseek(PtrM,0,2);
				fwrite(&moto,sizeof(TpMotoqueiros),1,PtrM);
				printf("Cadastro concluido\n");
			}
		}
		else
			printf("Ja cadastrado\n");
			
		printf("Qual o CPF do motoqueiro?\n");
		scanf("%s",&moto.CPF);
	}
	fclose(PtrM);
	getch();
}

//int BuscaNum(FILE*PtrPe, int aux)
//{
//	TpPedidos ped;
//	rewind(PtrPe);
//	fread(&ped,sizeof(TpPedidos),1,PtrPe);
//	while(!feof(PtrPe) && (ped.NumPedido != aux || ped.Status != 'A'))
//		fread(&ped,sizeof(TpPedidos),1,PtrPe);
//	if(!feof(PtrPe))
//		return ftell(PtrPe)-sizeof(TpPedidos);
//	else
//		return -1;
//}


int BuscaSeqNum(FILE *Ptr, int aux) // sequencial indexada
{
	TpPedidos ped;
	rewind(Ptr);
	
	fread(&ped,sizeof(TpPedidos),1,Ptr);
	while(!feof(Ptr) && (aux > ped.NumPedido || ped.Status != 'A'))
		fread(&ped,sizeof(TpPedidos),1,Ptr);
	
	if(!feof(Ptr) && aux == ped.NumPedido)
		return ftell(Ptr) - sizeof(TpPedidos);
	else
		return -1;
}

void CadastroPedidos(void)
{
	//clrscr();
	//printf("Qual o numero do pedido?\n");
	int pos,quant=0, posN,auxP,posP,posM, auxPed;
	char auxCPF[12],auxC[12];
	TpClientes cli ;
	TpMotoqueiros moto;
	TpPedidos ped;
	TpPizzas pizza;
	FILE*PtrPe=fopen("ArqPed.dat","ab+");
	FILE*PtrM=fopen("ArqMoto.dat","ab");
	FILE*PtrC=fopen("ArqCli.dat","ab");
	FILE*PtrP=fopen("ArqP.dat","ab+");
	
	if (PtrPe == NULL || PtrM == NULL || PtrC == NULL || PtrP == NULL)
		printf("Erro de abertura");
	else 
	{
		printf("Qual o numero do pedido?\n");
		scanf("%d",&auxPed);
		while(auxPed!=0)
		{	
			pos=BuscaSeqNum(PtrPe,auxPed);
			if(pos==-1)
			{
				printf("Qual o numero de telefone?\n");
				fflush(stdin);
				gets(auxC);
				posN=BuscaC(PtrC,auxC);
				//posN=-1;
				
				printf("%d",posN);
				if(posN==-1)
					printf("Cliente nao cadastrado!!\n");
				else
				{
					printf("Qual o codigo da pizza?\n");
					scanf("%d",&auxP);
					posP=buscaP(PtrP,auxP);
					if(posP==-1)
						printf("Pizza nao cadastrada\n");
						else
						{
							
							printf("Qual o CPF do motoqueiro: \n");
							scanf("%s", &auxCPF);
							posM=BuscaCPF(PtrM,auxCPF);
							if (posM == -1)
								printf("CPF nao encontrado"); 
							else 
							{
									printf("Data do pedido\n");
									scanf("%d %d %d",&ped.datapedido.d,&ped.datapedido.m,&ped.datapedido.a);
									
									fseek(PtrP, posP, SEEK_SET); 
									fread(&pizza, sizeof(TpPizzas), 1, PtrP); 
									pizza.quant+=1; 
									fseek(PtrP, posP, SEEK_SET); 
									fwrite(&pizza, sizeof(TpPizzas), 1, PtrP); 
									OrdeBolhas(PtrP);
									
									fseek(PtrPe,0,2);
									ped.NumPedido = auxPed;
									ped.Status = 'A';
									ped.Situacao=1;
									strcpy(ped.Telefone, auxC);
									ped.CodPizza = auxP;
									strcpy(ped.CPF, auxCPF);
									fwrite(&ped,sizeof(TpPedidos),1,PtrPe);	
							}
						}
				}
			}
			else
				printf("Pedido ja existente!");			
			printf("Qual o numero do pedido?\n");
			scanf("%d", &auxPed);
		}			
	}
	getch();
	fclose(PtrPe);
	fclose(PtrM);
	fclose(PtrC); 
	fclose(PtrP);
	
}

void AlterarCliente(void)
{
	clrscr();
	int posA;
	TpClientes cli;
	FILE*PtrC=fopen("ArqCli.dat","rb+");
	if(PtrC==NULL)
		printf("erro de abertura\n");
	else
	{
		printf("Qual o numero de telefone do cliente pra alterar?\n");
		fflush(stdin);
		gets(cli.Telefone);
		while(cli.Telefone!=0 || cli.Status=='A')
		{
			posA=BuscaC(PtrC,cli.Telefone);
			if(posA==-1)
				printf("Nao cadastrado!!\n");
			else
			{
				fseek(PtrC,posA,0);
				fread(&cli,sizeof(TpClientes),1,PtrC);
				printf("Nome %s\n", cli.Nome);
				printf("CEP do cliente: %d\n", cli.CEP);
				printf("Cidade do cliente: %s\n", cli.Cidade); 
				printf("Endereço do cliente: %s\n",cli.Endereco);
				printf("Status do cliente %s\n",cli.Status);
				printf("Telefone do cliente %s\n",cli.Telefone);
				
				printf("Deseja alterar o nome?(S/N)");
				if(toupper(getche())=='S')
				{
					printf("digite o novo nome:\n");
					fflush(stdin);
					gets(cli.Nome);
					fseek(PtrC,posA,0);
					fwrite(&cli,sizeof(TpClientes),1,PtrC);
					printf("Nome alterado!!\n");
				}
				else
					printf("Alteracao negada!!\n");
			}
			printf("Qual o numero de telefone do cliente pra alterar?\n");
			fflush(stdin);
			gets(cli.Telefone);
		}
	}
	fclose(PtrC);
	getch();			
}



void AlterarMoto(void)
{
	clrscr();
	int posA;
	TpMotoqueiros moto;
	FILE*PtrM=fopen("ArqMoto.dat","rb+");
	if(PtrM==NULL)
		printf("erro de abertura\n");
	else
	{
		printf("Qual o CPF do motoqueiro que deseja alterar?\n");
		fflush(stdin);
		gets(moto.CPF);
		while(moto.CPF!=0 || moto.Status=='A')
		{
			posA=BuscaCPF(PtrM,moto.CPF);
			if(posA==-1)
				printf("Nao cadastrado!!\n");
			else
			{
				fseek(PtrM,posA,0);
				fread(&moto,sizeof(TpMotoqueiros),1,PtrM);
				printf("Nome: %s\n",moto.Nome);
				printf("CPF %s\n", moto.CPF);
				printf("Endereço: %s\n", moto.Endereco); 
				printf("Status do motoqueiro%s\n",moto.Status);
				printf("Telefone do motoqueiro %s\n",moto.Telefone);
				
				printf("Deseja alterar o nome?(S/N)");
				if(toupper(getche())=='S')
				{
					printf("digite o novo nome:\n");
					fflush(stdin);
					gets(moto.Nome);
					fseek(PtrM,posA,0);
					fwrite(&moto,sizeof(TpMotoqueiros),1,PtrM);
					printf("Nome alterado!!\n");
				}
				else
					printf("Alteracao negada!!\n");
			}
			printf("Qual o CPF do motoqueiro que deseja alterar?\n");
			fflush(stdin);
			gets(moto.CPF);
		}
	}
	fclose(PtrM);
	getch();
	
}



void AlterarPed(void)
{
	clrscr();
	int posA;
	TpPedidos ped;
	TpClientes cli;
	FILE*PtrA=fopen("ArqPed.dat","rb+");
	if(PtrA==NULL)
		printf("erro de abertura\n");
	else
	{
		printf("Qual pedido deseja alterar?\n");
		scanf("%d",&ped.NumPedido);
		while(ped.NumPedido!=0 || ped.Status=='A')
		{
			posA=BuscaSeqNum(PtrA,ped.NumPedido);
			if(posA==-1)
				printf("Nao cadastrado!!\n");
			else
			{
				fseek(PtrA,posA,0);
				fread(&ped,sizeof(TpPedidos),1,PtrA);
				printf("Codigo do pedido: %d\n", ped.NumPedido);
				printf("Codigo da pizza: %d\n", ped.CodPizza); 
				printf("CPF do cliente: %s\n",ped.CPF);
				printf("Numero de telefone %s\n", ped.Telefone);
				printf("Data do pedido %d %d %d\n",ped.datapedido);
				printf("Situacao do pedido %d\n",ped.Situacao);
				
				printf("Deseja alterar a situacao?(S/N)");
				if(toupper(getche())=='S')
				{
					printf("digite (1 em preparo; 2 a caminho; 3 entregue");
					scanf("%d",&ped.Situacao);
					fseek(PtrA,posA,0);
					fwrite(&ped,sizeof(TpPedidos),1,PtrA);
					printf("Situacao alterada!!\n");
				}
				else
					printf("Alteracao negada!!\n");
			}
			printf("Qual pedido deseja alterar?\n");
			scanf("%d",&ped.NumPedido);
		}
	}
	fclose(PtrA);
	getch();			
}


void AlterarPizza(void)
{
	clrscr();
	int posA;
	TpPizzas pizza;
	FILE*PtrP=fopen("ArqP.dat","rb+");
	if(PtrP==NULL)
		printf("erro de abertura\n");
	else
	{
		printf("Digite o codigo da pizza que deseja alterar\n");
		scanf("%d",&pizza.Cod);
		while(pizza.Cod!=0 || pizza.Status=='A')
		{
			posA=buscaP(PtrP,pizza.Cod);
			if(posA==-1)
				printf("Nao cadastrado!!\n");
			else
			{
				fseek(PtrP,posA,0);
				fread(&pizza,sizeof(TpPizzas),1,PtrP);
				printf("Codigo da pizza: %d\n", pizza.Cod);
				printf("Descricao da pizza: %s\n", pizza.Desc); 
				printf("Status da pizza %s\n",pizza.Status);
				printf("Valor da pizza %.2f\n", pizza.Valor);

				printf("Deseja alterar o sabor?(S/N)");
				if(toupper(getche())=='S')
				{
					printf("digite o novo sabor:\n");
					fflush(stdin);
					gets(pizza.Desc);
					fseek(PtrP,posA,0);
					fwrite(&pizza,sizeof(TpPizzas),1,PtrP);
					printf("Sabor alterado!!\n");
				}
				else
					printf("Alteracao negada!!\n");
			}
			printf("Digite o codigo da pizza que deseja alterar\n");
			scanf("%d",&pizza.Cod);
		}
	}
	fclose(PtrP);
	getch();			
}

void Inseredados(void)
{
    TpClientes cli;
    TpMotoqueiros moto;
    TpPizzas pizza;
    TpPedidos ped;
    FILE* PtrC = fopen("ArqCli.dat", "ab");
    FILE* PtrM = fopen("ArqMoto.dat", "ab");
    FILE* PtrP = fopen("ArqP.dat", "ab");
    FILE* PtrPe = fopen("ArqPed.dat", "ab");

    // Cliente
    strcpy(cli.Cidade, "Euclides");
    strcpy(cli.Endereco, "Democrata");
    strcpy(cli.Nome, "Maria Julia");
    cli.CEP = 19275000;
    strcpy(cli.Telefone , "18996866687");
    cli.Status = 'A';
    fwrite(&cli, sizeof(TpClientes), 1, PtrC);

    
    strcpy(cli.Cidade, "Prudente");
    strcpy(cli.Endereco, "Av saudade");
    strcpy(cli.Nome, "Luigi");
    cli.CEP = 10239000;
    strcpy(cli.Telefone , "18997959115");
    cli.Status = 'A';
    fwrite(&cli, sizeof(TpClientes), 1, PtrC);


    // Motoqueiros
    strcpy(moto.CPF, "58556779824");
    moto.data.d = 21; // Dia
    moto.data.m = 5;  // Mês
    moto.data.a = 2024; // Ano
    strcpy(moto.Endereco, "Prudente");
    strcpy(moto.Nome, "Julia");
    strcpy(moto.Telefone , "18996866687");
    moto.Status = 'A';
    fwrite(&moto, sizeof(TpMotoqueiros), 1, PtrM);


    // Pizza
    pizza.Cod = 11;
    strcpy(pizza.Desc, "frango");
    pizza.Valor = 50;
    pizza.Status = 'A';
    fwrite(&pizza, sizeof(TpPizzas), 1, PtrP);
   
    
    pizza.Cod = 12;
    strcpy(pizza.Desc, "queijo");
    pizza.Valor = 40;
    pizza.Status = 'A';
    fwrite(&pizza, sizeof(TpPizzas), 1, PtrP);
    

    // Pedidos
    ped.CodPizza = 11;
    strcpy(ped.CPF, "58556779824");
    ped.datapedido.d = 21; // Dia
    ped.datapedido.m = 5;  // Mês
    ped.datapedido.a = 2024; // Ano
    ped.NumPedido = 22;
    ped.Situacao = 2;
	strcpy(cli.Telefone, "18996866687");
	ped.Status = 'A';
    fwrite(&ped, sizeof(TpPedidos), 1, PtrPe);
    

	ped.CodPizza = 12;
    strcpy(ped.CPF, "58556779824");
    ped.datapedido.d = 21; // Dia
    ped.datapedido.m = 5;  // Mês
    ped.datapedido.a = 2024; // Ano
    ped.NumPedido = 33;
    ped.Situacao = 1;
	strcpy(cli.Telefone, "18996866687");
	ped.Status = 'A';
    fwrite(&ped, sizeof(TpPedidos), 1, PtrPe);
    
    fclose(PtrC);
    fclose(PtrM);
    fclose(PtrP);
    fclose(PtrPe);
}


void PizzaCaminho(void)
{
	clrscr();
	TpPedidos ped;
	FILE*PtrPe = fopen("ArqPed.dat","rb");
	int a;
	if(PtrPe==NULL)
		printf("ERRo\n");
	else
	{
		fread(&ped,sizeof(TpPedidos),1,PtrPe);
		while(!feof(PtrPe))
		{
			if(ped.Situacao == 2)
				printf("Codigo da pizza a caminho %d",ped.NumPedido);
			fread(&ped,sizeof(TpPedidos),1,PtrPe);
		}
	}
	fclose(PtrPe);
	getch();	
}

void PizzaPreparo(void)
{
	clrscr();
	TpPedidos ped;
	FILE*PtrPe = fopen("ArqPed.dat","rb");
	int a;
	if(PtrPe==NULL)
		printf("ERRo\n");
	else
	{
		fread(&ped,sizeof(TpPedidos),1,PtrPe);
		while(!feof(PtrPe))
		{
			if(ped.Situacao == 1)
				printf("Codigo da pizza em preparo %d",ped.NumPedido);
			fread(&ped,sizeof(TpPedidos),1,PtrPe);
		}
	}
	fclose(PtrPe);
	getch();	
}

void ConsultaCli(void)
{
	int pos;
	char aux[12];
	TpClientes cli;
	FILE*PtrC=fopen("ArqCli.dat","rb");
	if(PtrC==NULL)
		printf("ERRO\n");
	else{
		printf("Qual o telefone do cliente deseja consultar?\n");
		fflush(stdin);
		gets(aux);
		while(strcmp(aux,"0")!=0)
		{
			pos = BuscaC(PtrC,aux);
			if(pos==-1)
				printf("Cliente nao cadastrado!!");
			else
			{
				fseek(PtrC,pos,0);
				fread(&cli,sizeof(TpClientes),1,PtrC);
				printf("Telefone %s \nCEP %d \nCidade %s \nEndereco %s \nNome %s",cli.Telefone,cli.CEP,cli.Cidade,cli.Endereco,cli.Nome);			
			}
			printf("Qual o telefone do cliente deseja consultar?\n");
			fflush(stdin);
			gets(aux);
		}
	}
	fclose(PtrC);
	getch();
}

void ConsultaMoto(void)
{
	int pos;
	char aux[12];
	TpMotoqueiros moto;
	FILE*PtrM=fopen("ArqMoto.dat","rb");
	if(PtrM==NULL)
		printf("ERRO\n");
	else
	{
		printf("Qual o CPF do motoqueiro que deseja consultar?\n");
		fflush(stdin);
		gets(aux);
		while(strcmp(aux,"\0")!=0)
		{
			pos = BuscaCPF(PtrM,aux);
			if(pos==-1)
				printf("CPF nao cadastrado!!");
			else
			{
				fseek(PtrM,pos,0);
				fread(&moto,sizeof(TpMotoqueiros),1,PtrM);
				printf("CPF: %s\n", moto.CPF);
                printf("Data: %d/%d/%d\n", moto.data.d, moto.data.m, moto.data.a);
                printf("Endereco: %s\n", moto.Endereco);
                printf("Nome: %s\n", moto.Nome);
                printf("Telefone: %s\n", moto.Telefone);			
			}
			printf("Qual o CPF do motoqueiro que deseja consultar?\n");
			fflush(stdin);
			gets(aux);
		}
	}
	fclose(PtrM);
	getch();
}

void ConsultaPizza(void)
{
	int pos, aux;
	TpPizzas pizza;
	FILE*PtrP=fopen("ArqP.dat","rb");
	if(PtrP==NULL)
		printf("ERRO\n");
	else{
		printf("Qual o codigo da pizza que deseja consultar?\n");
		scanf("%d", &aux);
		while(aux!=0)
		{
			pos = buscaP(PtrP,aux);
			if(pos==-1)
				printf("Codigo nao cadastrado!!");
			else
			{
				fseek(PtrP,pos,0);
				fread(&pizza,sizeof(TpPizzas),1,PtrP);
				printf("Codigo %d \nDescricao %s \nValor %.2f\nQuantidade vendida:%d\n",pizza.Cod,pizza.Desc,pizza.Valor,pizza.quant);			
			}
			printf("Qual o codigo da pizza que deseja consultar?\n");
			scanf("%d", &aux);
		}
	}
	fclose(PtrP);
	getch();
}

void ConsultaPed(void)
{
	int pos, aux;
	TpPedidos ped;
	FILE*PtrPed=fopen("ArqPed.dat","rb");
	if(PtrPed==NULL)
		printf("ERRO\n");
	else{
		printf("Qual o codigo do pedido que deseja consultar?\n");
		scanf("%d", &aux);
		while(aux!=0)
		{
			pos = BuscaSeqNum(PtrPed,aux);
			if(pos==-1)
				printf("Codigo nao cadastrado!!");
			else
			{
				fseek(PtrPed,pos,0);
				fread(&ped,sizeof(TpPedidos),1,PtrPed);
				printf("Codigo: %d\n", ped.CodPizza);
                printf("CPF: %s\n", ped.CPF);
                printf("Data: %d/%d/%d\n", ped.datapedido.d, ped.datapedido.m, ped.datapedido.a);
                printf("Numero do Pedido: %d\n", ped.NumPedido);
                printf("Situacao: %d\n", ped.Situacao);
                printf("Telefone:%s\n", ped.Telefone);			
			}
			printf("Qual o codigo do pedido que deseja consultar?\n");
			scanf("%d", &aux);
		}
	}
	fclose(PtrPed);
	getch();
}

void RelatorioCli(void)
{
	TpClientes cli;
	printf("------ RELATORIO CLIENTES ------\n");
	FILE*PtrC=fopen("ArqCli.dat","rb");
	if(PtrC==NULL)
		printf("ERRO\n");
	else
	{
		fseek(PtrC,0,0);
		fread(&cli,sizeof(TpClientes),1,PtrC);
		while(!feof(PtrC))
		{
			printf("Telefone %s \nCEP %d \nCidade %s \nEndereco %s \nNome %s\n", cli.Telefone,cli.CEP,cli.Cidade,cli.Endereco,cli.Nome);
			fread(&cli,sizeof(TpClientes),1,PtrC);
		}
	}
	fclose(PtrC);
	getch();
}

void RelatorioPizza(void)
{
	TpPizzas p;
	printf("------ RELATORIO CLIENTES ------\n");
	FILE*PtrP=fopen("ArqP.dat","rb");
	if(PtrP==NULL)
		printf("ERRO\n");
	else
	{
		fseek(PtrP,0,0);
		fread(&p,sizeof(TpPizzas),1,PtrP);
		while(!feof(PtrP))
		{
			printf("Codigo %d \nDescricao %s \nQuantidade %d \nStatus %s \nValor %.2f\n",p.Cod,p.Desc,p.quant,p.Status,p.Valor);
			fread(&p,sizeof(TpPizzas),1,PtrP);
		}
	}
	fclose(PtrP);
	getch();
}


void RelatorioPed(void)
{
	TpPedidos ped;
	printf("------ RELATORIO PEDIDOS ------\n");
	FILE*PtrPe=fopen("ArqPed.dat","rb");
	if(PtrPe==NULL)
		printf("ERRO\n");
	else
	{
		fseek(PtrPe,0,0);
		fread(&ped,sizeof(TpPedidos),1,PtrPe);
		while(!feof(PtrPe))
		{
			printf("Cod pizza %d \nCPF %s \nData %d %d %d \nNum ped %d \nSituacao %d\n Status %s\n Telefone %s\n",ped.CodPizza, ped.CPF, ped.datapedido.d, ped.datapedido.m, ped.datapedido.a,ped.NumPedido,ped.Situacao,ped.Status,ped.Telefone);
			fread(&ped,sizeof(TpPedidos),1,PtrPe);
		}
	}
	fclose(PtrPe);
	getch();
}

/*
void RelatorioMoto(void)
{
	TpMotoqueiros moto;
	printf("------ RELATORIO MOTOQUEIROS ------\n");
	FILE*PtrM=fopen("ArqMoto.dat","rb");
	if(PtrM==NULL)
		printf("ERRO\n");
	else
	{
		fseek(PtrM,0,0);
		fread(&moto,sizeof(TpMotoqueiros),1,PtrM);
		while(!feof(PtrC))
		{
			printf("CPF %s \nData %d %d %d \n \nEndereco %s \nNome %s\n Status %s\n Telefone %s\n", moto.CPF, moto.data.d, moto.data.m, moto.data.a, moto.Endereco, moto.Nome, moto.Status, moto.Telefone);
			fread(&moto,sizeof(TpMotoqueiros),1,PtrM);
		}
	}
	fclose(PtrM);
	getch();
}*/

void ExclusaoFisicaCli(void)
{
	printf("------ EXCLUSAO FISICA CLIENTES -----");
	TpClientes cli;
	int pos;
	char aux[12];
	FILE*PtrC=fopen("ArqCli.dat","rb");
	if(PtrC==NULL)
		printf("ERRO\n");
	else
	{
		printf("Qual telefone deseja excluir!!\n");
		fflush(stdin);
		gets(aux);
		if(strcmp(aux, "0")!=0)
		{
			pos = BuscaC(PtrC,aux);
			if(pos==-1)
			{	
				printf("Cliente nao cadastrado\n");
				getch();
			}
			
			else
			{
				fseek(PtrC,pos,0);
				fread(&cli,sizeof(TpClientes),1,PtrC);
				printf("---- Detalhes do registro ----\n");
				printf("Telefone %s \tCEP %d \tCidade %s \tEndereco %s \tNome %s", cli.Telefone,cli.CEP,cli.Cidade,cli.Endereco,cli.Nome);
				printf("Confirma exclusao?(S/N)\n");
				
				
				if(toupper(getche())=='S')
				{
					FILE*PtrN = fopen("ArqNovo.dat","wb");
					rewind(PtrC);
					fread(&cli,sizeof(TpClientes),1,PtrC);
					while(!feof(PtrC))
					{
						if(strcmp(cli.Telefone,aux) != 0 )
							fwrite(&cli,sizeof(TpClientes),1,PtrN);
						fread(&cli,sizeof(TpClientes),1,PtrC);
					}
					fclose(PtrC);
					fclose(PtrN);
					remove("ArqCli.dat");
					rename("ArqNovo.dat","ArqCli.dat");
					printf("---- Registro deletado ----\n");
					getch();
				}
				else
					printf("---- Exclusao Negada ----\n");
			}
		}
		
	}
	fclose(PtrC);
}


void ExclusaoFisicaPed(void)
{
	printf("------ EXCLUSAO FISICA PEDIDOS -----");
	TpPedidos ped;
	TpPizzas pizza;
	int pos, aux, posP;
	FILE*PtrPe=fopen("ArqPed.dat","rb");
	FILE*PtrP=fopen("ArqP.dat","rb+");
	if(PtrPe==NULL || PtrP==NULL)
		printf("ERRO\n");
	else
	{
		printf("Qual o codigo deseja excluir!!\n");
		scanf("%d",&aux);
		if(aux!=0)
		{
			pos = BuscaSeqNum(PtrPe,aux);
			if(pos==-1)
			{	
				printf("Pedido nao cadastrado\n");
				getch();
			}
			
			else
			{
				fseek(PtrPe,pos,0);
				fread(&ped,sizeof(TpPedidos),1,PtrPe);
				printf("---- Detalhes do registro ----\n");
				printf("Codigo da pizza %d\n",ped.CodPizza);
				printf("CPF do motoqueiro %s\n",ped.CPF);
				printf("Data do pedido %d/%d/%d\n",ped.datapedido.d,ped.datapedido.m,ped.datapedido.a);
				printf("Numero do pedido %d\n",ped.NumPedido);
				printf("Situacao %d\n",ped.Situacao);
				printf("Telefone do cliente %s\n",ped.Telefone);
				printf("Confirma exclusao?(S/N)\n");
				
				if(toupper(getche())=='S')
				{
					posP = buscaP(PtrP,ped.CodPizza);
					if(posP!=-1)
					{
							
						fseek(PtrP, posP, SEEK_SET); 
						fread(&pizza, sizeof(TpPizzas), 1, PtrP); 
						pizza.quant-=1; 
						fseek(PtrP, posP, SEEK_SET); 
						fwrite(&pizza, sizeof(TpPizzas), 1, PtrP);
						OrdeBolhas(PtrP);
					
					}
					FILE*PtrN = fopen("ArqNovo.dat","wb");
					rewind(PtrPe);
					fread(&ped,sizeof(TpPedidos),1,PtrPe);
					while(!feof(PtrPe))
					{
						if(ped.NumPedido!=aux)
							fwrite(&ped,sizeof(TpPedidos),1,PtrN);
						fread(&ped,sizeof(TpPedidos),1,PtrPe);
					}
					fclose(PtrPe);
					fclose(PtrN);
					fclose(PtrP);
					remove("ArqPed.dat");
					rename("ArqNovo.dat","ArqPed.dat");
					printf("---- Registro deletado ----\n");
					getch();
				}
				else
					printf("---- Exclusao Negada ----\n");
					getch();
			}
		}
		
	}
	fclose(PtrPe);
}


void ExclusaoFisicaMoto(void)
{
	FILE*Ptr=fopen("ArqMoto.dat","rb");
	TpMotoqueiros moto;
	char aux[12];
	int pos;
	if(Ptr==NULL)
	{
		printf("ERRO\n");
	}
	else
	{
		printf("Qual CPF deseja excluir?\n");
		fflush(stdin);
		scanf("%s",&aux);
		if(strcmp(aux,"0")!=0)
		{
			pos = BuscaCPF(Ptr,aux);
			if(pos==-1)
			{
				printf("Motoqueiro nao cadastrado!!\n");
				getch();
			}
			else
			{
				fseek(Ptr,pos,0);
				fread(&moto,sizeof(TpMotoqueiros),1,Ptr);
				printf("CPF: %s\n",moto.CPF);
				printf("Data de admissao: %d/%d/%d\n",moto.data.d,moto.data.m,moto.data.a);
				printf("Endereco: %s\n",moto.Endereco);
				printf("Nome: %s\n",moto.Nome);
				printf("Telefone: %s\n",moto.Telefone);
				printf("Deseja excluir?(S/N)");
				if(toupper(getche())=='S')
				{
					FILE*PtrN=fopen("ArqNovo.dat","wb");
					rewind(Ptr);
					fread(&moto,sizeof(TpMotoqueiros),1,Ptr);
					while(!feof(Ptr))
					{
						if(moto.CPF!=aux)
							fwrite(&moto,sizeof(TpMotoqueiros),1,PtrN);
						fread(&moto,sizeof(TpMotoqueiros),1,Ptr);
					}
					fclose(Ptr);
					fclose(PtrN);
					remove("ArqMoto.dat");
					rename("ArqNovo.dat","ArqMoto.dat");
					printf("Exclusao concluida\n!!");
					getch();	
				}
				else
				{
					printf("Exclusao negada!!\n");
					getch();
				}
					
			}
		}
	}
	fclose(Ptr);

}


void ExclusaoFisicaPizza(void)
{
	FILE*Ptr=fopen("ArqP.dat","rb");
	TpPizzas pizza;
	int aux,pos;
	if(Ptr==NULL)
	{
		printf("ERRO!\n");
	}
	else
	{
		printf("Qual o codigo deseja excluir?\n");
		scanf("%d",&aux);
		if(aux!=0)
		{
			pos= buscaP(Ptr,aux);
			if(pos==-1)
			{
				printf("Pizza nao cadastrada!!\n");
			}
			else
			{
				fseek(Ptr,pos,0);
				fread(&pizza,sizeof(TpPizzas),1,Ptr);
				printf("Codigo da pizza: %d\n",pizza.Cod);
				printf("Descricao: %s\n",pizza.Desc);
				printf("Valor: %.2f",pizza.Valor);
				printf("Deseja excluir?(S/N)\n");
				if(toupper(getche())=='S')
				{
					FILE*PtrN=fopen("ArqNovo.dat","wb");
					rewind(Ptr);
					fread(&pizza,sizeof(TpPizzas),1,Ptr);
					while(!feof(Ptr))
					{
						if(pizza.Cod!=aux)
							fwrite(&pizza,sizeof(TpPizzas),1,PtrN);
						fread(&pizza,sizeof(TpPizzas),1,Ptr);
					}
					fclose(Ptr);
					fclose(PtrN);
					remove("ArqP.dat");
					rename("ArqNovo,dat","ArqP.dat");
					printf("Exclusao concluida\n");
					getch();
				}
				else
				{
					printf("Exclusao negada\n");
					getch();
				}
			}
		}
	}
	fclose(Ptr);
}


void ExclusaoLogicaPed(void)
{
	TpPedidos ped;
	int pos;
	FILE*PtrP=fopen("ArqPed.dat","rb+");
	if(PtrP==NULL)
		printf("Erro\n");
	else
	{
		printf("Qual codigo do pedido que deseja excluir?\n");
		scanf("%d",&ped.NumPedido);
		while(ped.NumPedido!=0)
		{
			pos=BuscaSeqNum(PtrP,ped.NumPedido);
			if(pos==-1)
				printf("Codigo nao cadastrado\n");
			else
			{
				fseek(PtrP,pos,0);
				fread(&ped,sizeof(TpPedidos),1,PtrP);
				printf("Codigo da pizza %d, CPF do motoqueiro %s\n Telefone do cliente %s\n data do pedido %d %d %d\n numero do pedido %d\n Situacao do pedido %d\n", ped.CodPizza, ped.CPF, ped.Telefone, ped.datapedido,ped.NumPedido, ped.Situacao);
				printf("Deseja excluir(S/N)\n");
				if(toupper(getche())=='S')
				{
					fseek(PtrP,pos,0);
					ped.Status = 'I';
					fwrite(&ped,sizeof(TpPedidos),1,PtrP);
					printf("Exclusao Logica concluida\n");
				}
				else
					printf("Exclusao negada!!\n");
			}
			printf("Qual codigo do pedido que deseja excluir?\n");
			scanf("%d",&ped.NumPedido);
		}
	}
	fclose(PtrP);
	getch();
}


void ExclusaoLogicaCli(void)
{
	FILE*Ptr=fopen("ArqCli.dat","rb+");
	TpClientes cli;
	char aux[12];
	int pos;
	if(Ptr==NULL)
	{
		printf("ERRO!!\n");
	}
	else
	{
		printf("Qual Telefone deseja excluir?\n");
		fflush(stdin);
		gets(aux);
		if(strcmp(aux,"0")!=0)
		{
			pos= BuscaC(Ptr,aux);
			if(pos==-1)
			{
				printf("Cliente nao cadastrado!!\n");
				getch();
			}
			else
			{
				fseek(Ptr,pos,0);
				fread(&cli,sizeof(TpClientes),1,Ptr);
				printf("CEP: %d\n",cli.CEP);
				printf("Cidade: %s\n",cli.Cidade);
				printf("Endereco: %s\n",cli.Endereco);
				printf("Nome: %s\n",cli.Nome);
				printf("Telefone: %s\n",cli.Telefone);
				printf("Deseja excluir?(S/N)\n");
				if(toupper(getche())=='S')
				{
					fseek(Ptr,pos,0);
					cli.Status = 'I';
					fwrite(&cli,sizeof(TpClientes),1,Ptr);
					printf("Cliente Inativo!!");
				}
				else
				{
					printf("Exclusao negada!!\n");
					getch();
				}
			}
		}
	}
	fclose(Ptr);
}


void ExclusaoLogicaPizza(void)
{
	FILE*Ptr=fopen("ArqP.dat","rb+");
	TpPizzas pizza;
	int aux,pos;
	if(Ptr==NULL)
	{
		printf("ERRO\n");
	}
	else
	{
		printf("Qual codigo deseja excluir?n");
		scanf("%d",&aux);
		if(aux!=0)
		{
			pos=buscaP(Ptr,aux);
			if(pos==-1)
			{
				printf("Pizza nao cadastrada\n");
				getch();
			}
			else
			{
				fseek(Ptr,pos,0);
				fread(&pizza,sizeof(TpPizzas),1,Ptr);
				printf("Codigo da pizza: %s\n",pizza.Cod);
				printf("Descricao: %s\n",pizza.Desc);
				printf("Valor: %.2f\n",pizza.Valor);
				printf("Desseja excluir?(S/N)\n");
				if(toupper(getche())=='S')
				{
					fseek(Ptr,pos,0);
					pizza.Status = 'I';
					fwrite(&pizza,sizeof(TpPizzas),1,Ptr);
					printf("Pizza inativa!!\n");
					getch();
				}
				else
				{
					printf("Exclusao negada!!\n");
					getch();
				}
			}
		}
	}
	fclose(Ptr);
}

void ConsumoCli(void)
{
	FILE*Ptr=fopen("ArqCli.dat","rb");
	FILE*PtrPe=fopen("ArqPed.dat","rb");
	TpPedidos ped;
	TpClientes cli;
	int quant=0,a,b,qtde=0, quantPe=0, total=0, pos=0;
	quant = ftell(Ptr)/sizeof(TpClientes);
	quantPe = ftell(PtrPe)/sizeof(TpPedidos);//TL
	if(Ptr==NULL||PtrPe==NULL)
		printf("ERRO\n");
	else
	{
		for(a=0;a<quant;a++)
		{
			fseek(Ptr,a,0);
			fread(&cli,sizeof(TpClientes),1,Ptr);
			for(b=0;b<quantPe;b++)
			{
				fseek(Ptr,b,0);
				fread(&ped,sizeof(TpPedidos),1,Ptr);
				if(cli.Telefone==ped.Telefone)
				{
					if(cli.Status=='A'&&ped.Status=='A')
						qtde++;
				}		
			}
			if(total<qtde)
			{
				total=qtde;
				pos = a;
			}
		}
	}
	fseek(Ptr,pos,0);
	fread(&cli,sizeof(TpClientes),1,Ptr);
	printf("O Cliente que mais consome e: Cep: %d, Cidade: %s, Endereco: %s, Nome: %s, Telefone %d", cli.CEP,cli.Cidade,cli.Endereco,cli.Nome,cli.Telefone);
	fclose(Ptr);
	fclose(PtrPe);
	getch();
}

void MaisTipoPizza(void)
{
	printf("----- o Cliente que mais consome um determinado tipo de pizza -----\n");
	TpPizzas pizza;
	TpPedidos ped;
	TpClientes cli;
	FILE*Ptr=fopen("ArqP.dat","rb");
	FILE*PtrPed=fopen("ArqPed.dat","rb");
	FILE*PtrC=fopen("ArqCli.dat","rb");
	int qtde=0,qtdePed=0,aux,a,b,total=0,quant=0,pos=0;
	qtde = ftell(PtrC)/sizeof(TpClientes);
	qtdePed = ftell(PtrPed)/sizeof(TpPedidos);
	if(Ptr==NULL || PtrPed==NULL || PtrC==NULL)
		printf("ERRO\n");
	else
	{
		printf("Qual o codigo da pizza?\n");
		scanf("%d",&aux);
		for(a=0;a<qtde;a++)
		{
			fseek(Ptr,a,0);
			fread(&cli,sizeof(TpClientes),1,PtrC);
			for(b=0;b<qtdePed;b++)
			{
				fseek(PtrPed,b,0);
				fread(&ped,sizeof(TpPedidos),1,PtrPed);
				if(cli.Telefone==ped.Telefone)
				{
					if(ped.CodPizza==aux)
						if(cli.Status=='A'&&ped.Status=='A')
							quant++;
				}
			}
			if(total<quant)
			{
				total=quant;
				pos=a;
			}
		}
		fseek(PtrC,pos,0);
		fread(&cli,sizeof(TpClientes),1,PtrC);
		printf("o cliente que mais consome a pizza:\n CEP: %d\nCidade %s\nEndereco %s\nNome %s\nTelefone %s\n",cli.CEP,cli.Cidade,cli.Endereco,cli.Nome,cli.Telefone);
		fclose(Ptr);
		fclose(PtrPed);
		fclose(PtrC);
		getch();
	}
}

void PizzaMaisPed(void)
{
	TpPizzas pizza;
	TpPedidos ped;
	FILE*Ptr=fopen("ArqP.dat","rb");
	FILE*PtrPed=fopen("ArqPed.dat","rb");
	int qtde=0, qtdePed=0,a,b, pos=0, total=0,quant;
	qtde = ftell(Ptr)/sizeof(TpPizzas);
	qtdePed = ftell(PtrPed)/sizeof(TpPedidos);
	if(Ptr==NULL || PtrPed==NULL)
		printf("ERRO\n");
	else
	{
		for(a=0;a<qtde;a++)
		{
			fseek(Ptr,a,0);
			fread(&pizza,sizeof(TpPizzas),1,Ptr);
			for(b=0;b<qtdePed;b++)
			{
				fseek(PtrPed,b,0);
				fread(&ped,sizeof(TpPedidos),1,PtrPed);
				if(pizza.Cod==ped.CodPizza)
				{
					if(pizza.Status=='A'&&ped.Status=='A')
						quant++;
				}
			}
			if(total<quant)
			{
				total=quant;
				pos=a;
			}
		}
		fseek(Ptr,pos,0);
		fread(&pizza,sizeof(TpPizzas),1,Ptr);
		printf("A pizza mais pedida:\n codigo da pizza: %d\nDescricao %s\nValor %.2f\n",pizza.Cod,pizza.Desc,pizza.Valor);
		fclose(Ptr);
		fclose(PtrPed);
		getch();
	}
	
}

void CliLetra(char Letra) {
    TpClientes cli;
    int qtde = 0, a;
    FILE *PtrC = fopen("ArqCli.dat", "rb");

    if (PtrC == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo\n");
    }
    fseek(PtrC, 0, SEEK_END);
    qtde = ftell(PtrC) / sizeof(TpClientes);
    rewind(PtrC);

    printf("Clientes que começam com a letra %c:\n", Letra);
    for (a = 0; a < qtde; a++) {
        fseek(PtrC, a * sizeof(TpClientes), SEEK_SET);
        fread(&cli, sizeof(TpClientes), 1, PtrC);
        if (cli.Nome[0] == Letra) {
            printf("CEP: %d\nCidade: %s\nEndereco: %s\nNome: %s\nTelefone: %s\n\n",
                   cli.CEP, cli.Cidade, cli.Endereco, cli.Nome, cli.Telefone);
        }
    }

    fclose(PtrC);
}


//falta ordenaçao iserçao direta e busca com sentinela


//int BuscaCliBi (FILE *PtrCli ,int &aux) //Busca Binaria
//{
//	int inicio=0,meio;
//	TpClientes cli;
//	fseek(PtrForn,0,2);
//	int fim = (ftell(PtrCli)/sizeof(TpClientes)) - 1;
//	meio = (inicio+fim)/2;
//	
//	fseek(PtrCli,meio*sizeof(TpClientes),0);
//	fread(&cli, sizeof(TpClientes), 1, PtrCli);
//	while(inicio <= fim && cli.Telefone != aux)
//    {
//    	
//    	if(cli.Telefone < aux)
//        	inicio = meio+1;
//        else
//        	fim = meio-1;
//        	
//        meio = (inicio+fim)/2;
//       
//        fseek(PtrC,meio*sizeof(TpClientes),0);
//        
//        fread(&cli, sizeof(TpClientes), 1, PtrC);
//    }
//    
//    if(cli.Telefone == aux )
//        return meio*sizeof(TpClientes); //encontrou
//    else
//    	return -1; // Produto nao encontrado
//}

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
        gotoxy(i,LF); printf("%c",205); // 205 coluna
    }
    for(i=LI+1; i<LF; i++)
    {
        gotoxy(CI,i); printf("%c",186);
        gotoxy(CF,i); printf("%c",186);
    }
    
    textcolor(7);
    textbackground(0);
}



char MenuPrincipal()
{
	
	char escolha;
	system("cls");
	textcolor(15);
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	
	gotoxy(30,3);
	printf("------ M E N U ------");
	gotoxy(3,8);
	printf("[P] PEDIDOS");
	gotoxy(3,9);
	printf("[M] MOTOQUEIROS");
	gotoxy(3,10);
	printf("[S] SABOR DE PIZZA");
	gotoxy(3,11);
	gotoxy(3,11);
	printf("[C] CLIENTES");
	gotoxy(3,12);
	printf("[E] ESTATISTICAS");
	gotoxy(3,18);
	printf("[R] RELATORIOS");
	printf("[I] INSERIR DADOS");
	printf("[ESC] Sair");
 	return toupper(getche());	
}

char MenuClientes ()
{
	char escolha;
	system("cls");
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	
	gotoxy(30,3);	
	textcolor(RED); 
	printf("----- C L I E N T E S -----");
	gotoxy(3,8);
	textcolor(BLUE);
	printf("[A] CADASTRO");
	gotoxy(3,9);
	printf("[B] CONSULTA");
	gotoxy(3,10);
	printf("[C] EXCLUSAO FISICA");
	gotoxy(3,11);
	printf("[D] EXCLUSAO LOGICA");
	gotoxy(3,11);
	printf("[E] ALTERAR DADOS");
	gotoxy(3,12);
	printf("[F] RELATORIO");
	gotoxy(3,13);
	printf("[ESC] Sair");
	
	return toupper(getche());	
	
}

char MenuMoto ()
{
	char escolha;
	system("cls");
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	
	gotoxy(30,3);	
	textcolor(RED); 
	printf("----- M O T O Q U E I R O S -----");
	gotoxy(3,8);
	textcolor(BLUE);
	printf("[A] CADASTRO");
	gotoxy(3,9);
	printf("[B] CONSULTA");
	gotoxy(3,10);
	printf("[C] EXCLUSAO FISICA");
	gotoxy(3,11);
	printf("[D] EXCLUSAO LOGICA");
	gotoxy(3,11);
	printf("[E] ALTERAR DADOS");
	gotoxy(3,12);
	printf("[F] RELATORIO");
	gotoxy(3,13);
	printf("[ESC] Sair");
	
	return toupper(getche());	
	
}

char MenuPizzas ()
{
	char escolha;
	system("cls");
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	
	gotoxy(30,3);	
	textcolor(RED); 
	printf("----- P I Z Z A S -----");
	gotoxy(3,8);
	textcolor(BLUE);
	printf("[A] CADASTRO");
	gotoxy(3,9);
	printf("[B] CONSULTA");
	gotoxy(3,10);
	printf("[C] EXCLUSAO FISICA");
	gotoxy(3,11);
	printf("[D] EXCLUSAO LOGICA");
	gotoxy(3,11);
	printf("[E] ALTERAR DADOS");
	gotoxy(3,12);
	printf("[F] RELATORIO");
	gotoxy(3,13);
	printf("[ESC] Sair");
	
	return toupper(getche());	
	
}

char MenuRelatorios ()
{
	char escolha;
	system("cls");
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	
	gotoxy(30,3);	
	textcolor(RED); 
	printf("----- R E L A T O R I O S -----");
	gotoxy(3,8);
	textcolor(BLUE);
	printf("[A] MOTOQUEIROS + ENTREGA");
	gotoxy(3,9);
	printf("[B] CLIENTES C. DETERM. LETRA");
	gotoxy(3,10);
	printf("[C] RANKING PED. PIZZAS");
	gotoxy(3,11);
	printf("[D] RELAT. TDS. CLIENTES");
	gotoxy(3,11);
	printf("[E] PIZZAS EM ANDAMENTO");
	gotoxy(3,12);
	printf("[F] PIZZAS A CAMINHO");
	gotoxy(3,13);
	printf("[ESC] Sair");
	
	return toupper(getche());	
	
}

char MenuEstatisticas ()
{
	char escolha;
	system("cls");
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	
	gotoxy(30,3);	
	textcolor(RED); 
	printf("----- E S T A T I S T I C A S -----");
	gotoxy(3,8);
	textcolor(BLUE);
	printf("[A] PIZZA MAIS PEDIDA");
	gotoxy(3,9);
	printf("[B] PIZZA MENOS PEDIDA");
	gotoxy(3,10);
	printf("[C] CLIENTE QUE MAIS CONSOME");
	gotoxy(3,11);
	printf("[D] CLIENTE + CONS. DETERM. TIPO PIZZA");
	gotoxy(3,11);
	printf("[E] MOTOQ. MENOS EXPERI.");
	gotoxy(3,12);
	printf("[F] MOTOQ. QUE ENTREGA + PIZZA");
	gotoxy(3,13);
	printf("[ESC] Sair");
	
	return toupper(getche());	
	
}

char MenuPedido ()
{
	char escolha;
	system("cls");
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	
	gotoxy(30,3);	
	textcolor(RED); 
	printf("----- P E D I D O S -----");
	gotoxy(3,8);
	textcolor(BLUE);
	printf("[A] CADASTRO");
	gotoxy(3,9);
	printf("[B] CONSULTA");
	gotoxy(3,10);
	printf("[C] EXCLUSAO FISICA");
	gotoxy(3,11);
	printf("[D] EXCLUSAO LOGICA");
	gotoxy(3,11);
	printf("[E] ALTERAR DADOS");
	gotoxy(3,12);
	printf("[F] RELATORIO");
	gotoxy(3,13);
	printf("[ESC] Sair");
	
	return toupper(getche());	
	
}


int main(void)
{	
	FILE *Ptr;
	char op,aux;
	
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	
	do

		{
			op=MenuPrincipal();
			switch(toupper(op))
			{
					case'C': 
							gotoxy(30, 2);
							printf("------C L I E N T E S------");
							op=MenuClientes(); 
							switch (toupper(op))
							{
								clrscr();
								case 'A':CadastroClientes();
								break;
								case 'B':ConsultaCli();
								break;  
								case 'C':ExclusaoFisicaCli();
								break;  
								case 'D':ExclusaoLogicaCli();
								break; 
								case 'E':AlterarCliente();
								break;
								case 'F':RelatorioCli();
							break;
							}
					break;
					case 'M':
							gotoxy(30, 2);
							printf("------M O T O Q U E I R O S------");
							op=MenuMoto(); 
							switch (toupper(op))
							{
								clrscr();
								case 'A':CadastroMoto();
								break;
								case 'B':ConsultaMoto();
								break;  
								case 'C':ExclusaoFisicaMoto();
								break;  
							//	case 'D':ExclusaoLogicaMoto(); falta 
								break; 
								case 'E':AlterarMoto();
								break;
								/*case 'F':RelatorioMoto();*/
							break;
							}		
							
					break;
					case 'P':  
							gotoxy(30, 2);
							printf("------P E D I D O S------");
							op=MenuPedido(); 
							switch (toupper(op))
							{
								//clrscr();
								case 'A':CadastroPedidos();
								break;
								
								case 'B':ConsultaPed();
								break;  
								
								case 'C':ExclusaoFisicaPed();
								break;  
								case 'D':ExclusaoLogicaPed();
								break; 
								case 'E':AlterarPed();
								break;
								case 'F':RelatorioPed();
								break;
							}		
							break;
						
					case 'S': 
							gotoxy(30, 2);
							printf("------P I Z Z A S------");
							op=MenuPizzas(); 
							switch (toupper(op))
							{
								clrscr();
								case 'A':CadastroPizzas();
								break;
								case 'B':ConsultaPizza();
								break;  
								case 'C':ExclusaoFisicaPizza();
								break;  
								case 'D':ExclusaoLogicaPizza();
								break; 
								case 'E':AlterarPizza();
								break;
								case 'F':RelatorioPizza();
								break;
							}
					break;
					case 'R': 
							gotoxy(30, 2);
							printf("------R E L A T O R I O S------");
							op=MenuRelatorios(); 
							switch (toupper(op))
							{
								clrscr();
								//case 'A':MOTOQUEIROS MAIS ESNTREGA(); falta
								break;
								case 'B':
									printf("Qual letra deseja procurar?");
									scanf("%c",&aux);
									CliLetra(aux);
									break;  
							//	case 'C':RANKING PED. PIZZA(); falta
							//	break;  
							//	case 'D':RELAT. TODS. CLIEN.(); falta
							//	break; 
								case 'E':PizzaPreparo();
								break;
								case 'F':PizzaCaminho();
								break;
							}
					break;	
					case 'E': 
							gotoxy(30, 2);
							printf("------E S T A T I S T I C A S------");
							op=MenuEstatisticas(); 
							switch (toupper(op))
							{
								clrscr();
								//case 'A':PIZZA MAIS PED(); falta
								break;
							//	case 'B':PIZZA MENOS PED(); falta
								break;  
								case 'C':ConsumoCli();
								break;  
								case 'D':MaisTipoPizza();
								break; 
								//case 'E':MOTO MENOS EXPERIENTE(); falta
								break;
							//	case 'F':MOTO QUE ENTREGA MAIS PIZZA(); falta
								break;
							}
							
					
				
					break;
						
					case 'I':Inseredados() ;
				
					break;

				
						
			}
		}	while(op!= 27); 
		
}

