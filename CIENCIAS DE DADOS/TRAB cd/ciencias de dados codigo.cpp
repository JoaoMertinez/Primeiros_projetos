#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio2.h>
#include <windows.h>

void LimpaMensagem(void)
{	
	int x,y;
	for(x=20;x<78;x++){
		gotoxy(x,23);	
		printf(" ");
	}	
}

void LimpaTela(void)
{
	int x,y;
	//LIMPA QUADRADO
	for(x=30;x<=78;x++){
		for(y=6;y<=20;y++){
			gotoxy(x,y);
			printf(" ");
		}
	}
	//LIMPA MENSAGEM
	for(x=20;x<78;x++){
		gotoxy(x,23);	
		printf(" ");
	}	

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
	gotoxy(4,7);
	textcolor(5);
	printf("**Arvore Genealogica**");
	textcolor(4);
	gotoxy(4,10);
	printf("[A] Animais");
	textbackground(0);
	gotoxy(4,11);
	printf("[B] Creditos");
	gotoxy(4,19);
	printf("[ESC] Sair");
	textcolor(15);
}

void Formulario(void)
{
	system("cls");
	Moldura(1,1,80,25,10,5);
	gotoxy(24,3);
	textcolor(10);
	printf("#*** Ciencia de Dados ***#");
	textcolor(15);
	
	Moldura(2,2,79,4,14,1);
	Moldura(2,5,27,21,12,7);
	MenuPrincipal();
	Moldura(2,22,79,24,11,4);
	gotoxy(4,23);
	textcolor(10);
	printf("Mensagem: ");

	Moldura(28,5,79,21,9,6);
}

void creditos(){
	gotoxy(40,7);
	printf("# # # Feito por # # #");
	gotoxy(30,9);
	printf("Bhreno Gabriel Moraes Ferreira");
	gotoxy(30,10);
	printf("RA: 262318792");
	gotoxy(30,12);
	printf("Felipe Augusto Gobbo dos Santos");
	gotoxy(30,13);
	printf("RA: 262319020");
	gotoxy(30,15);
	printf("Joao Claudio Martinez");
	gotoxy(30,16);
	printf("RA: 262319640");
	gotoxy(30,18);
	printf("Luigi Sardelari Scaliante");
	gotoxy(30,19);
	printf("RA: 262318687");
	
	
	gotoxy(20,23);
	printf("Pressione qualquer tecla para sair");
	
	getch();
}

void menu()
{
	gotoxy(40,7);
	printf("#*** Arvore zoologico ***#");
	gotoxy(47,9);
	printf("FIPP UNOESTE");
	gotoxy(47,10);
	printf("trabalho desenvolvido na primeira versao da arvore");
	
	
	gotoxy(20,23);
	printf("Aperte qualquer tecla para continuar");
	
	 getch();
}

void Erro(void)
{
	gotoxy(20,23);
	printf("Valor invalido!, por favor apenas 'S' ou 'N'");
	getch();
	LimpaMensagem();
}

int verifica(int pos)
{
	int i;
	for(i=0; i<100 && pos !='S' && pos!= 'N' && pos!=27; i++)
	{
		Erro();
		pos = toupper(getch());
	}
	return pos;
}

