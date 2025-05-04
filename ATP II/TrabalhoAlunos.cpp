#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>
#include <windows.h>
#define TF 50

struct TpAluno
{
	char nome[40], RA[13];

};

struct TpDisc
{
	char nomeD[40];
	int codD;
	float media;
};

struct TabAlunosDisc
{
	float nota;
	TpAluno aluno;
	TpDisc codigo;
};

void Moldura (int CI, int LI, int CF, int LF, int Frente, int Fundo) 
{
	int a;
	textcolor(Frente);
	textbackground(Fundo);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LF);
	printf("%c",188);
	for(a=CI+1; a<CF; a++)
	{
		gotoxy(a,LI);
		printf("%c",205);
		gotoxy(a,LF);
		printf("%c",205);
	}
	for(a=LI+1; a<LF; a++)
	{
		gotoxy(CI,a);
		printf("%c",186);
		gotoxy(CF,a);
		printf("%c",186);
	}
	textcolor(7);
	textbackground(0);
}

void LimpaTela(void)
{
    int x, y;
    for(x = 32; x <= 87; x++)
    {
        for(y = 12; y <= 22; y++)
        {
            gotoxy(x, y);
            printf(" ");
        }
    }

}

void LimpaTelaM(void)
{
	int x, y;
	for(x = 12; x <= 29; x++)
    {
        for(y = 10; y <= 22; y++)
        {
            gotoxy(x, y);
            printf(" ");
        }
    }
}


void FormPrincipal(void)
{
	clrscr();
	Moldura(10,5,89,25,15,1);
	Moldura(11,6,88,8,15,8);  
	gotoxy(32,7);
	textcolor(11);
	printf("------------TRABALHO ATP II------------\n");
	Moldura(11,9,30,24,15,3); 
	Moldura(31,9,88,24,15,9); 
	  
	Moldura(10,26,89,28,15,9); 	
	gotoxy(28,27);
	textcolor(5); 
	printf("Engenheiros da programacao Andrey, Luigi e Matheus");
	textcolor(15); 
}


int buscaRA (TpAluno TabA[TF], int TL, char aux[13])
{
	int i=0;
	while(i<TL&&stricmp(aux,TabA[i].RA)!=0)
		i++;
	if (i<TL)
		return i;
	else
		return -1;
}

int buscaRADisc (TabAlunosDisc TabAD[TF], int TL, char aux[13], int auxD)
{
	int i=0,j=0;
	while(i<TL&&stricmp(aux,TabAD[i].aluno.RA)!=0)
		i++;
	while(j<TL&&auxD!=TabAD[j].codigo.codD)
		j++;
	if (i<TL&&j<TL)
		return i;
	else
		return -1;
}

int buscaRANotas (TabAlunosDisc TabAD[TF], int TL, char aux[13]){
	int i=0;
	while(i<TL&&stricmp(aux,TabAD[i].aluno.RA)!=0)
		i++;
	if (i<TL)
		return i;
	else
		return -1;
}

int buscaAluno (TpAluno TabA[TF], int TL, char aux[40])
{
	int i=0;
	while(i<TL && stricmp(aux,TabA[i].nome)!=0)
		i++;
	if(i<TL)
		return i;
	else
		return -1;
}


int buscaDisc (TpDisc TabD[TF], int TLD, int aux)
{
    int i = 0;
    while (i < TLD && aux != TabD[i].codD)
        i++;
    if(i < TLD)
        return i;
    else
        return -1;
}


int buscaDiscNotas (TabAlunosDisc TabAD[TF], int TLAD, int aux)
{
    int i = 0;
    while (i < TLAD && aux != TabAD[i].codigo.codD)
        i++;
    if(i < TLAD)
        return i;
    else
        return -1;
}

 int buscaMat (TpDisc TabD[TF], int TL, char aux[40])
{
	int i=0;
	while(i<TL&&stricmp(aux,TabD[i].nomeD)!=0)
		i++;
	if(i<TL)
		return i;
	else
		return -1;
}

void CadastroDisc (TpDisc TabD[TF], int &TLD)
{
    char auxM[40];
    int aux, pos, i;
    clrscr();
    FormPrincipal();
    gotoxy(36,10);
    printf("-------CADASTRO DISC.-------\n");
    if(TLD >= TF)
    {
        textcolor(9);
		gotoxy(36,11);
		printf("Cadastro cheio!");
		textcolor(15);
		getch();
		LimpaTela();
    }
    else
    {
    	gotoxy(33,11);
        printf("'0' para finalizar\n");
        gotoxy(33,12);
        printf("Codigo da disciplina [xxx]: ");      
        scanf("%d", &aux);

        while(TLD < TF && aux > 0)
        {
            pos = buscaDisc(TabD, TLD, aux);
            if(pos != -1)
            {
                gotoxy(33,13);
                textcolor(4);
                printf("Codigo ja cadastrado!\n");
                textcolor(15);
                getch();
                LimpaTela();
            }
            else
            {
                if(aux > 999)
                {
                    gotoxy(33,13);
                    textcolor(4);
                    printf("Codigo invalido!\n");
                    getch();
                    textcolor(15);
                    LimpaTela();
                }
                else
                {
                    TabD[TLD].codD = aux;
                    gotoxy(33,13);
                    printf("Nome da materia: ");
                    fflush(stdin);
                    gets(auxM);

                    i = buscaMat(TabD, TLD, auxM);
                    if(i != -1)
                    {
                        gotoxy(36,14);
                        textcolor(4);
                        printf("-> Materia ja cadastrada!\n");
                        getch();
                        textcolor(15);
                        LimpaTela();
                    }
                    else
                    {
                        strcpy(TabD[TLD].nomeD, auxM);
                        gotoxy(33,14);
                        textcolor(9);
                        printf("-> Materia cadastrada!\n");
                        textcolor(15);
                        TLD++;
                        getch();
                    }
                }
            }
            LimpaTela();
            gotoxy(33,11);
	        printf("'0' para finalizar\n");
	        gotoxy(33,12);
	        printf("Codigo da disciplina [xxx]: ");      
	        scanf("%d", &aux);
        }
    }
    textcolor(9);
    gotoxy(40,18);
    printf("Cadastro finalizado!\n");
    textcolor(15);
    getch();
    LimpaTela();
}

