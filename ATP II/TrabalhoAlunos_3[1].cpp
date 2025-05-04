#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>
#define TF 50

struct TpAluno
{
	char nome[40], RA[13];

};

struct TpDisc
{
	char nomeD[40];
	int codD;
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
		//Sleep(50);
		gotoxy(a,LF);
		printf("%c",205);
	}
	for(a=LI+1; a<LF; a++)
	{
		gotoxy(CI,a);
		printf("%c",186);
		//Sleep(50);
		gotoxy(CF,a);
		printf("%c",186);
	}
	textcolor(7);
	textbackground(0);
}



void FormPrincipal(void)
{
	clrscr();
	Moldura(10,5,75,23,15,1);
	Moldura(11,6,74,8,15,8);
	gotoxy(24,7);
	textcolor (11);
	printf ("------------TRABALHO ATP II------------\n");
	Moldura(11,9,30,22,15,3);
	Moldura(31,9,74,22,15,9);
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
        gotoxy(36,11);
        printf("Cadastro cheio!\n");
        getch();
    }
    else
    {
        gotoxy(36,11);
        printf("Codigo da disciplina [xxx]:\n");
        gotoxy(36,12);
        printf("ou digite '0' para finalizar\n");
        gotoxy(63,11);
        scanf("%d", &aux);

        while(TLD < TF && aux > 0)
        {
            pos = buscaDisc(TabD, TLD, aux);
            if(pos != -1)
            {
                gotoxy(36,13);
                printf("Codigo ja cadastrado!\n");
                getch();
                clrscr();
            }
            else
            {
                if(aux > 999)
                {
                    gotoxy(36,13);
                    printf("Codigo invalido!\n");
                    getch();
                }
                else
                {
                    TabD[TLD].codD = aux;
                    gotoxy(36,13);
                    printf("Digite o nome da materia:\n");
                    fflush(stdin);
                    gotoxy(61,13);
                    gets(auxM);

                    i = buscaMat(TabD, TLD, auxM);
                    if(i != -1)
                    {
                        gotoxy(36,14);
                        printf("Materia ja cadastrada!\n");
                        getch();
                    }
                    else
                    {
                        strcpy(TabD[TLD].nomeD, auxM);
                        gotoxy(36,14);
                        printf("Materia cadastrada!\n");
                        TLD++;
                        getch();
                    }
                }
            }
            gotoxy(36,15);
            printf("\nCodigo da disciplina [xxx]:\n");
            gotoxy(36,16);
            printf("ou Digite '0 ' para finalizar\n");
            gotoxy(63,15);
            scanf("%d", &aux);
        }
    }
    gotoxy(36,17);
    printf("Cadastro finalizado!\n");
    getch();
    clrscr();
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
		gotoxy(33,14);
		printf("Cadastro cheio!\n");
		getch();
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
			pos=buscaRA(TabA, TL, aux);
			if(pos!=-1)
			{
				gotoxy(33,13);
				printf("RA ja cadastrado!\n");
				getch();
				clrscr();
			}
			else
			{
				if (strlen(aux)>12)
				{
					gotoxy(33,13);
					printf("RA invalido!\n");
					getch();
					clrscr();
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
						printf("Nome ja cadastrado!\n");
						getch();
					}
					else
					{
						strcpy(TabA[TL].nome,auxN);
						gotoxy(33,14);
						printf("Cadastro feito!\n");						
						TL++;
						getch();
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
	gotoxy(40,17);
	printf("Cadastro finalizado!\n");
	getch();
	clrscr();
}

void CadastroAlunoDisc (TabAlunosDisc TabAD[TF], TpDisc TabD[TF], TpAluno TabA[TF], int &TL, int TLA, int TLD)
{
    int pos, auxD;
    char aux[13];
    clrscr();
    FormPrincipal();
    gotoxy(32,10);
    printf("-------CADASTRO DE NOTAS-------\n");
    if(TL >= TF)
    {
        gotoxy(32,14);
        printf("Cadastro cheio!\n");
        getch();
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
            gotoxy(33,14);
            printf("-> Aluno nao cadastrado!\n");
            getch();
        }
        else
        {
            strcpy(TabAD[TL].aluno.RA, aux);
            gotoxy(33,14);
            printf("Digite o cod. da materia: ");
            scanf("%d", &auxD);
            pos = buscaDisc(TabD, TLD, auxD);
            if(pos == -1)
            {
                gotoxy(33,15);
                printf("-> Materia nao cadastrada!\n");
                getch();
            }
            else
            {
                TabAD[TL].codigo.codD = auxD;
                gotoxy(33,15);
                printf("Digite a nota: ");
                scanf("%f", &TabAD[TL].nota);
                gotoxy(33,17);
                printf("Cadastro finalizado!\n");
                TL++;
                getch();
            }                    
        }
        printf("'0' para finalizar\n");
        gotoxy(33,12);
        printf("RA [xx.xx.xxxx-x]: ");
        fflush(stdin);
        gets(aux);
    }

    printf("Cadastro finalizado!\n");
    getch();
    clrscr();
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
        gotoxy(36,11);
        printf("Cadastro vazio!\n");
        getch();
    }
    else
    {
        gotoxy(34,11);
        printf("Digite o RA do aluno que deseja excluir:\n");
        gotoxy(34,12);
        printf("ou Digite '0' para finalizar\n");
        gotoxy(34,13);
        printf("RA [xx.xx.xxxx-x]:\n");
        gotoxy(52,13);
        scanf("%s",&aux);
        while(strcasecmp(aux,"0")!=0)
        {
            pos=buscaRA(TabA,TL,aux);
            gotoxy(34,14);
            if(pos==-1)
            {
            	printf("RA nao encontrado\n");
                getch();
            }            
            else
            {
				i=pos;
                pos=buscaRANotas(TabAD,TLN,aux);
                if(pos!=-1)
                {
                    printf("Nao e possivel excluir\n");
                    getch();
                }
                else
                {
                    printf("Deseja excluir o aluno %s ?<S|N>\n", TabA[i].nome);
                    if(toupper(getche())=='S')
                    {
                        for(;i<TL-1;i++)
                        {
                            strcpy(TabA[i].nome,TabA[i+1].nome);
                            strcpy(TabA[i].RA, TabA[i+1].RA);
                        }
                        TL--;
                        printf("Exclusao feita!\n");
                        getch();
                    }
                }
            }
            gotoxy(34,11);
	        printf("\nDigite o RA do aluno que deseja excluir:\n");
	        gotoxy(34,12);
	        printf("ou Digite 'SAIR' para finalizar\n");
	        gotoxy(34,13);
	        printf("RA [xx.xx.xxxx-x]:\n");
	        gotoxy(52,13);
	        scanf("%s",&aux);
    	}
	}
	printf("exclusao concluida!\n");
	getch();
	clrscr();
}

