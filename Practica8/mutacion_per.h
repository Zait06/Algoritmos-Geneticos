/*
	Permutacion
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int i,j,k;
int inds=0,alelo=0;
int **a,**cruz;// Matriz para almacenar los individuos de formato bit, gray o entero
int **inser,**dezp,**intrec,**heu;
int *numeros,*punCruz;

void insersion(void);
void dezplazamiento(void);
void intercambio(void);
void heuristico(void);
void imprDescen(void);

void iniciar(void)
{
	a=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		a[i]=(int *)malloc(alelo*sizeof(int));

	cruz=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		cruz[i]=(int *)malloc(alelo*sizeof(int));

	inser=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		inser[i]=(int *)malloc(alelo*sizeof(int));

	dezp=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		dezp[i]=(int *)malloc(alelo*sizeof(int));

	intrec=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		intrec[i]=(int *)malloc(alelo*sizeof(int));

	heu=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		heu[i]=(int *)malloc(alelo*sizeof(int));
}

void fin(void)
{
	free(a);	free(cruz);
	free(heu);
}

void indiEnte(void)		//Genera indivudios de tipo entero
{
	int lz,f;
	srand(time(NULL)); // Semilla para realizar numeros aleatorios

	for(i=0;i<inds;i++)
	{
		j=0;
		while(j<alelo)
		{
			lz=rand()%(alelo); //Alelo aleatorio
			if(j>0)
			{	
				// Verificación de que ningun alelo se repita
				for(k=0;k<j;k++)
				{
					if(lz!=a[i][k])
						{f=1;}
					else
						{f=0; break;}
				}
			}
			else
				{f=1;}

			if(f==1)
			{
				// Guarda el alelo
				a[i][j]=lz;
				j++;
			}
		}
	}
}

void inicioMutaPer(void)
{
	fin();

	// Se solicida el tamaño de la población
	printf("\nTamanio de poblacion: "); scanf("%d",&inds);

	// Se solicitan el numero de alelos
	printf("Numero de alelos: "); scanf("%d",&alelo);

	if((inds%2)!=0)
	{
		printf("La población debe ser numero par.\n");
		getchar();
		system("clear");
		inicioMutaPer();
	}
	else
	{
		iniciar();
		indiEnte();
	}
}

void insersion(void)
{
	int num1,num2,aux;

	srand(time(NULL));	

	for(i=0;i<inds;i++)
	{
		num1=rand()%(alelo); 
		num2=rand()%(alelo);
		if(num2<num1)
		{
			aux=num2;
			num2=num1;
			num1=aux;
		}

		for(j=0;j<alelo;j++)
		{
			if(j>num1 && j<=num2)
				{inser[i][j]=a[i][j-1];}
			else if(j==num1)
				{inser[i][j]=a[i][num2];}
			else
				{inser[i][j]=a[i][j];}
		}
	}
}

void dezplazamiento(void)
{
	int *numeros,cant=0,aux;
	int num1,num2,flag;
	numeros=(int *)malloc(alelo*sizeof(int *));

	srand(time(NULL));

	cant=alelo/4;

	for(i=0;i<inds;i++)
	{	
		for(j=0;j<(cant*2);j++)
			numeros[i]=rand()%(alelo);

		// Ordenamiento de posiciones
		for(j=1;j<(cant*2);j++)
		{
			for(k=0;k<(cant*2)-1;k++)
			{
				if(numeros[k]>numeros[k+1])
				{
					aux=numeros[k+1];
					numeros[k+1]=numeros[k];
					numeros[k]=aux;
				}
			}
		}

		for(j=0,k=0;j<alelo;j++)
		{
			if(j>numeros[k] && j<=numeros[k+1])
				{dezp[i][j]=a[i][j-1];}
			else if(j==numeros[k])
				{dezp[i][j]=a[i][numeros[k+1]];}
			else
				{dezp[i][j]=a[i][j];}
			
			if(j==numeros[k+1])
				{k++;}
		}
	}
}

void intercambio(void)
{
	int num1,num2;

	srand(time(NULL));

	for(i=0;i<inds;i++)
		for(j=0;j<alelo;j++)
			intrec[i][j]=a[i][j];

	for(i=0;i<inds;i++) // Acomoda los alelos a mutar
	{
		num1=rand()%(alelo); 
		num2=rand()%(alelo);
		intrec[i][num1]=a[i][num2];
		intrec[i][num2]=a[i][num1];	
	}
}

void heuristico(void)
{
	int *numeros,cant;
	int num1,num2,flag;
	numeros=(int *)malloc(inds*sizeof(int *));

	srand(time(NULL));

	cant=rand()%(alelo);

	/*
		Si los alelos a seleccionar no son un numero par
		se vuelve a crear otro numero
	*/

	if(cant%2==0)
	{
		for(i=0;i<inds;i++)
			for(j=0;j<alelo;j++)
				heu[i][j]=a[i][j];

		i=0;
		while(i<cant)
		{
			num1=rand()%(alelo);
			if(i!=0)
			{
				for(j=0;j<i;j++) // Busca que no se repitan posiciones
				{
					if(num1==numeros[j])
						{flag=0; break;}
					else
						{flag=1;}
				}
				if(flag==1)
				{
					numeros[i]=num1;
					i++;
				}
			}
			else
			{
				numeros[i]=num1;
				i++;
			}
		}

		for(i=0;i<cant;i++)
		{
			for (j=0;j<cant;j=j+2)	// Acomoda los alelos a mutar
			{
				num1=numeros[j];
				num2=numeros[j+1];
				heu[i][num1]=a[i][num2];
				heu[i][num2]=a[i][num1];
			}
		}
	}
	else
		{heuristico();}
}

void imprDescen(void)
{
	printf("Insersión:\n");
	printf("No.\t  Padres\t\bDescendencia\n");
	for(i=0;i<inds;i++)
	{
		printf("%3d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);

		printf("\t");
		for(j=0;j<alelo;j++)
			printf("%d",inser[i][j]);

		printf("\n");
	}

	printf("\n\nDezplazamiento:\n");
	printf("No.\t  Padres\t\bDescendencia\n");
	for(i=0;i<inds;i++)
	{
		printf("%3d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);

		printf("\t");
		for(j=0;j<alelo;j++)
			printf("%d",dezp[i][j]);

		printf("\n");
	}

	printf("\n\nIntercambio reciproco:\n");
	printf("No.\t  Padres\t\bDescendencia\n");
	for(i=0;i<inds;i++)
	{
		printf("%3d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);

		printf("\t");
		for(j=0;j<alelo;j++)
			printf("%d",intrec[i][j]);

		printf("\n");
	}

	printf("\n\nHeuristico:\n");
	printf("No.\t  Padres\t\bDescendencia\n");
	for(i=0;i<inds;i++)
	{
		printf("%3d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);

		printf("\t");
		for(j=0;j<alelo;j++)
			printf("%d",heu[i][j]);

		printf("\n");
	}
}