void CadastroAluno (TpAluno TabA[TF],int &TL)
{
	int pos=0;
	char aux[13],auxN[40];
	clrscr();
	FormPrincipal();
	gotoxy(36,10);
	printf("-------CADASTRO DE ALUNOS-------\n");
	if(TL>=TF)
	{
		textcolor(9);
		gotoxy(36,11);
		printf("Cadastro cheio!");
		textcolor(15);
		getch();
		LimpaTela();
	}
	else
	{
		gotoxy(33,11);
		printf("'0' para finalizar\n");
		gotoxy(33,12);
		printf("RA [xx.xx.xxxx-x]: ");
		fflush(stdin);
		gets(aux);
		
		while (TL<TF && strcasecmp(aux,"0")!=0)
		{
			if (strlen(aux)>12 || strlen(aux)<12)
			{
				gotoxy(33,13);
				textcolor(4);
				printf("RA invalido!\n");
				textcolor(15);
				getch();
				LimpaTela();
			}
			else
			{
				pos=buscaRA(TabA, TL, aux);
				if(pos!=-1)
				{
					gotoxy(33,13);
					textcolor(4);
					printf("RA ja cadastrado!");
					getch();
					textcolor(15);
					LimpaTela();
				}
				else
				{
					strcpy(TabA[TL].RA,aux);
					gotoxy(33,13);
					printf("Nome: ");
					fflush(stdin);
					gets(auxN);
					pos=buscaAluno(TabA, TL, auxN);
					if(pos!=-1)
					{
						gotoxy(33,14);
						textcolor(4);
						printf("Nome ja cadastrado!\n");
						getch();
						textcolor(15);
						LimpaTela();
					}
					else
					{
						strcpy(TabA[TL].nome,auxN);
						gotoxy(33,15);
						textcolor(9);
						printf("Cadastro feito!\n");
						textcolor(15);						
						TL++;
						getch();
						LimpaTela();
					}		
					
				}
			}	
			gotoxy(33,11);
			printf("'0' para finalizar\n");
			gotoxy(33,12);
			printf("RA [xx.xx.xxxx-x]: ");
			fflush(stdin);
			gets(aux);			
		}
	}
	LimpaTela();
	gotoxy(40,17);
	textcolor(9);
	printf("Cadastro finalizado!\n");
	getch();
	LimpaTela();
}

int buscaAD(TabAlunosDisc TabAD[TF],int TL,char aux[13],int auxD)
{
	int pos;
	
	pos=0;
	while(pos<TL && stricmp(aux,TabAD[pos].aluno.RA)!=0 && auxD != TabAD[pos].codigo.codD)
	pos++;
	if(pos<TL)
		return 0;
	else
		return 1;
	
}
void CadastroAlunoDisc (TabAlunosDisc TabAD[TF], TpDisc TabD[TF], TpAluno TabA[TF], int &TL, int TLA, int TLD)
{
    int pos, auxD,a,b;
    char aux[13];
    clrscr();
    FormPrincipal();
    gotoxy(32,10);
    printf("-------CADASTRO DE NOTAS-------\n");
    if(TL >= TF)
    {
        textcolor(9);
		gotoxy(36,11);
		printf("Cadastro cheio!");
		textcolor(15);
		getch();
		LimpaTela();
    }
    else
    {
        gotoxy(33,11);
        printf("'0' para finalizar\n");
        gotoxy(33,12);
        printf("RA [xx.xx.xxxx-x]: ");
        fflush(stdin);
        gets(aux);
    }

    while(TL < TF && strcasecmp(aux, "0") != 0)
    {
        pos = buscaRA(TabA, TLA, aux);
        if(pos == -1)
        {
        	textcolor(4);
            gotoxy(33,14);
            printf("->Aluno nao cadastrado!\n");
            textcolor(15);
            getch();
            LimpaTela();
            
        }
        else
        {           
            gotoxy(33,14);
            printf("Digite o cod. da materia(xxx): ");
            scanf("%d", &auxD);
            pos = buscaDisc(TabD, TLD, auxD);
            if(pos == -1)
            {
                gotoxy(33,15);
                textcolor(4);
                printf("-> Materia nao cadastrada!\n");
                textcolor(15);
                getch();
                LimpaTela();
            }
            else
            {
				pos=buscaRADisc(TabAD,TL,aux,auxD);
            	if( pos == -1)
            	{
            		gotoxy(33,16);
		            textcolor(4);
		            printf("-> Aluno e materia ja cadastrada!");
		            textcolor(15);
		            getch();
		            LimpaTela();
            	}
            	else
            	{
            		strcpy(TabAD[TL].aluno.RA, aux);
           			TabAD[TL].codigo.codD = auxD;
	                gotoxy(33,15);
	                printf("Digite a nota: ");
	                scanf("%f", &TabAD[TL].nota);
	                gotoxy(33,16);
	                textcolor(9);
	                printf("Cadastro concluido!\n");
	                textcolor(15);
	                TL++;
	                getch();
	                LimpaTela();
            	}
            }                    
        }
        LimpaTela();
        gotoxy(33,11);
        printf("'0' para finalizar\n");
        gotoxy(33,12);
        printf("RA [xx.xx.xxxx-x]: ");
        fflush(stdin);
        gets(aux);
    }
    LimpaTela();
	textcolor(9);
	gotoxy(40,18);
    printf("Cadastro finalizado!\n");
    getch();
    LimpaTela();
}