void Animais(void)
{
	char x,op='S',p;
	int i=7;
	
	menu();
	LimpaTela();
	while(op == 'S')
	{
		gotoxy(30,7);
		printf("O animal tem barbatana? (S/N)");
		gotoxy(20,23);
		printf("Ou Pressione 2 [Esc] - Sair!");
		x = toupper(getch());
		x = verifica(x);
		if(x == 'S' && x != 27) //1
		{
			gotoxy(30,8);
			printf("Voa ou plana? (S/N)");
			gotoxy(20,23);
			printf("Ou Pressione 2 [Esc] - Sair!");
			x = toupper(getch());
			x = verifica(x);
			if(x == 'S' && x != 27) //2
			{
				gotoxy(30,9);
				printf("O animal e mamifero? (S/N)");
				gotoxy(20,23);
				printf("Ou Pressione 2 [Esc] - Sair!");
				x = toupper(getch());
				x = verifica(x);
				LimpaMensagem();
				if(x == 'S' && x != 27) //3
				{
					gotoxy(30,10);
					printf("O animal e aquatico? (S/N)");
					x = toupper(getch());
					x = verifica(x);
					if(x == 'S' && x != 27) //4
					{
						gotoxy(30,11);
						printf("Possui calda? (S/N)");
						x = toupper(getch());
						x = verifica(x);
						if(x == 'S' && x != 27) //5
						{
							gotoxy(30,12);
							printf("Possui pelos(CABELOS)? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S') //6 --- Desição Final
							{
								gotoxy(20,23);
								printf("O animal escolhido foi : 'Frut bat'");
							}
							else
							{
								gotoxy(20,23);
								printf("O animal escolhido foi: 'dolphin'");
							}
						}
						else
						{
							if(x != 27)
							{
								gotoxy(30,12);
								printf("Possui perna ou pata? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'beaver'");
								}
								else
								{
									gotoxy(30,13);
									printf("Ele e domestico? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Squirrel'");
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Wallaby'");
									}
									
								}
							}
							
						}
					}
					else
					{
						if(x != 27)
						{	
							gotoxy(30,11);
							printf("O animal e Predador? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S')
							{
								gotoxy(30,12);
								printf("Possui pelo(Cabelos)? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Clam'");
								}
								else
								{
									gotoxy(30,13);
									printf("Ele e Domestico? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Kiwi'");
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Rhea'");
									}
								}	
						
							}
							else
							{
								gotoxy(30,12);
								printf("Possui classe animal? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(30,13);
									printf("Possui respiracao nasal? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Slowworm'");
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Pitviper'");
									}
								}
								else
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Girl'");
								}
							}
						}
					}
					
				}
				else
				{
					if(x != 27)
					{
						gotoxy(30,10);
						printf("O animal e Aquatico? (S/N)");
						x = toupper(getch());
						x = verifica(x);
						if(x == 'S')
						{
							gotoxy(30,11);
							printf("Possui cauda? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S')
							{
								gotoxy(30,12);
								printf("Possui classe animal? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(30,13);
									printf("E domestico? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Lark'");
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Flamingo'");
									}
								}
								else
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Fruitbat'");
								}
							}
							else
							{
								gotoxy(20,23);
								printf("O animal escolhido foi: 'Chicken'");
							}
						}
						else
						{
							gotoxy(30,11);
							printf("E domestico? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S')
							{
								gotoxy(20,23);
								printf("O animal escolhido foi: 'Crow'");
							}
							else
							{
								gotoxy(20,23);
								printf("O animal escolhido foi: 'Vulture'");
							}
						}
					}
				}
					
			}
			else
			{
				if(x != 27)
				{
					gotoxy(30,9);
					printf("Tamanho  de um Gato? (S/N)");
					x = toupper(getch());
					x = verifica(x);
					if(x == 'S')
					{
						gotoxy(30,10);
						printf("Possui pelos(CABELOS)? (S/N)");
						x = toupper(getch());
						x = verifica(x);
						if(x == 'S')
						{
							gotoxy(30,11);
							printf("Possui classe animal? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S')
							{
								gotoxy(30,12);
								printf("Possui Ovos? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Seasnake'");
								}
								else
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Dolphin'");
								}
							}
							else
							{
								gotoxy(30,12);
								printf("Possui barbatanas? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Seal'");
								}
								else
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Sealion'");
								}
							}
						}
						else
						{
							gotoxy(30,11);
							printf("E aquatico? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S')
							{
								gotoxy(30,12);
								printf("E domestico? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Duck'");
								}
								else
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Swan'");
								}
							}
							else
							{
								gotoxy(30,12);
								printf("E mamifero? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Penguin'");
								}
								else
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Gull'");
								}
							}
						}
					}
					else
					{
						gotoxy(30,10);
						printf("E aquatico? (S/N)");
						x = toupper(getch());
						x = verifica(x);
						if(x == 'S')
						{
							gotoxy(30,11);
							printf("Possui cauda? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S')
							{
								gotoxy(20,23);
								printf("O animal escolhido foi: 'Haddock'");
							}
							else
							{
								gotoxy(20,23);
								printf("O animal escolhido foi: 'Carp'");
							}
						}
						else
						{
							gotoxy(30,11);
							printf("E domestico? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S')
							{
								gotoxy(30,12);
								printf("E predador? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Seawasp'");
								}
								else
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Bass'");
								}
							}
							else
							{
								gotoxy(30,12);
								printf("Possui respiracao nasal? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Dogfish'");
								}
								else
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Stingray'");
								}
							}
							
						}
					}
				}
			}
				
				
		}
		else
		{
			if(x != 27)
			{
				gotoxy(30,8);
				printf("E domestico? (S/N)");
				gotoxy(20,23);
				printf("Ou Pressione 2 [Esc] - Sair!");
				x = toupper(getch());
				x = verifica(x);
				if(x == 'S' && x != 27)
				{
					gotoxy(30,9);
					printf("E aquatico? (S/N)");
					gotoxy(20,23);
					printf("Ou Pressione 2 [Esc] - Sair!");
					x = toupper(getch());
					x = verifica(x);
					if(x == 'S' && x != 27)
					{
						gotoxy(30,10);
						printf("E mamifero (S/N)");
						gotoxy(20,23);
						printf("Ou Pressione 2 [Esc] - Sair!");
						x = toupper(getch());
						x = verifica(x);
						LimpaMensagem();
						if(x == 'S' && x != 27)
						{
							gotoxy(30,11);
							printf("Possui classe animal? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S' && x != 27)
							{
								gotoxy(30,12);
								printf("Possui asas ou voa? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Flea'");
								}
								else
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Toad'");
								}
							}
							else
							{
								if(x != 27)
								{
									gotoxy(30,12);
									printf("Possui cauda? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Hare'");
									}
									else
									{
										gotoxy(30,13);
										printf("Possui pernas? (S/N)");
										x = toupper(getch());
										x = verifica(x);
										if(x == 'S')
										{
											gotoxy(20,23);
											printf("O animal escolhido foi: 'Cavy'");
										}
										else
										{
											gotoxy(20,23);
											printf("O animal escolhido foi: 'Hamster'");
										}
									}
								}
								
							}
						}
						else
						{
							if(x !=27)
							{
								gotoxy(30,11);
								printf("Possui respiracao nasal? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(30,12);
									printf("Possui classe animal? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Gnat'");
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Housefly'");
									}
								}
								else
								{
									gotoxy(30,12);
									printf("Possui cauda? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Wasp'");
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Honeybee'");
									}
								}
							}
							
						}
					}
					else
					{
						if(x != 27)
						{
							gotoxy(30,10);
							printf("E predador? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S')
							{
								gotoxy(30,11);
								printf("Possui asas ou voa? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(30,12);
									printf("Possui penas? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Scorpion'");
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Ladybird'");
									}
								}
								else
								{
									gotoxy(30,12);
									printf("Possui barbatanas? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(30,13);
										printf("Possui barbatanas? (S/N)");
										x = toupper(getch());
										x = verifica(x);
										if(x == 'S')
										{
											gotoxy(20,23);
											printf("O animal escolhido foi: 'Crab'");
										}
										else
										{
											gotoxy(20,23);
											printf("O animal escolhido foi: 'Starfish'");
										}
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Crayfish'");
									}
								}
							}
							else
							{
								gotoxy(30,11);
								printf("Possui asas ou voa? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(30,12);
									printf("Possui classes animal? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')	
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Tuatara'");
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Mole'");
									}
								}
								else
								{
									gotoxy(30,12);
									printf("Possui pernas? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Frog'");
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Newt'");
									}
								}
							}
						
						}
					}
				}
				else
				{
					if(x != 27)
					{
						gotoxy(30,9);
						printf("E aquatico? (S/N)");
						x = toupper(getch());
						x = verifica(x);
						if(x == 'S')
						{
							gotoxy(30,10);
							printf("Possui cauda? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S')
							{
								gotoxy(30,11);
								printf("Possui classe animal? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Tortoise'");
								}
								else
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Antelope'");
								}
							}
							else
							{
								gotoxy(20,23);
								printf("O animal escolhido foi: 'Calf'");
							}
						}
						else
						{
							gotoxy(30,10);
							printf("Possui asas ou voa? (S/N)");
							x = toupper(getch());
							x = verifica(x);
							if(x == 'S')
							{
								gotoxy(30,11);
								printf("Possui pernas? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Bear'");
								}
								else
								{
									gotoxy(30,12);
									printf("Possui cauda? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Boar'");
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Pussycat'");
									}
								}
							}
							else
							{
								gotoxy(30,11);
								printf("Possui classe animal? (S/N)");
								x = toupper(getch());
								x = verifica(x);
								if(x == 'S')
								{
									gotoxy(20,23);
									printf("O animal escolhido foi: 'Octopus'");
								}
								else
								{
									gotoxy(30,12);
									printf("Possui penas? (S/N)");
									x = toupper(getch());
									x = verifica(x);
									if(x == 'S')
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Mink'");
									}
									else
									{
										gotoxy(20,23);
										printf("O animal escolhido foi: 'Platplus'");
									}
								}
							}
					
						}
					}
				}
			}
		}
		getch();
		LimpaTela();
		gotoxy(30,07);
		printf("Deseja continuar o programa? (S/N)");
		op = toupper(getch());
		op = verifica(op);
		LimpaTela();	
	}
}

int main(void)
{
	char p;
	Formulario();
	
	gotoxy(20,23);
	printf("Selecione uma das opcoes ao lado:  ");
	
	do
	{
		p = toupper(getch());
		LimpaTela();
		switch(p)
		{
		case 'A' : Animais();
				   break;
		
		case 'B' : creditos();
				   break;
		}
	}
	while(p!=27);
	LimpaMensagem();
	gotoxy(20,23);
	printf("Programa finalizado!");
	printf("\n\n\n\n");
}
