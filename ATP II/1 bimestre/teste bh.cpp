#include <stdio.h>
int main()
{
	int horaex,falta,premio;
	float grat;
	
	printf(" digite o numero de horas extras trabalhadas em minutos\n");
	scanf("%d",&horaex);
	while(horaex>=0)
	{
		printf("digite o numero de horas faltas em minutos\n");
		scanf("%d",&falta);
		if(horaex<=600)
			premio=100;
			else
			if(horaex>600&&horaex<=1200)
				premio=200;
				else
				if(horaex>1200&&horaex<=1800)
					premio=300;
					else
					if(horaex>1800&&horaex<=2400)
						premio=400;
						else
						if(horaex>2400)
							premio=500;
		grat = (horaex) - (2/3*(falta));
		printf("gratificacao e :%2.f\n", grat);
		
				
		printf(" digite o numero de horas extras trabalhadas em minutos do proximo funcionario\n");
		scanf("%d",&horaex);
		
	}
}