void FuancMedia(TabAlunosDisc TabAD[TF],TpDisc TabD[TF], int TL, int TLD)
{
	int i=0, j, pos, contM, auxD;
	float soma;
	
	
	while(i<TL){
		auxD=TabAD[i].codigo.codD;
		pos=buscaDisc(TabD,TLD,auxD);
		contM=0;
		j=0;
		while(j<TL && TabD[pos].media==0)
		{
			if(TabAD[j].codigo.codD==TabD[pos].codD){
				soma+= TabAD[j].nota;
				contM++;
			}
			j++;
		}
		if(TabD[pos].media==0)
			TabD[pos].media=soma/contM;
		i++;
	}
}

void mediaRep(TabAlunosDisc TabAD[TF],TpDisc TabD[TF], int TL, int TLD)
{
	int i=0;
	
	FuncMedia(TabAD, TabD, TL, TLD);
	
	printf("Disicplinas com médias abaixo de 6!!\n");
	
	while(i<TLD){
		if(TabD[i].media<6.0 && TabD[i].media!=0)
			printf("Disciplina: %s", TabD[i].nomeD);
		i++;
	}
	getch();
}

void ExcluirAluno(TpAluno TabA[TF], TabAlunosDisc TabAD[TF], int &TL, int TLN)
{
    int pos,i;
    char aux[13], auxN[13];
    clrscr();
    FormPrincipal();
    gotoxy(36,10);
    printf("-------EXCLUIR ALUNO-------\n");
    if(TL==0)
    {
        textcolor(9);
		gotoxy(33,14);
		printf("-> Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
    }
    else
    {
        gotoxy(33,12);
    	printf("'0' para finalizar:\n");
    	gotoxy(33,13);
        printf("Digite o RA que deseja excluir:");
		gotoxy(33,14);
        printf("RA [xx.xx.xxxx-x]: ");
        scanf("%s", aux);
        while(strcasecmp(aux,"0")!=0)
        {
            pos=buscaRA(TabA,TL,aux);
            if(pos==-1)
            {
            	gotoxy(33,15);
            	textcolor(4);
                printf("RA nao encontrado!\n");
                getch();
                textcolor(15);
                LimpaTela();
            }            
            else
            {
				i=pos;
                pos=buscaRANotas(TabAD,TLN,aux);
                if(pos!=-1)
                {
                	gotoxy(33,16);
            		textcolor(4);
                    printf("Nao e possivel excluir\n");
                    getch();
                    textcolor(15);
                	LimpaTela();
                }
                else
                {
                	gotoxy(33,16);
                    printf("Deseja excluir o aluno %s <S|N>: ", TabA[i].nome);
                    if(toupper(getche())=='S')
                    {
                        for(;i<TL-1;i++)
                        {
                            strcpy(TabA[i].nome,TabA[i+1].nome);
                            strcpy(TabA[i].RA, TabA[i+1].RA);
                        }
                        TL--;
                        textcolor(9);
                        gotoxy(33,17);
                        printf("-> Exclusao feita!\n");
                        textcolor(15);
                        getch();
                    }
                }
            }
            LimpaTela();
            gotoxy(33,12);
	    	printf("'0' para finalizar:\n");
	    	gotoxy(33,13);
	        printf("Digite o RA que deseja excluir:");
			gotoxy(33,14);
	        printf("RA [xx.xx.xxxx-x]: ");
	        scanf("%s", aux);
    	}
	}
	LimpaTela();
	textcolor(9);
	gotoxy(40,18);
    printf("Exclusao finalizada!\n");
    getch();
    LimpaTela();
}

void consultaAlunos (TpAluno TabA[TF], int TL)
{
	int pos;
	char aux[13];
	clrscr();
	FormPrincipal();
	gotoxy(36,10);
	printf("-------COSULTA ALUNOS-------\n");
	if(TL==0)
	{
		textcolor(9);
		gotoxy(33,14);
		printf("-> Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
	}
	else
	{
		gotoxy(33,12);
    	printf("'0' para finalizar:\n");
    	gotoxy(33,13);
        printf("Digite o RA que deseja consultar:");
		gotoxy(33,14);
        printf("RA [xx.xx.xxxx-x]: ");
        scanf("%s", aux);
		
		while(strcasecmp(aux,"0")!=0)
		{
			pos=buscaRA(TabA,TL,aux);
			if (pos==-1)
			{
				gotoxy(33,15);
            	textcolor(4);
                printf("RA nao encontrado!\n");
                getch();
                textcolor(15);
                LimpaTela(); 
			}				
			else
			{
				gotoxy(33,15);
				printf("RA:");
				textcolor(2);
				printf("%s",TabA[pos].RA);
				textcolor(15);  
				printf(" Aluno:");
				textcolor(2);
				printf("%s\n",TabA[pos].nome);
				textcolor(15);
				getch();
			}
			LimpaTela(); 
			gotoxy(33,12);
	    	printf("'0' para finalizar:\n");
	    	gotoxy(33,13);
	        printf("Digite o RA que deseja consultar:");
			gotoxy(33,14);
	        printf("RA [xx.xx.xxxx-x]: ");
	        scanf("%s", aux);
		}
		
	}
	LimpaTela(); 
	gotoxy(40,18);
	textcolor(9);
	printf("Consulta finalizada!\n");
	textcolor(15);
	getch();
	LimpaTela();
}

void consultaDisc(TpDisc TabD[TF], int TL)
{
    int pos, aux;
    clrscr();
    FormPrincipal();
    gotoxy(36,10);
    printf("-------CONSULTA DISC.-------\n");
    if(TL == 0)
    {
        textcolor(9);
		gotoxy(33,14);
		printf("-> Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
    }
    else
    {
        gotoxy(33,12);
        printf("'0' para finalizar\n");
        gotoxy(33,13);
        printf("Codigo da disciplina [xxx]: ");      
        scanf("%d", &aux);
        
        while(aux != 0)
        {
            pos = buscaDisc(TabD, TL, aux);
            if(pos == -1)
            {
            	gotoxy(33,14);
                textcolor(4);
                printf("Codigo nao encontrado!\n");
                textcolor(15);
                getch();
                LimpaTela();
            }
            else
            {
            	gotoxy(33,14);
				printf("Cod.:");
				textcolor(2);
				printf("[%d]",TabD[pos].codD);
				textcolor(15);  
				printf(" Disc.:");
				textcolor(2);
				printf("%s\n",TabD[pos].nomeD);
				textcolor(15);
				getch();
            }
            LimpaTela();
            gotoxy(33,12);
	        printf("'0' para finalizar");
	        gotoxy(33,13);
	        printf("Codigo da disciplina [xxx]: ");      
	        scanf("%d", &aux);
        }
    }
    LimpaTela(); 
	gotoxy(40,18);
	textcolor(9);
	printf("Consulta finalizada!\n");
	textcolor(15);
	getch();
	LimpaTela();
}

void consultaAlunoDisc (TabAlunosDisc TabAD[TF], TpAluno TabA [TF], int TL, int TLN)
{
    int pos, i,x;
    char aux[13];
    clrscr();
    FormPrincipal();
    gotoxy(36,10);
    printf("-------CONSULTA ALUNO DISC.-------\n");

    if (TL == 0)
    {
        textcolor(9);
		gotoxy(33,14);
		printf("-> Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
    }
    else
    {
    	gotoxy(33,12);
    	printf("'0' para finalizar:\n");
    	gotoxy(33,13);
        printf("Digite o RA que deseja consultar:");
		gotoxy(33,14);
        printf("RA [xx.xx.xxxx-x]: ");
        scanf("%s", aux);
        while (strcasecmp(aux, "0") != 0)
        {
            pos = buscaRA(TabA, TL, aux);

            if (pos == -1)
            {
            	gotoxy(33,15);
            	textcolor(4);
                printf("RA nao encontrado!\n");
                getch();
                textcolor(15);
                LimpaTela();              
            }
            else
            {
            	LimpaTela(); 
            	gotoxy(33,11);
                printf("Disc e notas do RA [%s]: ", aux);

                for (i = 0,x=12; i < TLN; i++,x++)
                {
                    if (strcmp(TabAD[i].aluno.RA, aux) == 0) 
                    {
						gotoxy(33,x);                  	
                        printf("-> Disciplina: %d | Nota: %.2f", TabAD[i].codigo.codD, TabAD[i].nota);
                    }
                }
                getch();
            }
			LimpaTela(); 
            gotoxy(33,12);
	    	printf("'0' para finalizar:\n");
	    	gotoxy(33,13);
	        printf("Digite o RA que deseja consultar:");
			gotoxy(33,14);
	        printf("RA [xx.xx.xxxx-x]: ");
	        scanf("%s", aux);
        }
    }
	LimpaTela();
	gotoxy(40,18);
	textcolor(9);
    printf("Consulta finalizada!\n");
    textcolor(15);
    getch();
    clrscr();
}

void AlunosPorLetra (TpAluno TabA[TF], int TL)
{
    int i,x, achou=0;
    char aux;
    clrscr();
    FormPrincipal();
	gotoxy(36,10);
    printf("----CONSULTA ALUNOS POR LETRA----\n");
    if(TL==0)
    {
        textcolor(9);
		gotoxy(33,14);
		printf("-> Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
    }
    else
    {  	
        gotoxy(33,11);
        printf("'0' para sair");
        gotoxy(33,12);
        printf("Digite a letra inicial do aluno: ");
        scanf(" %c", &aux);
        while(aux!='0')
        {
            for(i=0,x=12;i<TL;i++,x++)
            {
                if(aux==TabA[i].nome[0])
				{
					gotoxy(33,x);
					textcolor(15);
					printf("->");
					textcolor(9);
                    printf("%s\n", TabA[i].nome);
                     getch();
                    achou=1;
                }
            }
            textcolor(15);
            if(achou==0)
            {
            	gotoxy(33,13);
            	printf("Nenhum aluno com: '%c' na inicial!");
            	getch();
            } 
			LimpaTela(); 	
            gotoxy(33,11);
	        printf("'0' para sair");
	        gotoxy(33,12);
	        printf("Digite a letra inicial do aluno: ");
	        scanf(" %c", &aux);
        }

    }
    getch();
    LimpaTela();
}

void AlterarDisc (TpDisc TabD[TF], int TLD)
{
	int pos,i,dis,aux;
	char auxM[40];
	clrscr();
	FormPrincipal();
	gotoxy(36,10);
	printf("-------ALTERAR DISC.-------\n");
	if(TLD==0)
	{
		textcolor(4);
		gotoxy(33,14);
		printf("-> Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
	}
	else
	{
		gotoxy(33,11);
		printf("'0' para finalizar.\n");
		gotoxy(33,12);
		printf("Cod. disc. para alterar[xxx]: ");	
		scanf("%d", &aux);
		while( TLD <TF && aux>0)
		{
			pos=buscaDisc(TabD, TLD, aux);			
			if(pos==-1)
			{
				gotoxy(33,13);
				textcolor(4);
				printf("Cod. nao encontrado\n");
				textcolor(15);
				getch();
				LimpaTela();	
			}
			else
			{
				gotoxy(33,13);
				printf("Cod.:[%d] Disc.:%s\n",TabD[pos].codD, TabD[pos].nomeD);
				gotoxy(33,14);
				printf("Deseja alterar o nome <S|N>: ");
				if(toupper(getche())=='S')
				{
					gotoxy(33,15);
					printf("Novo nome para disc: ");
					fflush(stdin);
					gets(auxM);
					i=pos;
					pos=buscaMat(TabD,TLD,auxM);
					if(pos!=-1)
					{
						gotoxy(33,16);
						textcolor(4);
						printf("Nome ja cadastrado!\n");
						textcolor(15);
						getch();
						LimpaTela();	
						
					}
					else
					{
						strcpy(TabD[i].nomeD,auxM);
						gotoxy(33,16);
						textcolor(9);
						printf("Alteracao concluida!\n");
						textcolor(15);
						getch();
					}
				}
	
			}
			LimpaTela();
			gotoxy(33,11);
			printf("'0' para finalizar.\n");
			gotoxy(33,12);
			printf("Cod. disc. para alterar[xxx]: ");	
			scanf("%d", &aux);
		}
	
	}
	LimpaTela();
	gotoxy(40,18);
	textcolor(9);
	printf("Alteracao finalizada!\n");
	textcolor(15);
	getch();
	LimpaTela();
}

void alterarAlunos (TpAluno TabA[TF], int TL)
{
	int	pos,i;
	char aux[13],auxN[40];
	clrscr();
	FormPrincipal();
	gotoxy(36,10);
	printf("-------ALTERAR ALUNOS-------\n");
	if(TL==0)
	{
		textcolor(4);
		gotoxy(33,14);
		printf("-> Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
	}
	else
	{
		gotoxy(33,12);
		printf("RA do aluno que deseja alterar:");
		gotoxy(33,11);
		printf("'0' para finalizar;");
		gotoxy(33,13);
		printf("RA [xx.xx.xxxx-x]: ");
		fflush(stdin);
		gets(aux);
		while(strcasecmp(aux,"0")!=0)
		{
			pos=0;
			pos=buscaRA(TabA,TL,aux);
			
			if (pos==-1)
			{
				textcolor(4);
				gotoxy(33,14);
				printf("->RA nao encontrado!\n");
				textcolor(15);
				getch();
				LimpaTela();
			}				
			else
			{
				gotoxy(33,15);
				printf("RA:");
				textcolor(2);
				printf("%s",TabA[pos].RA);
				textcolor(15);  
				printf(" Aluno:");
				textcolor(2);
				printf("%s\n",TabA[pos].nome);
				textcolor(15);
				gotoxy(33,16);
				printf("Deseja alterar o nome do aluno <S|N>:");
				if (toupper(getche())=='S')
				{
					gotoxy(33,17);
					printf("-> Digite o novo nome: ");					
					fflush(stdin);
					textcolor(2);
					gets(auxN);
					textcolor(15);
					i=pos;
					pos=buscaAluno(TabA,TL,auxN);
					if(pos!=-1)
					{
						textcolor(4);
						gotoxy(33,18);
						printf("-> Nome ja cadastrado!\n");
						getch();
						textcolor(15);
					}
					else
					{
						strcpy(TabA[i].nome,auxN);
						textcolor(9);
						gotoxy(33,18);
						printf("-> Alteracao concluida!\n");
						getch();
						textcolor(15);
					}
				}
			}
			LimpaTela();
			gotoxy(33,12);
			printf("RA do aluno que deseja alterar:");
			gotoxy(33,11);
			printf("'0' para finalizar;");
			gotoxy(33,13);
			printf("RA [xx.xx.xxxx-x]: ");
			fflush(stdin);
			gets(aux);
		}
	}	
	gotoxy(40,18);
	textcolor(9);
	printf("Alteracao finalizada!\n");
	textcolor(15);
	getch();
	LimpaTela();
}

void AlterarNotas(TabAlunosDisc TabAD[TF], int TL)
{
	int pos,i,auxD;
	char aux[13];
	clrscr();
	FormPrincipal();
	gotoxy(36,10);
	printf("-------ALTERAR DISC.-------\n");
	if(TL==0)
	{
		textcolor(4);
		gotoxy(33,14);
		printf("-> Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
	}
	else
	{
        gotoxy(33,12);
        printf("Digite o RA: ");
        gotoxy(33,11);
        printf("'0' para finalizar.");
        gotoxy(33,13);
        printf("RA [xx.xx.xxxx-x]: ");
        scanf("%s",&aux);
        while(TL < TF && strcasecmp(aux, "0") != 0)
        {
        	pos=buscaRANotas(TabAD,TL,aux);
        	if(pos==-1)
        	{
        		gotoxy(33,14);
        		textcolor(4);
        		printf("Aluno sem notas!\n");
        		textcolor(15);
        		getch();
        	}
        	else
        	{
        		LimpaTela();
        		gotoxy(33,12);
        		printf("Disc. que deseja alterar nota[xxx)]: ");
        		scanf("%d",&auxD);
        		i=pos;
        		pos=buscaDiscNotas(TabAD,TL,auxD);
        		if(pos==-1)
        		{
        			textcolor(4);
        			gotoxy(33,16);
        			printf("-> Disc. nao cadastrada!\n");
        			textcolor(15);
        			getch();
        			LimpaTela();
        		}
        		else
        		{
        			gotoxy(33,14);
        			printf("Disc: %d | Nota: %.2f\n",TabAD[i].codigo.codD,TabAD[i].nota);
        			gotoxy(33,15);
        			printf("Deseja alterar a nota <S|N>: ");
        			if(toupper(getche())=='S')
        			{
        				gotoxy(33,16);
        				printf("Digite a nova nota: ");
        				scanf("%f",&TabAD[i].nota);
        				textcolor(9);
        				gotoxy(33,17);
        				printf("Alteracao concluida!");
        				textcolor(15);
        				LimpaTela();
        			}
        		}	
        	}
        	LimpaTela();
        	FormPrincipal();
			gotoxy(36,10);
			printf("-------ALTERAR DISC.-------\n");
	       	gotoxy(33,12);
	        printf("Digite o RA: ");
	        gotoxy(33,11);
	        printf("'0' para finalizar.");
	        gotoxy(33,13);
	        printf("RA [xx.xx.xxxx-x]: ");
	        scanf("%s",&aux);
        }       
	}
	textcolor(9);
	gotoxy(40,18);
	printf("Alteracao finalizada!");
	textcolor(15);
	getch();
	LimpaTela();
}

void Reprovados (TabAlunosDisc TabAD[TF], TpAluno TabA[TF], int TLN, int TLA)
{
    int i, j, cont,pos;
    clrscr();
    LimpaTelaM();
    FormPrincipal();
    gotoxy(36,10);
    printf("----- REPROVADO EM 2 OU + ----\n");
    if(TLN==0)
    {
        textcolor(15);
	 	gotoxy(33,14);
		printf("-> ");
        textcolor(4);
		gotoxy(33,14);
		printf("SEM RELATORIOS!");
		textcolor(15);
		getch();
		LimpaTela();
		LimpaTelaM();
    }
    else
    {
	    for(i=0;i<TLN;i+=j)
        {
            j=0;
            cont=0;
            while(stricmp(TabAD[i].aluno.RA, TabAD[i+j].aluno.RA)==0)
            {
                if(TabAD[j].nota < 6)
                    cont++;
                j++;
            }
            if(cont>=2)
            {
                pos=buscaRA(TabA,TLA,TabAD[i].aluno.RA);
                printf("RA: %s | NOME: %s ", TabAD[i].aluno.RA, TabA[pos].nome);
            }
        }
    }
    getch();
}

void PesquisaPorPalavra(TabAlunosDisc TabAD[TF], TpDisc Disc[TF], int TL, int TLD) 
{
    char aux[40]; 
    int i,x;
    clrscr();
    FormPrincipal();
    gotoxy(36,10);
    printf("-----PESQUISA POR PALAVRA-----\n");
    if (TLD == 0)
	 {
	 	textcolor(15);
	 	gotoxy(33,14);
		printf("-> ");
        textcolor(4);
		gotoxy(33,14);
		printf("Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
     } 
	else
	{
		gotoxy(33,14);
        printf("Digite um pedaco da palavra: ");
        fflush(stdin);
        gets(aux);
        if (strlen(aux) == 0)
		 {
		 	textcolor(9);
			gotoxy(33,16);
			printf("-> Nao ha cadastros\n");
			textcolor(15);
			getch();
			LimpaTela();
         }
         else
         {
         	for (i = 0,x=15; i < TLD; i++,x++)
			 {
	            if (strstr(Disc[i].nomeD, aux) != 0)
				{ 
					gotoxy(33,x);
					textcolor(15);
					printf("-> "); 
					textcolor(9);
	                printf("%s\n", Disc[i].nomeD); 
	            }
	         }	
         }
    }
    getch(); 
    LimpaTela();
}

void RelatorioGeral (TabAlunosDisc TabAD[TF], TpAluno TabA[TF], TpDisc TabD[TF], int TLN, int TLA, int TLD)
{
	int i, j,x,pos,cont;
	LimpaTela();
	LimpaTelaM();
    FormPrincipal();
    gotoxy(36,10);
    printf("-----RELATORIO GERAL-----\n");
	if(TLN==0)
	{
		textcolor(15);
	 	gotoxy(33,14);
		printf("-> ");
        textcolor(4);
		gotoxy(33,14);
		printf("-> SEM RELATORIOS!");
		getch();
		textcolor(15);
		LimpaTela();
	}
	else
	{
		for(i=0,x=11; i<TLN ;i+=j,x+=cont)
		{
			j=0;
			cont=0;
			pos=buscaRA(TabA,TLA,TabAD[i].aluno.RA);
			gotoxy(33,x+1);   
			printf("RA: %s Nome: %s\n", TabAD[i].aluno.RA, TabA[pos].nome);	
			while(i+j<TLN && stricmp(TabAD[i].aluno.RA, TabAD[i+j].aluno.RA)==0)
			{
				gotoxy(33,x+2);
				pos=buscaDisc(TabD,TLD,TabAD[i+j].codigo.codD);
				printf("Disciplina: %d - %s ", TabAD[i+j].codigo.codD, TabD[pos].nomeD);
				if(TabAD[i+j].nota >= 6)
				{
					printf("Nota: %.2f Situacao: ", TabAD[i+j].nota);
					textcolor(2);
					printf("Aprovado");
					textcolor(15);
				}	
				else
				{
					printf("Nota: %.2f Situacao: ", TabAD[i+j].nota);
					textcolor(4);
					printf("Reprovado");
					textcolor(15);
				}	
				j++;
				if(x>=22)
				{
					gotoxy(33,x+1);
					printf("[ENTER],Limpeza de tela para continuar!");
					Moldura(31, 9, 88, 24, 15, 9); 
                    x = 11;
				}
				x++;
				cont++;
			}
			gotoxy(33,x+cont);
			printf("------------------------------------------------------");
		}
		getch();
	}

	LimpaTela();
}

void ExcluirDisc(TpDisc TabD[TF],TabAlunosDisc TabAD[TF], int &TLD, int TLN)
{
    int pos, i,aux;
    clrscr();
    FormPrincipal();
    gotoxy(36,10);
    printf("-------EXCLUIR DISC.-------\n");
    if(TLD == 0)
    {
        textcolor(9);
		gotoxy(33,14);
		printf("-> Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
    }
    else
    {
    	gotoxy(33,11);
        printf("'0' para sair.\n"); 
        gotoxy(32,12);
        printf("Digite o cod. da disciplina[xxx]: ");       
        scanf("%d", &aux);
        while(TLD<TF&&aux>0)
        {
	        pos = buscaDisc(TabD, TLD, aux);
	        gotoxy(32,12);
	        if(pos == -1)
	        {
	        	gotoxy(33,14);
	        	textcolor(4);
	        	printf("Cod. nao encontrado\n");
	        	textcolor(15);
	            getch();
	            LimpaTela();
	        }           
	        else
	        {
	           i=pos;
	           pos=buscaDiscNotas(TabAD,TLN,aux);   
			   if(pos!=-1)
	            {
	            	gotoxy(33,14);
	        		textcolor(4);
	            	printf("Nao e possivel excluir\n");
	            	textcolor(15);
		            getch();
		            LimpaTela();
	            }
	            else
	            {
	            	gotoxy(33,14);
	                printf("Deseja excluir a disc %s <S|N>: ", TabD[i].nomeD);
	                if(toupper(getche())=='S')
	                {
	                    for(;i<TLD-1;i++)
	                    {
	                        strcpy(TabD[i].nomeD,TabD[i+1].nomeD);
	                        TabD[i].codD=TabD[i+1].codD;
	                    }
	                    TLD--;
	                    gotoxy(33,16);
	                    textcolor(9);
	                    printf("Exclusao feita!\n");
	                    textcolor(15);
	                    getch();
	                }
	            }
        	}
        	LimpaTela();
	        gotoxy(33,11);
	        printf("'0' para sair.\n"); 
	        gotoxy(32,12);
	        printf("Digite o cod. da disciplina[xxx]: ");       
	        scanf("%d", &aux);
        }       
    }
    LimpaTela();
	textcolor(9);
	gotoxy(40,18);
    printf("Exclusao finalizada!\n");
    getch();
    LimpaTela();
}

void ordenarAluno(TpAluno TabA[TF], int TL)
{	
	int i=0, j=1; 
	char aux[13];
	clrscr();
    FormPrincipal();
    gotoxy(36,10);
    printf("-------ORDENAR ALUNOS-------\n");
	if(TL==0)
	{
		textcolor(4);
		gotoxy(33,14);
		printf("-> Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
	}
	else
	{
		for(i=0; i<TL; i++)
			for(j=i+1; j<TL; j++)
				if(TabA[i].RA > TabA[j].RA)
				{
					strcpy(aux, TabA[i].RA);
					strcpy(TabA[i].RA,TabA[j].RA);
					strcpy(TabA[j].RA, aux);
				}
		textcolor(9);
		gotoxy(33,14);
		printf("Tabela de alunos ordenada pelo RA!");
		textcolor(15);	
		getch();
		LimpaTela();
	}	
}

void ordenarDisc(TpDisc TabD[TF], int TL)
{	
	int i=0, j=1, aux; 
	clrscr();
    FormPrincipal();
    gotoxy(36,10);
    printf("-------ORDENAR DISC.-------\n");
	if(TL==0)
	{
		textcolor(4);
		gotoxy(33,14);
		printf("-> Nao ha disc. cadastrados!");
		textcolor(15);
		getch();
		LimpaTela();
	}	
	else
	{
		for(i=0; i<TL; i++)
			for(j=i+1; j<TL; j++)
				if(TabD[i].codD > TabD[j].codD)
				{
					aux = TabD[i].codD;
					TabD[i].codD = TabD[j].codD;
					TabD[j].codD = aux;
				}
		textcolor(9);
		gotoxy(33,14);
		printf("Tabela de disc. ordenada pelo cod.!");	
		textcolor(15);	
		getch();
		LimpaTela();
	}	
}

void ordenarAlunoDisc(TabAlunosDisc TabAD[TF], int TL)
{	
	int i=0, j=1; 
	char aux[13];
	clrscr();
    FormPrincipal();
    gotoxy(36,10);
    printf("-------ORDENAR TABELA RA-------\n");
	if(TL==0)
	{
		textcolor(4);
		gotoxy(33,14);
		printf("-> Nao ha cadastros!");
		textcolor(15);
		getch();
		LimpaTela();
	}
		
	else
	{
		for(i=0; i<TL; i++)
			for(j=i+1; j<TL; j++)
				if(TabAD[i].aluno.RA > TabAD[j].aluno.RA)
				{
					strcpy(aux, TabAD[i].aluno.RA);
					strcpy(TabAD[i].aluno.RA,TabAD[j].aluno.RA);
					strcpy(TabAD[j].aluno.RA, aux);
				}
		textcolor(9);
		gotoxy(33,14);
		printf("Tabela de alunos disc. ordenada pelo RA!");	
		textcolor(15);
		getch();
		LimpaTela();
	}	
}


void ExcluirAlunoDisc(TabAlunosDisc TabAD[TF], int &TLN)
{
	int auxD,pos,i;
	char aux[13];
	clrscr();
	FormPrincipal();
    gotoxy(36,10);
    printf("-------EXCLUIR NOTAS-------\n");
    if(TLN == 0)
    {    
        textcolor(9);
		gotoxy(33,14);
		printf("-> Cadastro vazio!\n");
		textcolor(15);
		getch();
		LimpaTela();
    }
    else
    {
    	gotoxy(33,12);
    	printf("'0' para finalizar:\n");
    	gotoxy(33,13);
        printf("Digite o RA que deseja excluir:");
		gotoxy(33,14);
        printf("RA [xx.xx.xxxx-x]: ");
        scanf("%s", aux);
		while(strcasecmp(aux,"0")!=0)
        {
            pos=buscaRANotas(TabAD,TLN,aux);
            if(pos==-1)
            {
            	gotoxy(33,15);
            	textcolor(4);
                printf("RA nao encontrado!\n");
                getch();
                textcolor(15);
                LimpaTela();
            }            
            else
            {
            	gotoxy(33,15);
            	printf("Digite o codigo da disc[xxx]: ");
            	scanf("%d",&auxD);
				i=pos;
                pos=buscaDiscNotas(TabAD,TLN,auxD);
                if(pos==-1)
                {
                	gotoxy(33,16);
		            textcolor(4);
		            printf("Disc. nao encontrado!\n");
		            textcolor(15);
		            getch();
		            LimpaTela();
                }
                else
                {
                	LimpaTela();
                	gotoxy(33,11);
                    printf("Disc.:%d - Nota:%.2f", TabAD[i].codigo.codD,TabAD[i].nota);
                    gotoxy(33,12);
                    printf("Confirmar a exclusao <S|N>: ");
                    if(toupper(getche())=='S')
                    {
                        for(;i<TLN-1;i++)
                        {
                            TabAD[i].codigo.codD=TabAD[i+1].codigo.codD;
                            strcpy(TabAD[i].aluno.RA,TabAD[i+1].aluno.RA);
                            TabAD[i].nota=TabAD[i+1].nota;
                        }
                        TLN--;
                        textcolor(9);
                        gotoxy(33,14);
                        printf("Exclusao feita!");
                        textcolor(15);
                        getch();
                    }
                }
            }
            LimpaTela();
            gotoxy(33,12);
			printf("'0' para finalizar:\n");
			gotoxy(33,13);
		    printf("Digite o RA que deseja excluir:");
			gotoxy(33,14);
		    printf("RA [xx.xx.xxxx-x]: ");
		    scanf("%s", aux);
    	}
	}
	LimpaTela();
	textcolor(9);
	gotoxy(40,18);
    printf("Exclusao finalizada!\n");
    getch();
    LimpaTela();	
}

char menuRelatorio (void)
{
	FormPrincipal();
	gotoxy(12,10);
	printf ("----RELATORIO----\n");
	gotoxy(13,13);
	printf ("[A] REPROVADOS\n");
	gotoxy(13,14);
	printf ("[B] ALUNOS LETRA\n");
	gotoxy(13,15);
	printf ("[C] DISC. PALAVRA\n");
	gotoxy(13,16);
	printf ("[D] MEDIA DISC\n");
	gotoxy(13,17);
	printf ("[E] REL. GERAL\n");
	gotoxy(13,18);
	printf("[F] VOLTAR\n");
	gotoxy(13,20);
	printf("Opcao: ");
	
	return toupper(getch());
}

char menu (void)
{
	FormPrincipal();
	gotoxy(13,10);
	printf ("------MENU------\n");
	gotoxy(13,12);
	printf ("[A] ALUNOS\n");
	gotoxy(13,13);
	printf ("[B] DISCIPLINAS\n");
	gotoxy(13,14);
	printf ("[C] ALUNO DISC.\n");
	gotoxy(13,15);
	printf ("[D] RELATORIOS\n");
	gotoxy(13,16);
	printf("[ESC] FECHAR\n");
	gotoxy(13,20);
	printf("Opcao: ");
	
	return toupper(getch());
}

char menudois (void)
{
	
	FormPrincipal();
	gotoxy(12,10);
	printf("---MENU ESCOLHA---\n");
	gotoxy(13,12);
	printf ("[A] CADASTRO\n");
	gotoxy(13,13);
	printf ("[B] ALTERAR\n");
	gotoxy(13,14);
	printf ("[C] EXCLUIR\n");
	gotoxy(13,15);
	printf ("[D] CONSULTAR\n");
	gotoxy(13,16);
	printf ("[E] ORDENAR\n");
	gotoxy(13,17);
	printf("[F] VOLTAR\n");
	gotoxy(13,20);
	printf("Opcao: ");
	
	return toupper(getch());
}

int main ()
{
	TabAlunosDisc TabAD[TF];
	TpDisc TabD[TF];
	TpAluno TabA[TF];
	char op;
	int TLA=0, TLD=0, TLN=0;
	
	do
	{
		op=menu();
		switch(toupper(op))
		{
			case 'A':
					clrscr();
//					printf("-------MENU ALUNOS-------\n");
					do
					{
						op=menudois();
						switch(toupper(op))
						{
							clrscr();
							case 'A':					
							CadastroAluno(TabA,TLA);	
							break;
							case 'B':
							alterarAlunos(TabA,TLA);
							break;
							case 'C':
							ExcluirAluno(TabA,TabAD,TLA,TLN);
							break;
							case 'D':
							consultaAlunos(TabA,TLA);
							break;
							case 'E':
							ordenarAluno(TabA,TLA);
							break;
							case 'F':
								LimpaTelaM();
							break;
						}
					}while(op !='F');									
			break;	
				
			case 'B':
					clrscr();
//					printf("-------MENU DISC.-------\n");
					do
					{					
						op=menudois();
						switch(toupper(op))
						{
							clrscr();
							case 'A':
							CadastroDisc(TabD,TLD);	
							break;
							case 'B':
							AlterarDisc(TabD,TLD);
							break;
							case 'C':
							ExcluirDisc(TabD, TabAD,TLD,TLN);
							break;
							case 'D':
							consultaDisc(TabD,TLD);
							break;
							case 'E':
							ordenarDisc(TabD,TLD);
							break;
							case 'F':
								LimpaTelaM();
							break;
						}
					}while(op !='F');
			break;
			
			case 'C':
					clrscr();
//					printf("-------ALUNO DISC.-------\n");
					do
					{	
						op=menudois();
						switch(toupper(op))
						{
							clrscr();
							case 'A':
							CadastroAlunoDisc(TabAD, TabD, TabA, TLN,TLA,TLD);	
							break;
							case 'B':
							AlterarNotas(TabAD,TLN);
							break;
							case 'C':
							ExcluirAlunoDisc(TabAD,TLN);
							break;
							case 'D':
							consultaAlunoDisc(TabAD,TabA,TLA,TLN);
							break;
							case 'E':
							ordenarAlunoDisc(TabAD,TLN);
							break;
							case 'F':
								LimpaTelaM();
							break;
						}
					}while(op !='F');
			break;
					
			case 'D':
					clrscr();
					do
					{
						op = menuRelatorio();
						switch(toupper(op))
						{
							clrscr();
							case 'A':
							Reprovados(TabAD,TabA, TLN, TLA);
							break;
							case 'B':
							AlunosPorLetra(TabA,TLA);
							break;
							case 'C':
							PesquisaPorPalavra(TabAD,TabD,TLN,TLD);
							break;
							case 'D':
							mediaRep(TabAD,TabD,TLN,TLD);
							break;
							case 'E':
							RelatorioGeral(TabAD,TabA,TabD,TLN,TLA,TLN);
							break;
							case 'F':
								LimpaTelaM();
							break;						
						}
					}while(op !='F');
				break;					
		}
	}while(op != 27);
	
	return 0;
}