void consultaAlunos (TpAluno TabA[TF], int TL)
{
	int pos;
	char aux[13];
	clrscr();
	FormPrincipal();
	gotoxy(32,10);
	printf("-------COSULTA ALUNOS-------\n");
	if(TL==0)
	{
		gotoxy(36,13);
		printf("Cadastro vazio!\n");
		getch();
	}
	else
	{
		gotoxy(36,12);
		printf("Digite o RA que deseja\n");
		gotoxy(36,13);
		printf("ou Digite '0' para finalizar:\n");
		gotoxy(36,14);
		printf("RA [xx.xx.xxxx-x]:\n");
		gotoxy(54,14);
		scanf("%s",&aux);
		
		while(strcasecmp(aux,"0")!=0)
		{
			pos=buscaRA(TabA,TL,aux);
			gotoxy(36,15);
			if (pos==-1)
				printf("RA nao encontrado!\n");
			else
			{
				gotoxy(36,15);
				printf("RA: %s Aluno: %s\n", TabA[pos].RA,TabA[pos].nome);
				getch();
			}
			gotoxy(36,16);
			printf("Digite o RA que deseja:\n");
			gotoxy(36,17);
			printf("ou Digite 'SAIR' para finalizar:\n");
			gotoxy(36,18);
			printf("RA [xx.xx.xxxx-x]:\n");
			gotoxy(54,18);
			scanf("%s",&aux);
		}
		gotoxy(36,19);
		printf("Consulta finalizada!\n");
		getch();
		clrscr();
	}
	
}

