/*
	Hernández López Ángel Zait
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int i,j,k;
int inds=0,alelo=5,gen;
int **a, **cruz;// Matriz para almacenar los individuos de formato bit, gray o entero
int *selec, *punCruz; // Arrelo para almacenar a los padres seleccionado

void puntosCruza(int numCru);
void CruzaPorPunto(void);
void CruzaPorDosPuntos(void);
void CruzaUniforme(void);
void CruzaAcentuada(void);
void inicioCruza(void);
void tablainicial(void);

// Crea matrices dinamicas
void iniciar(void)
{
	a=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		a[i]=(int *)malloc(alelo*sizeof(int));
	cruz=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		cruz[i]=(int *)malloc(alelo*sizeof(int));
}

// Libera la memoria
void fin(void)
{
	free(cruz);
	free(selec);	free(punCruz);
}
/*
	Se verifica si dos valores son iguales si es así,
	se vuelve a elegir otro numero
*/

void indiBool(void)		//Genera individuos de bits
{
	srand(time(NULL)); // Semilla para realizar numeros aleatorios

	for(i=0;i<inds;i++)	
	{
		for(j=0;j<alelo;j++)
			a[i][j]=rand()%(2); // Alelo aleatorio
	}
	i=0; j=0;
}

void inicioCruza(void)
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
		inicioCruza();
	}
	else
	{
		iniciar();
		indiBool();
		tablainicial();
	}
}

// Genera los putnos de curza al azar
void puntosCruza(int numCru)
{
	srand(time(NULL));
	for(i=0;i<numCru;i++)
		punCruz[i]=rand()%alelo;
}

void CruzaPorPunto(void)
{
	int pos;
	punCruz=(int *)malloc((alelo/2)*sizeof(int));

	puntosCruza(alelo/2);

	//Inicio de proceso de cruza por un punto
	for(i=0,k=0;i<inds;i=i+2,k++)
	{
		for(j=0;j<punCruz[k];j++)
		{
			cruz[i][j]=a[i][j];
			cruz[i+1][j]=a[i+1][j];
		}
		for(j;j<alelo;j++)
		{
			cruz[i][j]=a[i+1][j];
			cruz[i+1][j]=a[i][j];
		}
	}
	//Fin de proceso de cruza

	printf("\n\nCruza por un punto.");
	printf("\nNo.\tCruza\t\tPunto de cruza\t Descendencia");
	k=0;
	for(i=0;i<inds;i++)
	{
		printf("\n%2d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);
		printf("\t    %3d\t\t   ",punCruz[k]);
		for(j=0;j<alelo;j++)
			printf("%d",cruz[i][j]);
		
		if(i%2!=0)
			k++;
	}
}



void CruzaPorDosPuntos(void)
{
	int pos1,pos2;
	int pap1,pap2;

	punCruz=(int *)malloc(alelo*sizeof(int));

	puntosCruza(alelo);

	//Inicio de proceso de cruza por dos punto
	for(i=0,k=0;i<inds;i=i+2,k=k+2)
	{
		if(punCruz[k]<punCruz[k+1])
			{pos1=punCruz[k]; pos2=punCruz[k+1];}
		else
			{pos2=punCruz[k]; pos1=punCruz[k+1];}

		pap1=i; pap2=i+1;

		for(j=0;j<pos1;j++)
		{
			cruz[i][j]=a[pap1][j];
			cruz[i+1][j]=a[pap2][j];
		}
		for(j;j<pos2;j++)
		{
			cruz[i][j]=a[pap2][j];
			cruz[i+1][j]=a[pap1][j];
		}
		for(j;j<alelo;j++)
		{
			cruz[i][j]=a[pap1][j];
			cruz[i+1][j]=a[pap2][j];
		}

	}
	//Fin de proceso de cruza

	// Impresión de la población despues de la cruza
	printf("\n\nCruza por dos puntos.");
	printf("\nNo.\tCruza\t\tPunto de cruza\t Descendencia");
	k=0;
	for(i=0;i<inds;i++)
	{
		printf("\n%2d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);
		printf("\t    %3d\t\t   ",punCruz[i]);
		for(j=0;j<alelo;j++)
			printf("%d",cruz[i][j]);
	}
}

void CruzaUniforme(void)
{
	int ele1,ele2;

	//Inicio de proceso de cruza uniforme
	srand(time(NULL));
	for(i=0;i<inds;i=i+2)
	{
		ele1=i;
		ele2=i+1;

		j=0;
		while(j<alelo)
		{
			if(rand()%(2)==1)
			{
				cruz[i][j]=a[ele1][j];
				cruz[i+1][j]=a[ele2][j];
			}
			else
			{
				cruz[i][j]=a[ele2][j];
				cruz[i+1][j]=a[ele1][j];
			}
			j++;
		}
	}
	//Fin de proceso de cruza

	// Impresión de la población despues de la cruza
	printf("\n\nCruza uniforme.");
	printf("\nNo.\t  Cruza\t\tDescendencia");
	k=0;
	for(i=0;i<inds;i++)
	{
		printf("\n%2d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);
		printf("\t");
		for(j=0;j<alelo;j++)
			printf("%d",cruz[i][j]);
	}
}

void CruzaAcentuada(void)
{
	int inte[2];
	int el1,el2,aux;

	//Inicio de proceso de cruza uniforme
	srand(time(NULL));
	for(i=0;i<inds;i=i+2)
	{
		el1=i;
		el2=i+1;

		for(j=0;j<2;j++)
			inte[j]=rand()%(alelo);

		if(inte[0]>inte[1])
		{
			aux=inte[0];
			inte[0]=inte[1];
			inte[1]=aux;
		}

		for(j=0;j<inte[0];j++)
		{
			cruz[i][j]=a[el1][j];
			cruz[i+1][j]=a[el2][j];
		}
		for(j;j<inte[1];j++)
		{
			cruz[i][j]=a[el2][j];
			cruz[i+1][j]=a[el1][j];
		}
		for(j;j<alelo;j++)
		{
			cruz[i][j]=a[el1][j];
			cruz[i+1][j]=a[el2][j];
		}
	}
	//Fin de proceso de cruza

	// Impresión de la población despues de la cruza
	printf("\n\nCruza acentuada.");
	printf("\nNo.\t  Cruza\t\tDescendencia");
	k=0;
	for(i=0;i<inds;i++)
	{
		printf("\n%2d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);
		printf("\t");
		for(j=0;j<alelo;j++)
			printf("%d",cruz[i][j]);
	}
}

void tablainicial(void)
{
	system("clear");
	printf("Población inicial.");
	printf("\nNo.\tIndividuo");
	k=0;
	for(i=0;i<inds;i++)
	{
		printf("\n%2d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);
	}
}