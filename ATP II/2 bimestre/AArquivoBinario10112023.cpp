// Arquivos Binários

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>

struct TpFunc
{
	int Matricula;
	float Salario;
	char Nome[30];
};

int BuscaMat(FILE *Ptr,int Mat)//pos devolve em bytes
{
	TpFunc R;
	rewind(Ptr);
	fread(&R,sizeof(TpFunc),1,Ptr);
	while (!feof(Ptr) && Mat!=R.Matricula)
		fread(&R,sizeof(TpFunc),1,Ptr);
	
	if (!feof(Ptr))
		return ftell(Ptr)-sizeof(TpFunc);//quando da ofread ele vai pra frente
	else
		return -1;
}

void Cadastro(void)
{
	TpFunc R;
	int pos;
	
	FILE *PtrArq = fopen("func.dat","ab");
	printf("\n### Cadastro de Funcionarios ###\n");
	printf("Matricula: ");
	scanf("%d",&R.Matricula);
	while(R.Matricula>0)
	{
		pos = BuscaMat(PtrArq,R.Matricula);
		
		if(pos==-1)
		{
			printf("Nome: ");
			fflush(stdin);
			gets(R.Nome);
			printf("Salario R$: ");
			scanf("%f",&R.Salario);
			fwrite(&R,sizeof(TpFunc),1,PtrArq);	
		}
		else
		{
			printf("\nFuncionario ja cadastrado");
			fseek(PtrArq,pos,0);
			fread(&R,sizeof(TpFunc),1,PtrArq);
			printf("\n*** Detalhes do Registro ***\n");
			printf("Matricula: %d\n",R.Matricula);
			printf("Nome: %s\n",R.Nome);
			printf("Salario: R$ %.f\n",R.Salario);
		}
		
		printf("\n\nMatricula: ");
			scanf("%d",&R.Matricula);
	}
	fclose(PtrArq);
}

void Consultar(void)
{
	int pos;
	TpFunc Reg;
	FILE *PtrFunc = fopen("func.dat","rb");
	printf("\n### Consulta de Funcionarios ###\n");
	if (PtrFunc == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("\nMatricula a consultar: ");
			scanf("%d",&Reg.Matricula);
			while (Reg.Matricula>0)
			{
				pos = BuscaMat(PtrFunc,Reg.Matricula);
				
				if (pos==-1)
					printf("\nMatricula nao encontrada!\n");
				else
					{   
						fseek(PtrFunc,pos,0);
						fread(&Reg,sizeof(TpFunc),1,PtrFunc);
						printf("\n*** Detalhes do Registro ***\n");
						printf("Matricula: %d\n",Reg.Matricula);
						printf("Nome: %s\n",Reg.Nome);
						printf("Salario: R$ %.f\n",Reg.Salario);
					}
				getch();
				
				printf("\nMatricula a consultar: ");
				scanf("%d",&Reg.Matricula);
			}	
			fclose(PtrFunc);
		}
}

void Alterar(void)
{
	int pos;
	TpFunc Reg;
	FILE *PtrFunc = fopen("func.dat","rb+");
	printf("\n### Alteracao de Funcionarios ###\n");
	if (PtrFunc == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("\nMatricula do Funcionario a alterar: ");
			scanf("%d",&Reg.Matricula);
			while (Reg.Matricula>0)
			{
				pos = BuscaMat(PtrFunc,Reg.Matricula);
				
				if (pos==-1)
					printf("\nMatricula nao encontrada!\n");
				else
					{   
						fseek(PtrFunc,pos,0);
						fread(&Reg,sizeof(TpFunc),1,PtrFunc);
						printf("\n*** Detalhes do Registro ***\n");
						printf("Matricula: %d\n",Reg.Matricula);
						printf("Nome: %s\n",Reg.Nome);
						printf("Salario: R$ %.f\n",Reg.Salario);
						
						printf("\nDeseja Alterar (S/N)? ");
						if (toupper(getche())=='S')
						{
							printf("\nNova Matricula: "); fflush(stdin);
							scanf("%d",&Reg.Matricula);
							printf("\nNovo Nome: "); fflush(stdin);
							gets(Reg.Nome);
							printf("\nSalario: R$ ");
							scanf("%f",&Reg.Salario);
							fseek(PtrFunc,pos,0);
							fwrite(&Reg,sizeof(TpFunc),1,PtrFunc);
							printf("\nRegistro atualizado!!\n");
						}
						
						fclose(PtrFunc);
					}
				getch();
				
				printf("\nMatricula do Funcionario a alterar: ");
				scanf("%d",&Reg.Matricula);
			}	
			fclose(PtrFunc);
		}
}

