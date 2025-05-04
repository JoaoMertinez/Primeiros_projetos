#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>

int main(void)
{
	int ci,li,cf,lf,i,j=0,x,y,op;
	
	printf("\ndigite a coluna inicial: ");
	scanf("%d",&ci);
	printf("\ndigite a linha inicial: ");
	scanf("%d",&li);
	printf("\ndigite a coluna final: ");
	scanf("%d",&cf);
	printf("\ndigite a linha final: ");
	scanf("%d",&lf);
	clrscr();
	
	gotoxy(ci,li);
	textcolor(2);
	printf("%c",201);
	textcolor(2);
	gotoxy(ci,lf);
	textcolor(2);
	printf("%c",200);
	gotoxy(cf,li);
	textcolor(2);
	printf("%c",187);
	textcolor(2);
	gotoxy(cf,lf);
	textcolor(2);
	printf("%c",188);
	
	for(i=ci+1;i<cf;i++)
	{
		textcolor(2);
		gotoxy(i,li);
		printf("%c",205);
		
		textcolor(2);
		gotoxy(i,lf);
		printf("%c",205);
		
	}
	
	for(i=li+1;i<lf;i++)
	{
		textcolor(2);
		gotoxy(ci,i);
		printf("%c",186);
		
		textcolor(2);
		gotoxy(cf,i);
		printf("%c",186);
		
	}
	
	x=(ci+cf)/2;
	y=(li+lf)/2;
	gotoxy(x,y);
	printf("%c",1);
		
	
	do
	{
		op=getch();
		{
			switch(op)
			{
				case 80:
					y=y+1;
					gotoxy(x,y);
					printf("%c",1);
					gotoxy(x,y-1);
					printf("%c",32);
					if(y==lf-1)
					{
						gotoxy(x,li+1);
						printf("%c",1);	
						gotoxy(x,lf-1);
						printf("%c",32);
						y=li;
						gotoxy(x,y+1);
						printf("%c",1);	
						gotoxy(x,li);
						printf("%c",205);
						
					}
					gotoxy(x,li);
					printf("%c",205);
					
				break;
				
				case 72:
					y=y-1;
					gotoxy(x,y);
					printf("%c",1);
					gotoxy(x,y+1);
					printf("%c",32);
					if(y==li-1)
					{
						gotoxy(x,lf-1);
						printf("%c",1);	
						gotoxy(x,li-1);
						printf("%c",32);
						y=lf;
						gotoxy(x,y-1);
						printf("%c",1);	
						gotoxy(x,li);
						printf("%c",205);
						
					}
					gotoxy(x,lf);
					printf("%c",205);
				break;
				
				case 75:
					x=x-1;
					gotoxy(x,y);
					printf("%c",1);
					gotoxy(x+1,y);
					printf("%c",32);
				
				break;
				
				case 77:
					x=x+1;
					gotoxy(x,y);
					printf("%c",1);
					gotoxy(x-1,y);
					printf("%c",32);
					if(x==cf-1)
					{
						gotoxy(ci+1,y);
						printf("%c",1);	
						gotoxy(cf-1,y);
						printf("%c",32);	
						x=ci;
						gotoxy(x+1,y);
						printf("%c",1);	
						gotoxy(x,ci);
						printf("%c",186);				
					}
					gotoxy(x,ci);
					printf("%c",186);
				break;
				
			}	
		}
	}while(op != 72 || 80 || 75 || 77);
	
	
	
	getch();
	return 0;
}
