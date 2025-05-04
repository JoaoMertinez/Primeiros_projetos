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


int BuscaC(FILE*PtrC, char aux[12]) //busca exaustiva 
{
	
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
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	TpClientes cli;
	FILE*PtrC=fopen("ArqCli.dat","ab+");
	if(PtrC==NULL)
	{
		gotoxy(45,6);
		printf("ERRO\n");
	}
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual o numero de telefone?\n");
		fflush(stdin);
		gotoxy(45,7);
		gets(cli.Telefone);
		while(strcmp(cli.Telefone,"0")!=0)
		{
			pos = BuscaC(PtrC,cli.Telefone);
			if(pos==-1)
			{
				gotoxy(45,8);
				printf("Qual o nome do Cliente?\n");
				fflush(stdin);
				gotoxy(45,9);
				gets(cli.Nome);
				gotoxy(45,10);
				printf("Qual o endereco?\n");
				fflush(stdin);
				gotoxy(45,11);
				gets(cli.Endereco);
				gotoxy(45,12);
				printf("Qual a cidade?\n");
				fflush(stdin);
				gotoxy(45,13);
				gets(cli.Cidade);
				gotoxy(45,14);
				printf("Qual o CEP?\n");
				gotoxy(45,15);
				scanf("%d",&cli.CEP);
				cli.Status = 'A';
				fseek(PtrC,0,2);
				fwrite(&cli,sizeof(TpClientes),1,PtrC);
			}
			else
			{
				gotoxy(45,8);
				printf("Cliente ja cadastrado\n");
				getch();
			}
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);
			printf("Qual o numero de telefone?(0 para sair)\n");
			fflush(stdin);
			gotoxy(45,7);
			gets(cli.Telefone);
		}
		fclose(PtrC);
		getch();
	}
}


int buscaP(FILE*PtrP, int aux) //busca sentinela
{
    TpPizzas pizza1, pizza2;

    fseek(PtrP, 0, SEEK_END);
    int qtde = ftell(PtrP) / sizeof(TpPizzas);

//colocando o sentinela
    pizza1.Cod = aux;
    pizza1.Status = 'A';
    fwrite(&pizza1, sizeof(TpPizzas), 1, PtrP);

    fseek(PtrP, 0, SEEK_SET);

    fread(&pizza1, sizeof(TpPizzas), 1, PtrP);
    
    //procurando o elemento
    while ((pizza1.Cod != aux || pizza1.Status != 'A')) {
        fread(&pizza1, sizeof(TpPizzas), 1, PtrP);
    }
    
    // Calcula a posição do registro encontrado
    int posicao = ftell(PtrP) - sizeof(TpPizzas);

    // Desativa a sentinela
    fseek(PtrP, qtde * sizeof(TpPizzas), SEEK_SET); // Posiciona no local da sentinela
    pizza2.Status = 'I';
    fwrite(&pizza2, sizeof(TpPizzas), 1, PtrP);
    
    fseek(PtrP, posicao, SEEK_SET); // Retorna ao registro encontrado
    fread(&pizza1, sizeof(TpPizzas), 1, PtrP);

    if(pizza1.Status == 'A')
        return posicao;
    else
        return -1;
}


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


