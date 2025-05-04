    #include<stdio.h> // Biblioteca principal
#include<conio2.h> // Biblioteca para utilizar moldura
#include<string.h> // Biblioteca para manipulação de strings
#include<stdlib.h> // Biblioteca que converte string para numero
#include<ctype.h>

struct Aluno {
    int ra;
    char nome[50],status;
};

struct Disciplina {
    int codigo;
    char nome[50];
};

struct Boletim {
    int ra;
    int codigo;
    float nota;
};

void erro(void)
{
	printf("Erro ou nao tem nessa poha!!\n");
	getch();	
}

char menu(void)
{
	clrscr();
	printf("\n# # # #   M E N U   # # # #\n");
	printf("\n[A] - Cadastrar Alunos");
	printf("\n[B] - Exibir Alunos");
	printf("\n[C] - Consultar Funcionarios");
	printf("\n[D] - Alterar Funcionarios");
	printf("\n[E] - Ordenar Funcionarios");
	printf("\n[ESC] - Finalizar");
	printf("\nOpcao desejada: \n");
	return toupper(getch());
}

int buscaRa(FILE *ptr, int ele)
{
	Aluno tab;
	
	rewind(ptr);
	fread(&tab,sizeof(Aluno),1,ptr);
	while(!feof(ptr) && !(ele == tab.ra && tab.status == 'A'))
		fread(&tab,sizeof(Aluno),1,ptr);
		
	if(!feof(ptr) && tab.status == 'A')
		return ftell(ptr)-sizeof(Aluno);
	else
		return -1;
}

void ordenaAluno(FILE *ptr) {
    Aluno a, b;
    fseek(ptr, 0, SEEK_END);
    int f = ftell(ptr) / sizeof(Aluno), pos, i;

    if (f > 1) {
        pos = (f - 1) * sizeof(Aluno);
        fseek(ptr, pos, SEEK_SET);
        fread(&a, sizeof(Aluno), 1, ptr);

        pos = (f - 2) * sizeof(Aluno);
        fseek(ptr, pos, SEEK_SET);
        fread(&b, sizeof(Aluno), 1, ptr);

        while (f > 1 && a.ra < b.ra) {
            pos = (f - 1) * sizeof(Aluno);
            fseek(ptr, pos, SEEK_SET);
            fwrite(&b, sizeof(Aluno), 1, ptr);

            pos = (f - 2) * sizeof(Aluno);
            fseek(ptr, pos, SEEK_SET);
            fwrite(&a, sizeof(Aluno), 1, ptr);
            f--;

            if (f > 1) {
                pos = (f - 1) * sizeof(Aluno);
                fseek(ptr, pos, SEEK_SET);
                fread(&a, sizeof(Aluno), 1, ptr);

                pos = (f - 2) * sizeof(Aluno);
                fseek(ptr, pos, SEEK_SET);
                fread(&b, sizeof(Aluno), 1, ptr);
            }
        }

        fseek(ptr, 0, SEEK_END);
    }
}


void salvarAlunos(void)
{
    FILE *ptra = fopen("alunos.dat", "ab+");
    Aluno tpa;

    if (ptra == NULL)
        erro();
    else
    {
        printf("\nRA: ");
        scanf("%d", &tpa.ra);
        while (tpa.ra > 0)
        {
            int pos = buscaRa(ptra, tpa.ra);

            if (pos != -1)
            {
                // O aluno já existe, trata conforme necessário
                erro();
            }
            else
            {
                printf("\nNome do aluno: ");
                fflush(stdin);
                gets(tpa.nome);
                tpa.status = 'A';
                fwrite(&tpa, sizeof(Aluno), 1, ptra);
            }
            printf("\nRA: ");
            scanf("%d", &tpa.ra);
        }
        fclose(ptra);
    }
    getch();
}

void exibirAlunos()
{
	FILE * ptra = fopen("alunos.dat","rb+");
	Aluno tab;
	
	if(ptra == NULL)
		erro();
	else
	{
		//rewind(ptra);
		while( (fread(&tab,sizeof(Aluno),1,ptra) ) == 1)
		{
			ordenaAluno(ptra);
			if(tab.status = 'A')
			{
				printf("\nNome do aluno: %s",tab.nome);
				printf("\nRA do aluno: %d\n",tab.ra);	
			}
		}
		fclose(ptra);	
	}
	getch();
}

int main()
{
	char op;
	
	do //nao esquecer ta repetiçao
	{
		op = menu();
		switch(op)
		{
			case 'A':
				salvarAlunos();
				break;
				
			case 'B':
				exibirAlunos();			
				break;
		}	
	}while (op!=27);
    return 0;
}
