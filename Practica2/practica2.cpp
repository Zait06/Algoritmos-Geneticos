/*
	Hernández López Ángel Zait
	Practica 2: Individuos
*/

#include "individuos.h"

int main()
{
	int op;

	printf("Generar individuo de tipo\n");
	printf("1. Binario\n2. Código Gray\n3. Reales\n4. Enteros\nOpcion: ");
	scanf("%d",&op);
	switch(op)
	{
		case 1:
			printf("\n\t\tIndividuo Binario"); indiBool();
		break;
		case 2:
			printf("\n\t\tIndividuo Codigo Gray"); indiGray();
		break;
		case 3:
			printf("\n\t\tIndividuo Real Flotante"); indiReal();
		break;
		case 4:
			printf("\n\t\tIndividuo Real Entero"); indiEnte();
		break;
		default:
			printf("\nOpcion no valida. Intente de nuevo\n\n");
		break;
	}
	
	return 0;
}