void CadastroPizzas(void){
	int pos;
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	TpPizzas pizza;
	FILE*PtrP=fopen("ArqP.dat","ab+");
	if (PtrP==NULL)
	{
	
		printf("ERRO\n");
	}
		
	else
		{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
			printf("Codigo da pizza:\n");
			gotoxy(45,7);
			scanf ("%d",&pizza.Cod);
			while(pizza.Cod!=0)
			{
				pos=buscaP(PtrP,pizza.Cod);
				if (pos==-1)
				{
					gotoxy(45,8);
					printf("Sabor da pizza:\n");
					fflush(stdin);
					gotoxy(45,9);
					gets(pizza.Desc);
					gotoxy(45,10);
					printf("Preco da pizza:\n");
					gotoxy(45,11);
					scanf("%f",&pizza.Valor);
					pizza.Status = 'A';
					pizza.quant=0;
				//	SelecaoDiretaPizza(PtrP);
					fseek(PtrP,0,2);
					fwrite(&pizza,sizeof(TpPizzas),1,PtrP);
					
				}
				else	
				{
					gotoxy(45,8);
					printf("Ja esta cadastrado!\n");
				}			
					
					
				getch();
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
				printf("Codigo da pizza:\n");
				gotoxy(45,7);
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
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	gotoxy(45,6);
	FILE*PtrM=fopen("ArqMoto.dat","ab+");
	printf("\nQual o CPF do motoqueiro?\n");
	gotoxy(45,7);
	scanf("%s",&moto.CPF);
	while(strcmp(moto.CPF, "0") != 0)
	{
		pos=BuscaCPF(PtrM,moto.CPF);
		if(pos==-1)
		{
			VCPF=ValidaCPF(moto.CPF);
			if(VCPF==0)
			{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
				printf("CPF invalido!!\n");
			}
				
			else
			{
				gotoxy(45,8);
				printf("Qual o seu nome?\n");
				fflush(stdin);
				gotoxy(45,9);
				gets(moto.Nome);
				gotoxy(45,10);
				printf("Qual o endereco?\n");
				fflush(stdin);
				gotoxy(45,11);
				gets(moto.Endereco);
				gotoxy(45,12);
				printf("Qual o telefone?");
				fflush(stdin);
				gotoxy(45,13);
				gets(moto.Telefone);
				gotoxy(45,14);
				printf("Qual a data de admissao?\n");
				gotoxy(45,15);
				scanf("%d %d %d",&moto.data.d,&moto.data.m,&moto.data.a);
				moto.Status = 'A';
				fseek(PtrM,0,2);
				fwrite(&moto,sizeof(TpMotoqueiros),1,PtrM);
				gotoxy(45,16);
				printf("Cadastro concluido\n");
			}
		}
		else
		{
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);
			printf("Ja cadastrado\n");
		}
			
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);	
		printf("Qual o CPF do motoqueiro?\n");
		gotoxy(45,7);
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
	
	int pos,quant=0, posN,auxP,posP,posM, auxPed;
	char auxCPF[12],auxC[12];
	TpClientes cli ;
	TpMotoqueiros moto;
	TpPedidos ped;
	TpPizzas pizza;
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	gotoxy(45,6);
	FILE*PtrPe=fopen("ArqPed.dat","ab+");
	FILE*PtrM=fopen("ArqMoto.dat","rb");
	FILE*PtrC=fopen("ArqCli.dat","rb");
	FILE*PtrP=fopen("ArqP.dat","rb+");
	if (PtrPe == NULL || PtrM == NULL || PtrC == NULL || PtrP == NULL)
		printf("Erro de abertura");
	else 
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual o numero do pedido?\n");
		gotoxy(45,7);
		scanf("%d",&auxPed);
		while(auxPed!=0)
		{
			pos=BuscaSeqNum(PtrPe,auxPed);
			if(pos==-1)
			{
				gotoxy(45,8);
				printf("Qual o numero de telefone?\n");
				fflush(stdin);
				gotoxy(45,9);
				gets(auxC);
				posN=BuscaC(PtrC,auxC);
				if(posN==-1)
				{
					gotoxy(45,10);
					printf("Cliente nao cadastrado!!\n");
				}
					
				else
				{
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					gotoxy(45,10);
					printf("Qual o codigo da pizza?\n");
					gotoxy(45,11);
					scanf("%d",&auxP);
					posP=buscaP(PtrP,auxP);
					if(posP==-1)
					{
						gotoxy(45,12);
						printf("Pizza nao cadastrada\n");
					}
						
						else
						{
							clrscr();
							Moldura(2,2,92,4,14,1); // MOLDURA AZUL
							Moldura(2,5,30,21,12,7); // MOLDURA BEJE
							Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
							Moldura(31,5,92,21,9,6);//AMARELA
							Moldura(1,1,93,25,10,5);//MOLDURA ROXA
							gotoxy(45,12);
							printf("Qual o CPF do motoqueiro: \n");
							gotoxy(45,13);
							scanf("%s", &auxCPF);
							posM=BuscaCPF(PtrM,auxCPF);
							if (posM == -1)
							{
								gotoxy(45,14);
								printf("CPF nao encontrado"); 
							}
								
							else 
							{
									clrscr();
									Moldura(2,2,92,4,14,1); // MOLDURA AZUL
									Moldura(2,5,30,21,12,7); // MOLDURA BEJE
									Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
									Moldura(31,5,92,21,9,6);//AMARELA
									Moldura(1,1,93,25,10,5);//MOLDURA ROXA
									gotoxy(45,14);
									printf("Data do pedido\n");
									gotoxy(45,15);
									scanf("%d %d %d",&ped.datapedido.d,&ped.datapedido.m,&ped.datapedido.a);
									
									fseek(PtrP, posP, SEEK_SET); 
									fread(&pizza, sizeof(TpPizzas), 1, PtrP); 
									pizza.quant+=1; 
									fseek(PtrP, posP, SEEK_SET); 
									fwrite(&pizza, sizeof(TpPizzas), 1, PtrP); 
									
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
			{
				gotoxy(45,16);
				printf("Pedido ja existente!");
			}
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);				
			printf("Qual o numero do pedido?\n");
			gotoxy(45,7);
			scanf("%d", &auxPed);
		}			
	}
	fclose(PtrPe);
	fclose( PtrM );
	fclose(PtrC); 
	fclose(PtrP);
	
}



void AlterarCliente(void)
{
	clrscr();
	int posA;
	TpClientes cli;
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	FILE*PtrC=fopen("ArqCli.dat","rb+");
	if(PtrC==NULL)
	{
		gotoxy(45,6);
		printf("erro de abertura\n");
	}
		
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual o numero de telefone do cliente pra alterar?\n");
		fflush(stdin);
		gotoxy(45,7);
		gets(cli.Telefone);
		while(cli.Telefone!=0 || cli.Status=='A')
		{
			posA=BuscaC(PtrC,cli.Telefone);
			if(posA==-1)
			{
				gotoxy(45,8);
				printf("Nao cadastrado!!\n");
			}
				
			else
			{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,8);
				fseek(PtrC,posA,0);
				fread(&cli,sizeof(TpClientes),1,PtrC);
				printf("Nome %s\n", cli.Nome);
				gotoxy(45,9);
				printf("CEP do cliente: %d\n", cli.CEP);
				gotoxy(45,10);
				printf("Cidade do cliente: %s\n", cli.Cidade); 
				gotoxy(45,11);
				printf("Endereço do cliente: %s\n",cli.Endereco);
				gotoxy(45,12);
				printf("Status do cliente %s\n",cli.Status);
				gotoxy(45,13);
				printf("Telefone do cliente %s\n",cli.Telefone);
				gotoxy(45,14);
				printf("Deseja alterar o nome?(S/N)");
				if(toupper(getche())=='S')
				{
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					gotoxy(45,6);
					printf("digite o novo nome:\n");
					fflush(stdin);
					gotoxy(45,7);
					gets(cli.Nome);
					fseek(PtrC,posA,0);
					fwrite(&cli,sizeof(TpClientes),1,PtrC);
					gotoxy(45,8);
					printf("Nome alterado!!\n");
				}
				else
				{
					gotoxy(45,15);
					printf("Alteracao negada!!\n");
				}
				
			}
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);
			printf("Qual o numero de telefone do cliente pra alterar?\n");
			fflush(stdin);
			gotoxy(45,7);
			gets(cli.Telefone);
		}
	}
	fclose(PtrC);
	getch();			
}