void consultaDisc(TpDisc TabD[TF], int TL)
{
    int pos, aux, i = 10;
    clrscr();
    FormPrincipal();
    gotoxy(36, i);
    printf("-------CONSULTA DISC.-------\n");
    i++;

    if(TL == 0)
    {
        gotoxy(32, i);
        printf("Cadastro vazio!\n");
        getch();
    }
    else
    {
        i++;
        gotoxy(32, i);
        printf("Codigo da disciplina [xxx]:\n");
        i++;
        gotoxy(32, i);
        printf("ou Digite '0' para finalizar:\n");
        gotoxy(59, i-1);
        scanf("%d", &aux);
        
        while(aux != 0)
        {
            pos = buscaDisc(TabD, TL, aux);
            i++;
            gotoxy(32, i);
            if(pos == -1)
            {
                printf("Cod. nao encontrado!\n");
                getch();
            }
            else
            {
                printf("Cod.:[%d] Disc.:%s\n", TabD[pos].codD, TabD[pos].nomeD);
                getch();
            }
            
            i += 2;
            gotoxy(32, i);
            printf("Codigo da disciplina [xxx]:\n");
            i++;
            gotoxy(32, i);
            printf("ou Digite '0' para finalizar:\n");
            gotoxy(59, i-1);
            scanf("%d", &aux);
        }
    }

    i++;
    gotoxy(32, i);
    printf("Consulta finalizada!\n");
    getch();
    clrscr();
}

void consultaAlunoDisc (TabAlunosDisc TabAD[TF], TpAluno TabA [TF], int TL, int TLN)
{
    int pos, i;
    char aux[13];
    clrscr();
    printf("-------CONSULTA ALUNO DISC.-------\n");

    if (TL == 0)
    {
        printf("Cadastro vazio!\n");
        getch();
    }
    else
    {
        printf("\nDigite o RA que deseja consultar:\n");
        printf("ou Digite '0' para finalizar:\n");
        printf("RA [xx.xx.xxxx-x]:\n");
        scanf("%s", aux);

        while (strcasecmp(aux, "0") != 0)
        {
            pos = buscaRA(TabA, TL, aux);

            if (pos == -1)
            {
                printf("RA nao encontrado!\n");
                getch();
            }
            else
            {
                printf("Disciplinas e notas do aluno com RA %s:\n", aux);

                for (i = 0; i < TLN; i++)//0=pos
                {
                    if (strcmp(TabAD[i].aluno.RA, aux) == 0) 
                    {                   	
                        printf("Disciplina: %d | Nota: %.2f\n", TabAD[i].codigo.codD, TabAD[i].nota);
                    }
                }
                getch();
            }

            printf("\nDigite o RA que deseja consultar:\n");
            printf("ou Digite 'SAIR' para finalizar:\n");
            printf("RA [xx.xx.xxxx-x]:\n");
            scanf("%s", aux);
        }
    }

    printf("Consulta finalizada!\n");
    getch();
    clrscr();
}

