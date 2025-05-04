#include <conio2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int i,j=1,c=1,cor2,cor1,l=0;
	char nome;
	
	for(i=0;i<255;i++)
	{
		
		cor1=i;
		cor2=i+3;
		gotoxy(c,j);
		textcolor(cor1);
		textbackground(cor2);
		//_sleep(200);
		printf("%c<->%d\n",i,i);
		j++;
		
		if(j==25)
		{
			j=1;
			c=c+10;
		}
	}
	getch();
	return 0;
}