char Menu(void)
{
	clrscr();
	printf("\n# # # #   M E N U   # # # #\n");
	printf("[A] - Cadastrar Funcionarios");
	printf("\n[B] - Exibir Funcionarios");
	printf("\n[C] - Consultar Funcionarios");
	printf("\n[D] - Alterar Funcionarios");
	printf("\n[E] - Ordenar Funcionarios");
	printf("\n[ESC] - Finalizar");
	printf("\nOpcao desejada: \n");
	return toupper(getche());
}

void Exibir(void)
{
	TpFunc Reg;
	FILE *PtrFunc = fopen("func.dat","rb");
	if (PtrFunc == NULL)
		printf("\nErro abertura!\n");
	else
		{
			fread(&Reg,sizeof(TpFunc),1,PtrFunc);
			while (!feof(PtrFunc))
			{
				printf("\nMatricula: %d",Reg.Matricula);
				printf("\nNome: %s",Reg.Nome);
				printf("\nSalario: R$ %.2f\n",Reg.Salario);
				fread(&Reg,sizeof(TpFunc),1,PtrFunc);
			}
			
			fclose(PtrFunc);
		}
	getch();
}

 void Ordenar(void)
{
	int a,b,QtdeReg;
	TpFunc RA, RB;
	FILE *Ptr=fopen("func.dat","rb+");
	if (Ptr==NULL)
		printf("\nErro de Abertura!\n");
	else
		{	
			fseek(Ptr,0,2); //Deslocar o Ponteiro para o final do Arquivo
			QtdeReg = ftell(Ptr)/sizeof(TpFunc);
			for(a=0; a<QtdeReg-1; a++)
				for(b=a+1; b<QtdeReg; b++)
				{
					fseek(Ptr,a*sizeof(TpFunc),0);//jogo o ponteiro para a posiçao 38(tamanho do arquivo) * a, para o começo (0) 
					fread(&RA,sizeof(TpFunc),1,Ptr);
					
					fseek(Ptr,b*sizeof(TpFunc),0);
					fread(&RB,sizeof(TpFunc),1,Ptr);
					
					if(RA.Matricula > RB.Matricula)
					{
						fseek(Ptr,a*sizeof(TpFunc),0);//joga pra posicao a
						fwrite(&RB,sizeof(TpFunc),1,Ptr);//escreve na b
						
						fseek(Ptr,b*sizeof(TpFunc),0);
						fwrite(&RA,sizeof(TpFunc),1,Ptr);
					}
				}
			printf("\nArquivo Ordenado pela Matricula!\n");
			fclose(Ptr);
		}
	getch();
}

int main(void)
{
	char op;
	//printf("\nint %d - char %d - float %d",sizeof(int),sizeof(op),sizeof(float));
	//getch();
	do
	{
		op = Menu();
		switch(op)
		{
			case 'A': Cadastro();
					  break;
					  
			case 'B': Exibir();
					  break;
					  
			case 'C': Consultar();
					  break;
					  
			case 'D': Alterar();
					  break;
					  
			case 'E': Ordenar();
					  break;
		}
	}while (op!=27);
	return 0;
}