void AlterarMoto(void)
{
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	int posA;
	TpMotoqueiros moto;
	FILE*PtrM=fopen("ArqMoto.dat","rb+");
	if(PtrM==NULL)
	{
		gotoxy(45,6);
		printf("erro de abertura\n");
	}
	
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual o CPF do motoqueiro que deseja alterar?\n");
		fflush(stdin);
		gotoxy(45,7);
		gets(moto.CPF);
		while(moto.CPF!=0 || moto.Status=='A')
		{
			posA=BuscaCPF(PtrM,moto.CPF);
			if(posA==-1)
			{
				gotoxy(45,8);
				printf("Nao cadastrado!!\n");
			}
				
			else
			{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,8);
				fseek(PtrM,posA,0);
				fread(&moto,sizeof(TpMotoqueiros),1,PtrM);
				printf("Nome: %s\n",moto.Nome);
				gotoxy(45,9);
				printf("CPF %s\n", moto.CPF);
				gotoxy(45,10);
				printf("Endereço: %s\n", moto.Endereco); 
				gotoxy(45,11);
				printf("Status do motoqueiro%s\n",moto.Status);
				gotoxy(45,12);
				printf("Telefone do motoqueiro %s\n",moto.Telefone);
				gotoxy(45,13);
				printf("Deseja alterar o nome?(S/N)");
				if(toupper(getche())=='S')
				{
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					gotoxy(45,6);
					printf("digite o novo nome:\n");
					fflush(stdin);
					gotoxy(45,7);
					gets(moto.Nome);
					fseek(PtrM,posA,0);
					fwrite(&moto,sizeof(TpMotoqueiros),1,PtrM);
					gotoxy(45,8);
					printf("Nome alterado!!\n");
				}
				else
				{
					gotoxy(45,14);
					printf("Alteracao negada!!\n");
				}
					
			}
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);
			printf("Qual o CPF do motoqueiro que deseja alterar?\n");
			fflush(stdin);
			gotoxy(45,7);
			gets(moto.CPF);
		}
	}
	fclose(PtrM);
	getch();
	
}



void AlterarPed(void)
{
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	int posA;
	TpPedidos ped;
	TpClientes cli;
	FILE*PtrA=fopen("ArqPed.dat","rb+");
	if(PtrA==NULL)
	{
		gotoxy(45,6);
		printf("erro de abertura\n");
	}
		
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual pedido deseja alterar?\n");
		gotoxy(45,7);
		scanf("%d",&ped.NumPedido);
		while(ped.NumPedido!=0 || ped.Status=='A')
		{
			posA=BuscaSeqNum(PtrA,ped.NumPedido);
			if(posA==-1)
			{
				gotoxy(45,8);
				printf("Nao cadastrado!!\n");
			}
				
			else
			{
				fseek(PtrA,posA,0);
				fread(&ped,sizeof(TpPedidos),1,PtrA);
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,8);
				printf("Codigo do pedido: %d\n", ped.NumPedido);
				gotoxy(45,9);
				printf("Codigo da pizza: %d\n", ped.CodPizza); 
				gotoxy(45,10);
				printf("CPF do cliente: %s\n",ped.CPF);
				gotoxy(45,11);
				printf("Numero de telefone %s\n", ped.Telefone);
				gotoxy(45,12);
				printf("Data do pedido %d %d %d\n",ped.datapedido);
				gotoxy(45,13);
				printf("Situacao do pedido %d\n",ped.Situacao);
				gotoxy(45,14);
				printf("Deseja alterar a situacao?(S/N)");
				if(toupper(getche())=='S')
				{
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					gotoxy(45,6);
					printf("digite (1 em preparo; 2 a caminho; 3 entregue");
					gotoxy(45,7);
					scanf("%d",&ped.Situacao);
					fseek(PtrA,posA,0);
					fwrite(&ped,sizeof(TpPedidos),1,PtrA);
					gotoxy(45,8);
					printf("Situacao alterada!!\n");
				}
				else
				{
					gotoxy(45,15);
					printf("Alteracao negada!!\n");
				}
					
			}
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);
			printf("Qual pedido deseja alterar?\n");
			gotoxy(45,7);
			scanf("%d",&ped.NumPedido);
		}
	}
	fclose(PtrA);
	getch();			
}


void AlterarPizza(void)
{
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	int posA;
	TpPizzas pizza;
	FILE*PtrP=fopen("ArqP.dat","rb+");
	if(PtrP==NULL)
	{
		gotoxy(45,6);
		printf("erro de abertura\n");
	}
		
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Digite o codigo da pizza que deseja alterar\n");
		gotoxy(45,7);
		scanf("%d",&pizza.Cod);
		while(pizza.Cod!=0 || pizza.Status=='A')
		{
			posA=buscaP(PtrP,pizza.Cod);
			if(posA==-1)
			{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,8);
				printf("Nao cadastrado!!\n");
			}
				
			else
			{
				fseek(PtrP,posA,0);
				fread(&pizza,sizeof(TpPizzas),1,PtrP);
				gotoxy(45,8);
				printf("Codigo da pizza: %d\n", pizza.Cod);
				gotoxy(45,9);
				printf("Descricao da pizza: %s\n", pizza.Desc);
				gotoxy(45,10); 
				printf("Status da pizza %s\n",pizza.Status);
				gotoxy(45,11);
				printf("Valor da pizza %.2f\n", pizza.Valor);
                gotoxy(45,12);
				printf("Deseja alterar o sabor?(S/N)");
				if(toupper(getche())=='S')
				{
					
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					gotoxy(45,6);
					printf("digite o novo sabor:\n");
					fflush(stdin);
					gotoxy(45,7);
					gets(pizza.Desc);
					fseek(PtrP,posA,0);
					fwrite(&pizza,sizeof(TpPizzas),1,PtrP);
					gotoxy(45,8);
					printf("Sabor alterado!!\n");
				}
				else
				{
					gotoxy(45,13);
					printf("Alteracao negada!!\n");
				}
					
			}
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);
			printf("Digite o codigo da pizza que deseja alterar\n");
			gotoxy(45,7);
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
    pizza.quant = 2;
    fwrite(&pizza, sizeof(TpPizzas), 1, PtrP);
   
    
    pizza.Cod = 12;
    strcpy(pizza.Desc, "queijo");
    pizza.Valor = 40;
    pizza.Status = 'A';
    pizza.quant = 1;
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
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	TpPedidos ped;
	FILE*PtrPe = fopen("ArqPed.dat","rb");
	int a;
	if(PtrPe==NULL)
	{
		gotoxy(45,6);
		printf("ERRo\n");
	}
		
	else
	{
		fread(&ped,sizeof(TpPedidos),1,PtrPe);
		while(!feof(PtrPe))
		{
			if(ped.Situacao == 2)
			{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
				printf("Codigo da pizza a caminho %d",ped.NumPedido);
			}
				
			fread(&ped,sizeof(TpPedidos),1,PtrPe);
		}
	}
	fclose(PtrPe);
	getch();	
}

