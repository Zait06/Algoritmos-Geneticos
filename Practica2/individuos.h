/*
	Hernández López Ángel Zait
	Practica 2: Individuos
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tgmath.h>

int i,j; //Contadores

void indiBool(void)		//Genera individuos de bits
{
	unsigned short int a[10][10];
	srand(time(NULL)); // Semilla para realizar numeros aleatorios

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			a[i][j]=rand()%(2); //Alelo aleatorio
	}

	for(i=0;i<10;i++)
	{
		printf("\nIndividuo %2d: ",i+1);
		for(j=0;j<10;j++)
			printf("%d ",a[i][j]); //Alelo aleatorio
	}
	printf("\n");
}

void indiGray(void)		//Genera indivudos con codigo Gray
{
	unsigned short int a[10][10],ap[10][10],r;
	srand(time(NULL)); // Semilla para realizar numeros aleatorios


	// Individuos binario
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			a[i][j]=rand()%(2); //Alelo aleatorio
	}


	for(i=0;i<10;i++)
	{
		printf("\nIndividuo %3d: ",i+1);
		for(j=0;j<10;j++)
			printf("%d ",a[i][j]); //Alelo aleatorio
	}
	printf("\n");

	//Individuos gray
	for(i=0;i<10;i++)
	{
		for(j=9;j>0;j--)
		{
			if(a[i][j-1]!=a[i][j])
				ap[i][j]=1;
			else 
				ap[i][j]=0;
		}
		ap[i][0]=a[i][0];
	}

	for(i=0;i<10;i++)
	{
		printf("\nIndividuo %2d\': ",i+1);
		for(j=0;j<10;j++)
			printf("%d ",ap[i][j]); //Alelo aleatorio
	}
	printf("\n");
}

void indiReal(void)		//Genera indivuduos de tipo flotante
{
	float a[10][10],r;
	srand(time(NULL)); // Semilla para realizar numeros aleatorios

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			r=rand()%(1000); //Alelo aleatorio
			a[i][j]=r/100;
		}
	}

	for(i=0;i<10;i++)
	{
		printf("\nIndividuo %2d: ",i+1);
		for(j=0;j<10;j++)
			printf("%5.02f ",a[i][j]);
	}
	printf("\n");
}

void indiEnte(void)		//Genera indivudios de tipo entero
{
	int a[10][10];
	srand(time(NULL)); // Semilla para realizar numeros aleatorios

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			a[i][j]=rand()%(100); //Alelo aleatorio
	}

	for(i=0;i<10;i++)
	{
		printf("\nIndividuo %2d: ",i+1);
		for(j=0;j<10;j++)
			printf("%4d ",a[i][j]); //Alelo aleatorio
	}
	printf("\n");
}