void AlunosPorLetra (TpAluno TabA[TF], int TL)
{
    int i, achou=0;
    char aux;
    clrscr();
    printf("----CONSULTA ALUNOS POR LETRA----\n");
    if(TL==0)
    {
        printf("Cadastro vazio!\n");
        getch();
    }
    else
    {
        printf("Digite a letra inicial do aluno:\n");
        printf("ou digite '0' para sair\n");
        scanf(" %c", &aux);
        while(aux!='0')
        {
            for(i=0;i<TL;i++)
            {
                if(aux==TabA[i].nome[0]){
                    printf("%s\n", TabA[i].nome);
                    achou=1;
                }
            }
            if(achou==0)
            {
            	printf("Nenhum aluno cadastrado com a letra: '%c' na inicial!\n");
            	getch();
            }  	
            printf("Digite a letra inicial do aluno:\n");
            printf("ou digite '0' para sair\n");
            scanf(" %c", &aux);
        }

    }
    getch();
    clrscr();
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
		gotoxy(36,11);
		printf("Cadastro vazio!\n");
		getch();
	}
	else
	{
		gotoxy(32,11);
		printf("Cod. da disc. que deseja alterar[xxx]:\n");
		gotoxy(32,12);
		printf("ou digite '0' para finalizar.\n");
		gotoxy(70,11);
		scanf("%d", &aux);
		while( TLD<TF&&aux>0)
		{
			pos=buscaDisc(TabD, TLD, aux);
			gotoxy(32,13);
			if(pos==-1)
				printf("Cod. nao encontrado\n");
			else
			{
				gotoxy(32,13);
				printf("Cod.:[%d] Disc.:%s\n",TabD[pos].codD, TabD[pos].nomeD);
				gotoxy(32,14);
				printf("Deseja alterar o nome?<S|N>:\n");
				gotoxy(61,14);
				if(toupper(getche())=='S')
				{
					gotoxy(32,15);
					printf("Digite o nome da nova disc.:\n");
					fflush(stdin);
					gotoxy(60,15);
					gets(auxM);
					i=pos;
					pos=buscaMat(TabD,TLD,auxM);
					if(pos!=-1)
					{
						gotoxy(32,16);
						printf("Nome ja cadastrado!\n");
						getch();
					}
					else
					{
						strcpy(TabD[i].nomeD,auxM);
						gotoxy(32,16);
						printf("Alteracao concluida!\n");
					}
				}
	
			}
			gotoxy(32,17);
			printf("\nCodigo da disciplina que deseja alterar[xxx]:\n");
			gotoxy(32,18);
			printf("ou digite '0' para finalizar.\n");
			gotoxy(69,18);
			scanf("%d", &aux);
		}
	
	}
	gotoxy(69,19);
	printf("Alteracao finalizada!\n");
	getch();
	clrscr();
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
		gotoxy(36,11);
		printf("Cadastro vazio!\n");
		getch();
	}
	else
	{
		gotoxy(35,11);
		printf("Digite o RA do aluno que deseja alterar\n");
		gotoxy(35,12);
		printf("ou digite '0' para finalizar\n");
		gotoxy(35,13);
		printf("RA [xx.xx.xxxx-x]:\n");
		fflush(stdin);
		gotoxy(53,13);
		gets(aux);
		while(strcasecmp(aux,"0")!=0)
		{
			pos=0;
			pos=buscaRA(TabA,TL,aux);
			gotoxy(35,14);
			if (pos==-1)
				printf("RA nao encontrado!\n");
			else
			{
				gotoxy(35,15);
				printf("RA: %s  Aluno: %s\n", TabA[pos].RA,TabA[pos].nome);
				getch();
				gotoxy(35,16);
				printf("Deseja alterar o nome do aluno?<S|N>\n");
				if (toupper(getche())=='S')
				{
					gotoxy(35,17);
					printf("Digite o novo nome:\n");					
					fflush(stdin);
					gotoxy(54,17);
					gets(auxN);
					i=pos;
					pos=buscaAluno(TabA,TL,auxN);
					if(pos!=-1)
					{
						gotoxy(35,18);
						printf("Nome ja cadastrado!\n");
						getch();
					}
					else
					{
						strcpy(TabA[i].nome,auxN);
						gotoxy(35,18);
						printf("Alteracao concluida!\n");
					}
				}
			}
			gotoxy(35,19);
			printf("Digite o RA do aluno que deseja alterar\n");
			gotoxy(35,20);
			printf("ou digite 'SAIR' para finalizar");
			gotoxy(35,21);
			printf("RA [xx.xx.xxxx-x]:\n");
			fflush(stdin);
			gotoxy(55,21);
			gets(aux);
		}
	}	
	gotoxy(36,22);
	printf("Alteracao finalizada!\n");
	getch();
	clrscr();
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
		gotoxy(36,11);
		printf("Cadastro vazio!\n");
		getch();
	}
	else
	{
        gotoxy(32,11);
        printf("Digite o RA: ");
        printf("ou Digite '0' para finalizar:\n");
        printf("RA [xx.xx.xxxx-x]:\n");
        scanf("%s",&aux);
        while(TL < TF && strcasecmp(aux, "0") != 0)
        {
        	pos=buscaRANotas(TabAD,TL,aux);
        	if(pos==-1)
        	{
        		printf("Aluno sem notas!\n");
        		getch();
        	}
        	else
        	{
        		printf("Digite a disc. que deseja alterar nota:\n");
        		printf("(xxx)\n");
        		scanf("%d",&auxD);
        		i=pos;
        		pos=buscaDiscNotas(TabAD,TL,auxD);
        		if(pos==-1)
        		{
        			printf("Disc. nao cadastrada!\n");
        			getch();
        		}
        		else
        		{
        			printf("Disc.:%d | Nota:%.2f\n",TabAD[i].codigo.codD,TabAD[i].nota);
        			printf("Deseja alterar a nota?<S|N>\n");
        			if(toupper(getche())=='S')
        			{
        				gotoxy(32,11);
        				printf("Digite a nova nota:\n");
        				scanf("%f",&TabAD[i].nota);
        				printf("Alteracao concluida!\n");
        			}
        		}	
        	}
       		gotoxy(32,11);
      		printf("\nDigite o RA: ");
       		printf("ou Digite '0' para finalizar:\n");
        	printf("RA [xx.xx.xxxx-x]:\n");
        	scanf("%s",&aux);
        }       
	}
	printf("Alteracao finalizada!\n");
	getch();
	clrscr();
}