void PizzaPreparo(void)
{
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	TpPedidos ped;
	FILE*PtrPe = fopen("ArqPed.dat","rb");
	int a;
	if(PtrPe==NULL)
	{
		gotoxy(45,6);
		printf("ERRo\n");
	}
		
	else
	{
		fread(&ped,sizeof(TpPedidos),1,PtrPe);
		while(!feof(PtrPe))
		{
			if(ped.Situacao == 1)
			{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
				printf("Codigo da pizza em preparo %d",ped.NumPedido);
			}
				
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
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	FILE*PtrC=fopen("ArqCli.dat","rb");
	if(PtrC==NULL)
	{
		gotoxy(45,6);
		printf("ERRO\n");
	}
		
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual o telefone do cliente deseja consultar?\n");
		fflush(stdin);
		gotoxy(45,7);
		gets(aux);
		while(strcmp(aux,"0")!=0)
		{
			pos = BuscaC(PtrC,aux);
			if(pos==-1)
			{
				gotoxy(45,8);
				printf("Cliente nao cadastrado!!");
			}
				
			else
			{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
				fseek(PtrC,pos,0);
				fread(&cli,sizeof(TpClientes),1,PtrC);
				printf("Telefone %s \nCEP %d \nCidade %s \nEndereco %s \nNome %s",cli.Telefone,cli.CEP,cli.Cidade,cli.Endereco,cli.Nome);			
			}
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);
			printf("Qual o telefone do cliente deseja consultar?\n");
			fflush(stdin);
			gotoxy(45,7);
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
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	TpMotoqueiros moto;
	FILE*PtrM=fopen("ArqMoto.dat","rb");
	if(PtrM==NULL)
	{
		gotoxy(45,6);
		printf("ERRO\n");
	}
		
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual o CPF do motoqueiro que deseja consultar?\n");
		fflush(stdin);
		gotoxy(45,7);
		gets(aux);
		while(strcmp(aux,"\0")!=0)
		{
			pos = BuscaCPF(PtrM,aux);
			if(pos==-1)
			{
				gotoxy(45,8);
				printf("CPF nao cadastrado!!");
			}
				
			else
			{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				fseek(PtrM,pos,0);
				fread(&moto,sizeof(TpMotoqueiros),1,PtrM);
				gotoxy(45,8);
				printf("CPF: %s\n", moto.CPF);
				gotoxy(45,9);
                printf("Data: %d/%d/%d\n", moto.data.d, moto.data.m, moto.data.a);
                gotoxy(45,10);
                printf("Endereco: %s\n", moto.Endereco);
                gotoxy(45,11);
                printf("Nome: %s\n", moto.Nome);
                gotoxy(45,12);
                printf("Telefone: %s\n", moto.Telefone);			
			}
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);
			printf("Qual o CPF do motoqueiro que deseja consultar?\n");
			fflush(stdin);
			gotoxy(45,7);
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
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	FILE*PtrP=fopen("ArqP.dat","rb");
	if(PtrP==NULL)
	{
		gotoxy(45,6);
		printf("ERRO\n");
	}
		
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual o codigo da pizza que deseja consultar?\n");
		gotoxy(45,7);
		scanf("%d", &aux);
		while(aux!=0)
		{
			pos = buscaP(PtrP,aux);
			if(pos==-1)
			{
				gotoxy(45,8);
				printf("Codigo nao cadastrado!!");
				getch();
			}
			else
			{
				fseek(PtrP,pos,0);
				fread(&pizza,sizeof(TpPizzas),1,PtrP);
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
				printf("Codigo %d \nDescricao %s \nValor %.2f\nQuantidade vendida:%d\n",pizza.Cod,pizza.Desc,pizza.Valor,pizza.quant);			
			}
			clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
			printf("Qual o codigo da pizza que deseja consultar?\n");
			gotoxy(45,7);
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
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	if(PtrPed==NULL)
	{
		gotoxy(45,6);
		printf("ERRO\n");
	}
		
	else{
		
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual o codigo do pedido que deseja consultar?\n");
		gotoxy(45,7);
		scanf("%d", &aux);
		while(aux!=0)
		{
			pos = BuscaSeqNum(PtrPed,aux);
			if(pos==-1)
			{
				gotoxy(45,8);
				printf("Codigo nao cadastrado!!");
			}
		
			else
			{
				fseek(PtrPed,pos,0);
				fread(&ped,sizeof(TpPedidos),1,PtrPed);
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,8);
				printf("Codigo: %d\n", ped.CodPizza);
				gotoxy(45,9);
                printf("CPF: %s\n", ped.CPF);
                gotoxy(45,10);
                printf("Data: %d/%d/%d\n", ped.datapedido.d, ped.datapedido.m, ped.datapedido.a);
                gotoxy(45,11);
                printf("Numero do Pedido: %d\n", ped.NumPedido);
                gotoxy(45,12);
                printf("Situacao: %d\n", ped.Situacao);
                gotoxy(45,13);
                printf("Telefone:%s\n", ped.Telefone);			
			}
			clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
			printf("Qual o codigo do pedido que deseja consultar?\n");
			gotoxy(45,7);
			scanf("%d", &aux);
		}
	}
	fclose(PtrPed);
	getch();
}

void RelatorioCli(void)
{
	TpClientes cli;
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	gotoxy(45,6);
	printf("------ RELATORIO CLIENTES ------\n");
	FILE*PtrC=fopen("ArqCli.dat","rb");
	if(PtrC==NULL)
	{
		gotoxy(45,7);
		printf("ERRO\n");
	}
		
	else
	{
		fseek(PtrC,0,0);
		fread(&cli,sizeof(TpClientes),1,PtrC);
		while(!feof(PtrC))
		{
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);
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
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	gotoxy(45,6);
	printf("------ RELATORIO PIZZAS ------\n");
	FILE*PtrP=fopen("ArqP.dat","rb+");
	
	if(PtrP==NULL)
	{
		gotoxy(45,7);
		printf("ERRO\n");
	}
		
	else
	{
		fseek(PtrP,0,0);
		fread(&p,sizeof(TpPizzas),1,PtrP);
		while(!feof(PtrP))
		{	
			if(p.quant==0)
			{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
				printf("\npizza sem venda: ");
			}
				
			
			if(p.quant>0)
			{
				gotoxy(45,7);
				printf("\nquantidade vendida: %d");
			}
				
			gotoxy(45,8);
			printf("Codigo %d Sabor %s Valor %.2f\n",p.Cod,p.Desc,p.Valor);
			
			fread(&p,sizeof(TpPizzas),1,PtrP);
		}
		
		fclose(PtrP);
		getch();
	}	
}


void RelatorioPed(void)
{
	TpPedidos ped;
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	gotoxy(45,6);
	printf("------ RELATORIO PEDIDOS ------\n");
	FILE*PtrPe=fopen("ArqPed.dat","rb");
	if(PtrPe==NULL)
	{
		gotoxy(45,7);
		printf("\nERRO");
	}
		
	else
	{
		fseek(PtrPe,0,0);
		fread(&ped,sizeof(TpPedidos),1,PtrPe);
		while(!feof(PtrPe))
		{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
			printf("Cod pizza %d \nCPF %s \nData %d %d %d \nNum ped %d \nSituacao %d\n Status %c\n Telefone %s\n",ped.CodPizza, ped.CPF, ped.datapedido.d, ped.datapedido.m, ped.datapedido.a,ped.NumPedido,ped.Situacao,ped.Status,ped.Telefone);
			fread(&ped,sizeof(TpPedidos),1,PtrPe);
		}
		fclose(PtrPe);
		getch();
	}	
}

void RelatorioMoto(void)
{
	TpMotoqueiros moto;
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	gotoxy(45,6);
	printf("------ RELATORIO MOTOQUEIROS ------\n");
	FILE*PtrM=fopen("ArqMoto.dat","rb");
	
	if(PtrM==NULL)
	{
		gotoxy(45,7);
		printf("ERRO\n");
	}
		
	else
	{
		fseek(PtrM,0,0);
		fread(&moto,sizeof(TpMotoqueiros),1,PtrM);
		while(!feof(PtrM))
		{
			//getch();
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);
			printf("CPF %s \nData %d %d %d \n \nEndereco %s \nNome %s\n Status %c\n Telefone %s\n", moto.CPF, moto.data.d, moto.data.m, moto.data.a, moto.Endereco, moto.Nome, moto.Status, moto.Telefone);

			fread(&moto,sizeof(TpMotoqueiros),1,PtrM);
		}
		getch();
		fclose(PtrM);
	}
}


void ExclusaoFisicaCli(void)
{
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	gotoxy(45,6);
	printf("------ EXCLUSAO FISICA CLIENTES -----");
	TpClientes cli;
	int pos;
	char aux[12];
	FILE*PtrC=fopen("ArqCli.dat","rb");
	if(PtrC==NULL)
	{
		gotoxy(45,7);
		printf("ERRO\n");
	}
		
	else
	{
		
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual telefone deseja excluir!!\n");
		fflush(stdin);
		gotoxy(45,7);
		gets(aux);
		if(strcmp(aux, "0")!=0)
		{
			pos = BuscaC(PtrC,aux);
			if(pos==-1)
			{	
				gotoxy(45,8);
				printf("Cliente nao cadastrado\n");
				getch();
			}
			
			else
			{
					clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				fseek(PtrC,pos,0);
				fread(&cli,sizeof(TpClientes),1,PtrC);
				gotoxy(45,6);
				printf("---- Detalhes do registro ----\n");
				gotoxy(45,7);
				printf("Telefone %s \tCEP %d \tCidade %s \tEndereco %s \tNome %s", cli.Telefone,cli.CEP,cli.Cidade,cli.Endereco,cli.Nome);
			    gotoxy(45,8);
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
					gotoxy(45,9);
					printf("---- Registro deletado ----\n");
					getch();
				}
				else
				{
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					printf("---- Exclusao Negada ----\n");
				}
					
			}
		}
		
	}
	fclose(PtrC);
}


void ExclusaoFisicaPed(void)
{
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	gotoxy(45,6);
	printf("------ EXCLUSAO FISICA PEDIDOS -----");
	TpPedidos ped;
	TpPizzas pizza;
	int pos, aux, posP;
	FILE*PtrPe=fopen("ArqPed.dat","rb");
	FILE*PtrP=fopen("ArqP.dat","rb+");
	if(PtrPe==NULL || PtrP==NULL)
	{
		gotoxy(45,7);
		printf("ERRO\n");
	}
		
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,7);
		printf("Qual o codigo deseja excluir!!\n");
		gotoxy(45,8);
		scanf("%d",&aux);
		if(aux!=0)
		{
			pos = BuscaSeqNum(PtrPe,aux);
			if(pos==-1)
			{	
				gotoxy(45,9);
				printf("Pedido nao cadastrado\n");
				getch();
			}
			
			else
			{
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				fseek(PtrPe,pos,0);
				fread(&ped,sizeof(TpPedidos),1,PtrPe);
				gotoxy(45,6);
				printf("---- Detalhes do registro ----\n");
				gotoxy(45,7);
				printf("Codigo da pizza %d\n",ped.CodPizza);
				gotoxy(45,8);
				printf("CPF do motoqueiro %s\n",ped.CPF);
				gotoxy(45,9);
				printf("Data do pedido %d/%d/%d\n",ped.datapedido.d,ped.datapedido.m,ped.datapedido.a);
				gotoxy(45,10);
				printf("Numero do pedido %d\n",ped.NumPedido);
				gotoxy(45,11);
				printf("Situacao %d\n",ped.Situacao);
				gotoxy(45,12);
				printf("Telefone do cliente %s\n",ped.Telefone);
				gotoxy(45,13);
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
					gotoxy(45,14);
					printf("---- Registro deletado ----\n");
					getch();
				}
				else
				{
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					gotoxy(45,6);
					printf("---- Exclusao Negada ----\n");
					
				}
				
			}
		}
		
	}
	fclose(PtrPe);
}


void ExclusaoFisicaMoto(void)
{
	FILE*Ptr=fopen("ArqMoto.dat","rb");
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	TpMotoqueiros moto;
	char aux[12];
	int pos;
	if(Ptr==NULL)
	{
		gotoxy(45,6);
		printf("ERRO\n");
	}
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual CPF deseja excluir?\n");
		fflush(stdin);
		gotoxy(45,7);
		scanf("%s",&aux);
		if(strcmp(aux,"0")!=0)
		{
			pos = BuscaCPF(Ptr,aux);
			if(pos==-1)
			{
				gotoxy(45,8);
				printf("Motoqueiro nao cadastrado!!\n");
				getch();
			}
			else
			{
				fseek(Ptr,pos,0);
				fread(&moto,sizeof(TpMotoqueiros),1,Ptr);
					clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
				printf("CPF: %s\n",moto.CPF);
				gotoxy(45,7);
				printf("Data de admissao: %d/%d/%d\n",moto.data.d,moto.data.m,moto.data.a);
				gotoxy(45,8);
				printf("Endereco: %s\n",moto.Endereco);
				gotoxy(45,9);
				printf("Nome: %s\n",moto.Nome);
				gotoxy(45,10);
				printf("Telefone: %s\n",moto.Telefone);
				gotoxy(45,11);
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
					gotoxy(45,12);
					printf("Exclusao concluida\n!!");
					getch();	
				}
				else
				{
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					gotoxy(45,6);
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
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	int aux,pos;
	if(Ptr==NULL)
	{
		gotoxy(45,6);
		printf("ERRO!\n");
	}
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual o codigo deseja excluir?\n");
		gotoxy(45,7);
		scanf("%d",&aux);
		if(aux!=0)
		{
			pos= buscaP(Ptr,aux);
			if(pos==-1)
			{
				gotoxy(45,8);
				printf("Pizza nao cadastrada!!\n");
			}
			else
			{
				fseek(Ptr,pos,0);
				fread(&pizza,sizeof(TpPizzas),1,Ptr);
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
				printf("Codigo da pizza: %d\n",pizza.Cod);
				gotoxy(45,7);
				printf("Descricao: %s\n",pizza.Desc);
				gotoxy(45,8);
				printf("Valor: %.2f",pizza.Valor);
				gotoxy(45,9);
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
					gotoxy(45,10);
					printf("Exclusao concluida\n");
					getch();
				}
				else
				{
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					gotoxy(45,6);
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
	clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					gotoxy(45,6);
	FILE*PtrP=fopen("ArqPed.dat","rb+");
	if(PtrP==NULL)
	{
		gotoxy(45,6);
		printf("Erro\n");
	}
		
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual codigo do pedido que deseja excluir?\n");
		gotoxy(45,7);
		scanf("%d",&ped.NumPedido);
		while(ped.NumPedido!=0)
		{
			pos=BuscaSeqNum(PtrP,ped.NumPedido);
			if(pos==-1)
			{
				gotoxy(45,8);
				printf("Codigo nao cadastrado\n");
			}
				
			else
			{
				fseek(PtrP,pos,0);
				fread(&ped,sizeof(TpPedidos),1,PtrP);
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
				printf("Codigo da pizza %d, CPF do motoqueiro %s\n Telefone do cliente %s\n data do pedido %d %d %d\n numero do pedido %d\n Situacao do pedido %d\n", ped.CodPizza, ped.CPF, ped.Telefone, ped.datapedido,ped.NumPedido, ped.Situacao);
			    gotoxy(45,7);
				printf("Deseja excluir(S/N)\n");
				if(toupper(getche())=='S')
				{
					fseek(PtrP,pos,0);
					ped.Status = 'I';
					fwrite(&ped,sizeof(TpPedidos),1,PtrP);
					gotoxy(45,8);
					printf("Exclusao Logica concluida\n");
				}
				else
				{
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					gotoxy(45,6);
					printf("Exclusao negada!!\n");
				}
			}
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROXA
			gotoxy(45,6);
			printf("Qual codigo do pedido que deseja excluir?\n");
			gotoxy(45,7);
			scanf("%d",&ped.NumPedido);
		}
	}
	fclose(PtrP);
	getch();
}


void ExclusaoLogicaCli(void)
{
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	FILE*Ptr=fopen("ArqCli.dat","rb+");
	TpClientes cli;
	char aux[12];
	int pos;
	if(Ptr==NULL)
	{
		gotoxy(45,6);
		printf("ERRO!!\n");
	}
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("Qual Telefone deseja excluir?\n");
		fflush(stdin);
		gotoxy(45,7);
		gets(aux);
		if(strcmp(aux,"0")!=0)
		{
			pos= BuscaC(Ptr,aux);
			if(pos==-1)
			{
				gotoxy(45,8);
				printf("Cliente nao cadastrado!!\n");
				getch();
			}
			else
			{
				fseek(Ptr,pos,0);
				fread(&cli,sizeof(TpClientes),1,Ptr);
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROXA
				gotoxy(45,6);
				printf("CEP: %d\n",cli.CEP);
				gotoxy(45,7);
				printf("Cidade: %s\n",cli.Cidade);
				gotoxy(45,8);
				printf("Endereco: %s\n",cli.Endereco);
				gotoxy(45,9);
				printf("Nome: %s\n",cli.Nome);
				gotoxy(45,10);
				printf("Telefone: %s\n",cli.Telefone);
				gotoxy(45,11);
				printf("Deseja excluir?(S/N)\n");
				if(toupper(getche())=='S')
				{
					fseek(Ptr,pos,0);
					cli.Status = 'I';
					fwrite(&cli,sizeof(TpClientes),1,Ptr);
					gotoxy(45,12);
					printf("Cliente Inativo!!");
				}
				else
				{
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROXA
					gotoxy(45,6);
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
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROX
	TpPizzas pizza;
	int aux,pos;
	if(Ptr==NULL)
	{
		gotoxy(45,6);
		printf("ERRO\n");
	}
	else
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROX
		gotoxy(45,6);
		printf("Qual codigo deseja excluir?n");
		gotoxy(45,7);
		scanf("%d",&aux);
		if(aux!=0)
		{
			pos=buscaP(Ptr,aux);
			if(pos==-1)
			{
				gotoxy(45,8);
				printf("Pizza nao cadastrada\n");
				getch();
			}
			else
			{
				fseek(Ptr,pos,0);
				fread(&pizza,sizeof(TpPizzas),1,Ptr);
				clrscr();
				Moldura(2,2,92,4,14,1); // MOLDURA AZUL
				Moldura(2,5,30,21,12,7); // MOLDURA BEJE
				Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
				Moldura(31,5,92,21,9,6);//AMARELA
				Moldura(1,1,93,25,10,5);//MOLDURA ROX
				gotoxy(45,6);
				printf("Codigo da pizza: %s\n",pizza.Cod);
				gotoxy(45,7);
				printf("Descricao: %s\n",pizza.Desc);
				gotoxy(45,8);
				printf("Valor: %.2f\n",pizza.Valor);
				gotoxy(45,9);
				printf("Desseja excluir?(S/N)\n");
				if(toupper(getche())=='S')
				{
					fseek(Ptr,pos,0);
					pizza.Status = 'I';
					fwrite(&pizza,sizeof(TpPizzas),1,Ptr);
					gotoxy(45,10);
					printf("Pizza inativa!!\n");
					getch();
				}
				else
				{
					clrscr();
					Moldura(2,2,92,4,14,1); // MOLDURA AZUL
					Moldura(2,5,30,21,12,7); // MOLDURA BEJE
					Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
					Moldura(31,5,92,21,9,6);//AMARELA
					Moldura(1,1,93,25,10,5);//MOLDURA ROX
					gotoxy(45,6);
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
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROX
	TpPedidos ped;
	TpClientes cli;
	int quant=0,a,b,qtde=0, quantPe=0, total=0, pos=0;
	quant = ftell(Ptr)/sizeof(TpClientes);
	quantPe = ftell(PtrPe)/sizeof(TpPedidos);//TL
	if(Ptr==NULL||PtrPe==NULL)
	{
		gotoxy(45,6);
		printf("ERRO\n");
	}
	
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
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROX
	gotoxy(45,6);
	printf("O Cliente que mais consome e: Cep: %d, Cidade: %s, Endereco: %s, Nome: %s, Telefone %d", cli.CEP,cli.Cidade,cli.Endereco,cli.Nome,cli.Telefone);
	fclose(Ptr);
	fclose(PtrPe);
	getch();
}

void MaisTipoPizza(void)
{
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROX
	gotoxy(45,6);
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
	{
		gotoxy(45,7);
		printf("ERRO\n");
	}
		
	else
	{
			clrscr();
			Moldura(2,2,92,4,14,1); // MOLDURA AZUL
			Moldura(2,5,30,21,12,7); // MOLDURA BEJE
			Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
			Moldura(31,5,92,21,9,6);//AMARELA
			Moldura(1,1,93,25,10,5);//MOLDURA ROX
			gotoxy(45,6);
		printf("Qual o codigo da pizza?\n");
		gotoxy(45,7);
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
		gotoxy(45,8);
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
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA ROXA
	FILE*Ptr=fopen("ArqP.dat","rb");
	FILE*PtrPed=fopen("ArqPed.dat","rb");
	int qtde=0, qtdePed=0,a,b, pos=0, total=0,quant;
	qtde = ftell(Ptr)/sizeof(TpPizzas);
	qtdePed = ftell(PtrPed)/sizeof(TpPedidos);
	if(Ptr==NULL || PtrPed==NULL)
	{
		gotoxy(45,6);
		printf("ERRO\n");
	}
		
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
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA ROXA
		gotoxy(45,6);
		printf("A pizza mais pedida:\n codigo da pizza: %d\nDescricao %s\nValor %.2f\n",pizza.Cod,pizza.Desc,pizza.Valor);
		fclose(Ptr);
		fclose(PtrPed);
		getch();
	}
	
}


void CliLetra(char Letra) {
    TpClientes cli;
    int qtde = 0, a;
    clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA
    FILE *PtrC = fopen("ArqCli.dat", "rb");
	qtde = ftell(PtrC) / sizeof(TpClientes);
	
    if (PtrC == NULL) 
	{
		gotoxy(45,6);
        printf("ERRO: Não foi possível abrir o arquivo\n");
        getch();
    }
    clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA
	gotoxy(45,6);
    printf("Clientes que começam com a letra %c:\n", Letra);
    for (a = 0; a < qtde; a++) {
        fseek(PtrC, a * sizeof(TpClientes), SEEK_SET);
        fread(&cli, sizeof(TpClientes), 1, PtrC);
        if (cli.Nome[0] == Letra) {
        	gotoxy(45,7);
            printf("CEP: %d\nCidade: %s\nEndereco: %s\nNome: %s\nTelefone: %s\n\n",
                   cli.CEP, cli.Cidade, cli.Endereco, cli.Nome, cli.Telefone);
            getch();
        }
    }

    fclose(PtrC);
}



void PizzaMaisPedida(void)
{
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA
	 FILE *Ptr = fopen("ArqP.dat", "rb");
    TpPizzas pizza, maisPedida;

    if (Ptr == NULL) {
    	gotoxy(45,6);
        printf("ERRO\n");
        getch();
    }

    fseek(Ptr, 0,0);
	fread(&pizza, sizeof(TpPizzas), 1, Ptr);
    if (pizza.quant==0) 
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA
		gotoxy(45,6);
        printf("Nenhum pedido encontrado\n");
        fclose(Ptr);
        getch();
    } else {
        maisPedida = pizza;
    }

	fread(&pizza, sizeof(TpPizzas), 1, Ptr);
    while (!feof(Ptr)) 
	{
        if (pizza.quant > maisPedida.quant) {
            maisPedida = pizza;
        }
        fread(&pizza, sizeof(TpPizzas), 1, Ptr);
    }
	gotoxy(45,7);
    printf("A pizza menos pedida:\n");
    gotoxy(45,8);
    printf("Codigo: %d\n", maisPedida.Cod);
    gotoxy(45,9);
    printf("Sabor: %s\n", maisPedida.Desc);
    gotoxy(45,10);
    printf("Quantidade de vendas: %d\n", maisPedida.quant);
    gotoxy(45,11);
    printf("Valor: %.2f\n", maisPedida.Valor);


    fclose(Ptr);
    getch();
}

void PizzaMenosPedida(void)
{
	clrscr();
	Moldura(2,2,92,4,14,1); // MOLDURA AZUL
	Moldura(2,5,30,21,12,7); // MOLDURA BEJE
	Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
	Moldura(31,5,92,21,9,6);//AMARELA
	Moldura(1,1,93,25,10,5);//MOLDURA
	gotoxy(45,6);
    FILE *Ptr = fopen("ArqP.dat", "rb");
    TpPizzas pizza, menosPedida;

    if (Ptr == NULL) {
    	gotoxy(45,6);
        printf("ERRO\n");
        getch();
    }

    fseek(Ptr, 0,0);
	fread(&pizza, sizeof(TpPizzas), 1, Ptr);
    if (pizza.quant==0) 
	{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA
		gotoxy(45,6);
        printf("Nenhum pedido encontrado\n");
        fclose(Ptr);
        getch();
    } else {
        menosPedida = pizza;
    }

	fread(&pizza, sizeof(TpPizzas), 1, Ptr);
    while (!feof(Ptr)) 
	{
        if (pizza.quant < menosPedida.quant) {
            menosPedida = pizza;
        }
        fread(&pizza, sizeof(TpPizzas), 1, Ptr);
    }
	gotoxy(45,7);
    printf("A pizza menos pedida:\n");
    gotoxy(45,8);
    printf("Codigo: %d\n", menosPedida.Cod);
    gotoxy(45,9);
    printf("Sabor: %s\n", menosPedida.Desc);
    gotoxy(45,10);
    printf("Quantidade de vendas: %d\n", menosPedida.quant);
    gotoxy(45,11);
    printf("Valor: %.2f\n", menosPedida.Valor);


    fclose(Ptr);
    getch();
}

void Ranking(void)
{
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA
	FILE*Ptr=fopen("ArqP.dat","rb");
	TpPizzas pizza;
	int a=8, b=0;
	if(Ptr==NULL)
	{
		gotoxy(45,6);
		printf("ERRO\n");
		getch();
	}
	else
	{
		fseek(Ptr,0,0);
		fread(&pizza,sizeof(TpPizzas),1,Ptr);
		clrscr();
		Moldura(2,2,92,4,14,1); // MOLDURA AZUL
		Moldura(2,5,30,21,12,7); // MOLDURA BEJE
		Moldura(2,22,92,24,11,4);//MOLDURA VERMELHA
		Moldura(31,5,92,21,9,6);//AMARELA
		Moldura(1,1,93,25,10,5);//MOLDURA
		gotoxy(42,7);
		printf("---- Ranking ----");
		while(!feof(Ptr))
		{
			gotoxy(42,a);
			printf("%d lugar: cod %d, Desc %s, valor %.2f",b+1, pizza.Cod,pizza.Desc,pizza.Valor);
			a++;
			b++;
			fread(&pizza,sizeof(TpPizzas),1,Ptr);
		}
		fclose(Ptr);
		getch();
	}
}

void OrdenacaoInsercao(TpPizzas *pizzas, int n) //Inserçao direta
{
    for (int i = 1; i < n; i++) {
        TpPizzas chave = pizzas[i];
        int j = i - 1;
        while (j >= 0 && pizzas[j].quant > chave.quant) {
            pizzas[j + 1] = pizzas[j];
            j--;
        }
        pizzas[j + 1] = chave;
    }
}


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
	gotoxy(3,13);
	printf("[R] RELATORIOS");
	gotoxy(3,14);
	printf("[I] INSERIR DADOS");
	gotoxy(3,15);
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
								case 'F':RelatorioMoto();
							break;
							}		
							
					break;
					case 'P':  
							gotoxy(30, 2);
							printf("------P E D I D O S------");
							op=MenuPedido(); 
							switch (toupper(op))
							{
								clrscr();
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
								case 'C':Ranking();
									break;  
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
								case 'A':
									PizzaMaisPedida();
									break;
								case 'B':
									PizzaMenosPedida();
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