void Reprovados (TabAlunosDisc TabAD[TF], TpAluno TabA[TF], int TLN, int TLA,int &k)
{
    int i, j, cont,pos;
    clrscr();
    gotoxy(36,10);
    printf("Alunos reprovados em 2 ou mais materias\n");
    if(TLN==0)
    {
        gotoxy(32,11);
        printf("NAO EXISTEM CADASTROS\n");
        getch();
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
                gotoxy(32,k);
                printf("RA: %s | NOME: %s ", TabAD[i].aluno.RA, TabA[pos].nome);
                k++;
            }
        }
    }
    getch();
}

void PesquisaPorPalavra(TabAlunosDisc TabAD[TF], TpDisc Disc[TF], int TL, int TLD) 
{
    char aux[40]; 
    int i;
    printf("RELATORIO POR PALAVRA\n");
    if (TLD == 0)
	 {
        printf("Sem cadastros\n");
        getch();  
     } 
	else
	{
        printf("Digite um pedaco da palavra: ");
        fflush(stdin);
        gets(aux);
        if (strlen(aux) == 0)
		 {
            printf("Nao ha cadastros\n");
            getch();
         }
        for (i = 0; i < TLD; i++)
		 {
            if (strstr(Disc[i].nomeD, aux) != 0)
			{ 
                printf("%s\n", Disc[i].nomeD); 
            }
         }

    }
    getch(); 
}

/*void Limpatela(void)
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
}*/

void RelatorioGeral (TabAlunosDisc TabAD[TF], TpAluno TabA[TF], TpDisc TabD[TF], int TLN, int TLA, int TLD)
{
	int i, j, pos;
	if(TLN==0)
	{
		printf("SEM RELATORIOS\n");
		getch();
	}
	else
	{
		for(i=0;i<TLN;i+=j)
		{
			j=0;
			pos=buscaRA(TabA,TLA,TabAD[i].aluno.RA);
			printf("RA:%s Nome:%s\n", TabAD[i].aluno.RA, TabA[pos].nome);
			while(i+j<TLN && stricmp(TabAD[i].aluno.RA, TabAD[i+j].aluno.RA)==0)
			{
				pos=buscaDisc(TabD,TLD,TabAD[i+j].codigo.codD);
				printf("Disciplina: %d - %s ", TabAD[i+j].codigo.codD, TabD[pos].nomeD);
				if(TabAD[i+j].nota >= 6)
					printf("Nota: %.2f Situacao: Aprovado\n", TabAD[i+j].nota);
				else
					printf("Nota: %.2f Situacao: Reprovado\n", TabAD[i+j].nota);
				j++;
			}
		}
	}
	getch();
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
        gotoxy(36,11);
        printf("Cadastro vazio!\n");
        getch();
    }
    else
    {
        gotoxy(32,11);
        printf("Digite o cod. da disciplina[xxx]: ");
        gotoxy(60,11);
        printf("Ou '0' para sair.\n");
        scanf("%d", &aux);
        while(TLD<TF&&aux>0)
        {
	        pos = buscaDisc(TabD, TLD, aux);
	        gotoxy(32,12);
	        if(pos == -1)
	        {
	        	printf("Cod. nao encontrado\n");
	            getch();
	        }           
	        else
	        {
	           i=pos;
	           pos=buscaDiscNotas(TabAD,TLN,aux);   
			   if(pos!=-1)
	            {
	            	printf("Nao e possivel excluir\n");
	            	getch();
	            }
	            else
	            {
	                printf("Deseja excluir a disc %s ?<S|N>\n", TabD[i].nomeD);
	                if(toupper(getche())=='S')
	                {
	                    for(;i<TLD-1;i++)
	                    {
	                        strcpy(TabD[i].nomeD,TabD[i+1].nomeD);
	                        TabD[i].codD=TabD[i+1].codD;
	                    }
	                    TLD--;
	                    printf("Exclusao feita!\n");
	                    getch();
	                }
	            }
        	}
        gotoxy(32,11);
        printf("\nDigite o cod. da disciplina[xxx]: ");
        gotoxy(60,11);
        printf("Ou '0' para sair.\n");
        scanf("%d", &aux);
        }       
    }
    printf("Exclusao concluida!\n");
	getch();
    clrscr();
}

void ordenarAluno(TpAluno TabA[TF], int TL)
{	
	int i=0, j=1; 
	char aux[13];
	
	if(TL==0)
		printf("\nNao ha alunos cadastrados!\n");
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
		printf("\nTabela de alunos ordenada pelo RA!\n");	
		getch();
	}	
}

void ordenarDisc(TpDisc TabD[TF], int TL)
{	
	int i=0, j=1, aux; 
	
	if(TL==0)
		printf("\nNao ha disc. cadastrados!\n");
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
		printf("\nTabela de disc. ordenada pelo cod.!\n");	
		getch();
	}	
}

void ordenarAlunoDisc(TabAlunosDisc TabAD[TF], int TL)
{	
	int i=0, j=1; 
	char aux[13];
	
	if(TL==0)
		printf("\nNao ha cadastros!\n");
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
		printf("\nTabela de alunos disc. ordenada pelo RA!\n");	
		getch();
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
    	printf("Cadastro vazio!\n");
    	getch();
    }
    else
    {
    	gotoxy(32,11);
    	printf("Digite o RA:\n");
    	gotoxy(33,11);
      	printf("ou Digite '0' para finalizar\n");
        gotoxy(34,13);
        printf("RA [xx.xx.xxxx-x]:\n");
        gotoxy(52,13);
        scanf("%s",&aux);
		while(strcasecmp(aux,"0")!=0)
        {
            pos=buscaRANotas(TabAD,TLN,aux);
            gotoxy(34,14);
            if(pos==-1)
            {
            	printf("RA nao encontrado\n");
                getch();
            }            
            else
            {
            	printf("Digite o codigo da disc. [xxx]\n");
            	scanf("%d",&auxD);
				i=pos;
                pos=buscaDiscNotas(TabAD,TLN,auxD);
                if(pos==-1)
                {
                    printf("Disc. nao encontrada!\n");
                    getch();
                }
                else
                {
                    printf("Disc.:%d - Nota:%.2f", TabAD[i].codigo.codD,TabAD[i].nota);
                    printf("\nConfirmar a exclusao?<S|N>\n");
                    if(toupper(getche())=='S')
                    {
                        for(;i<TLN-1;i++)
                        {
                            TabAD[i].codigo.codD=TabAD[i+1].codigo.codD;
                            strcpy(TabAD[i].aluno.RA,TabAD[i+1].aluno.RA);
                            TabAD[i].nota=TabAD[i+1].nota;
                        }
                        TLN--;
                        printf("Exclusao feita!\n");
                        getch();
                    }
                }
            }
            gotoxy(34,11);
	        printf("\nDigite o RA do aluno que deseja excluir:\n");
	        gotoxy(34,12);
	        printf("ou Digite 'SAIR' para finalizar\n");
	        gotoxy(34,13);
	        printf("RA [xx.xx.xxxx-x]:\n");
	        gotoxy(52,13);
	        scanf("%s",&aux);
    	}
	}
	printf("exclusao concluida!\n");
	getch();
	clrscr();	
}

char menuRelatorio (void)
{
	FormPrincipal();
	gotoxy(12,10);
	printf ("----RELATORIO----\n");
	gotoxy(13,13);
	printf ("[A] REPROVADOS\n");
	gotoxy(13,14);
	printf ("[B] ALUNOS POR LETRA\n");
	gotoxy(13,15);
	printf ("[C] DISCIPLINA POR PALAVRA\n");
	gotoxy(13,16);
	printf ("[D] MEDIA DISCIPLINAS\n");
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
	int TLA=0, TLD=0, TLN=0,k=12;
	
	do
	{
		op=menu();
		switch(toupper(op))
		{
			case 'A':
					clrscr();
//					printf("-------MENU ALUNOS-------\n");
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
						break;
					}
			
			break;	
				
			case 'B':
					clrscr();
//					printf("-------MENU DISC.-------\n");
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
						ExcluirDisc(TabD, TabAD,TLN,TLD);
						break;
						case 'D':
						consultaDisc(TabD,TLD);
						break;
						case 'E':
						ordenarDisc(TabD,TLD);
						break;
						case 'F':
						break;
					}
			break;
			
			case 'C':
					clrscr();
//					printf("-------ALUNO DISC.-------\n");
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
						break;
					}
			break;
					
			case 'D':
					clrscr();
					op = menuRelatorio();
					switch(toupper(op))
					{
						clrscr();
						case 'A':
						Reprovados(TabAD,TabA, TLN, TLA, k);
						break;
						case 'B':
						AlunosPorLetra(TabA,TLA);
						break;
						case 'C':
						DisciplinaPorPalavra(TabAD,TabD,TLN,TLD)
						break;
					//	case 'D':
					//	MediaDisciplinas(TabAD,);
					//	break;
						case 'E':
						RelatorioGeral(TabAD,TabA,TabD,TLN,TLA,TLN);
						break;
						case 'F':
						break;						
					}
		}
	}while(op!=27);
	return 0;
}
