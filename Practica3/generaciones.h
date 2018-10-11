/*
	Hernández López Ángel Zait
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graficar.h"

int i,j,k;
int max=0;
float maxf=0,minf=0;
int m=0,n=0,gener=1; // Indicadores del arreglo de maximos y minimos
float sumProb=0,sumApt=0,promApt=0,promProb=0,*aprob; //Sumadores y promedio
int inds=0,alelo=5,gen;
int **a, **cruz;// Matriz para almacenar los individuos de formato bit, gray o entero
float *maxsel,*minsel; //Almacen de maximos y minimos
int *aent,*aapt; //Arreglos de los valores enteros de los individuos
int *selec, *punCruz; // Arrelo para almacenar a los padres seleccionado

void tablainicial(void);
void elemMax(void);
void elemMin(void);
void puntosCruza(void);

// Crea matrices dinamicas
void iniciar(void)
{
	aent=(int *)malloc(inds*sizeof(int));
	maxsel=(float *)malloc(31*sizeof(float));
	minsel=(float *)malloc(31*sizeof(float));
	aapt=(int *)malloc(inds*sizeof(int));
	aprob=(float *)malloc(inds*sizeof(float));
	cruz=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		cruz[i]=(int *)malloc(alelo*sizeof(int));
}

// Libera la memoria
void fin(void)
{
	free(aent); free(maxsel); free(minsel); free(aapt);
	free(aprob); free(cruz); free(selec); free(punCruz);
}

// Pasa cada uno de los individuos a sus numeros enteros
void pasaEntero(int **matriz)
{
	for(i=0;i<inds;i++)
	{
		aent[i]=0;
		for(j=alelo-1,k=0;k<alelo;j--,k++)
		{
			if(matriz[i][j])
				aent[i]=aent[i]+pow((matriz[i][j]*2),k);
			else
			aent[i]=aent[i]+0;
		}
	}
	i=0; j=0; k=0;	
}

// Calculos de la suma, promedio promedio de cada individuo
void operaciones(void)
{
	sumApt=0; sumProb=0; promApt=0; promProb=0;
	for(i=0;i<inds;i++)
	{
		aapt[i]=0;
		aapt[i]=pow(aent[i],2);
		sumApt=sumApt+aapt[i];
	}
	promApt=sumApt/inds;
	for(i=0;i<inds;i++)
	{
		aprob[i]=0;
		aprob[i]=aapt[i]/promApt;
		sumProb=sumProb+aprob[i];
	}
	promProb=sumProb/inds;
}

/*
	Se verifica si dos valores son iguales si es así,
	se vuelve a elegir otro numero
*/
int igualNum(int a)
{
	int b;

	srand(time(NULL));
	b=rand()%(alelo+1);
	if(a==b)
		b=igualNum(a);
	return b;
}

void mutacion(void)
{
	int cam1,cam2,dat,lau,porcen=(inds*.10),vez;
	// porcen representa la población que sera mutada

	srand(time(NULL));
	// Elije los individuos a mutar aleatoriamente
	for(vez=0;vez<inds;vez++)
	{
		// Cambio de dos bits
		lau=rand()%(inds+1);
		cam1=rand()%(alelo+1);
		cam2=igualNum(cam1);
	
		for(i=0;i<inds;i++)
			for(j=0;j<alelo;j++)
				a[i][j]=cruz[i][j];

		dat=a[lau][cam1];
		a[lau][cam1]=a[lau][cam2];
		a[lau][cam2]=dat;
	}

	pasaEntero(a);
	operaciones(); 
	elemMax();

	// Impresion de los valores de la población
	printf("\nNo.\tDescendencia\tMutacion\tValor x\t\tAptitud");
	k=0;
	for(i=0;i<inds;i++)
	{
		printf("\n%2d\t   ",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",cruz[i][j]);
		printf("\t");
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);
		printf("\t\t%4d\t\t%4d",aent[i],aapt[i]);
	}
	printf("\n\t\t\t\t\tSuma:\t\t%5.02f\n",sumApt);
	printf("\t\t\t\t\tPromedio:\t%5.02f\n",promApt);
	printf("\t\t\t\t\tMaximo:\t\t%4d\n",max);
	printf("\n");

	/*
		Si se han realizado las operaciones de las
		generaciones, entonces los grafica, si no
		realiza de nuevo la seleccion, cruza y 
		mutacion de los individuos
	*/
	if(gener<gen)
	{
		gener++;
		tablainicial();
	} 
	else
	{
		maxsel[m]=(float)max/promApt; // Guarda los valores maximos en un arreglo
		elemMin();
		minsel[n]=minf; // Guarda los valores minimos en un arreglo
		grafMaxMin2(maxsel,minsel,gen+1);
		fin();
	}
	
}

void CruzaPorPunto(void)
{
	int pos,pos1;
	//Inicio de proceso de cruza por un punto
	for(i=0,k=0;i<inds;i++)
	{
		for(j=0;j<alelo;j++)
		{
			if(j<=(punCruz[k]-1)) pos=selec[i];
			else
			{
				if(i%2==0 && i==2)	pos=selec[i+1];
				else		pos=selec[i-1];
			}
			cruz[i][j]=a[pos][j];
		}
		if(i%2==0 && i>1)	k++;
	}
	//Fin de proceso de curza

	pasaEntero(cruz);
	operaciones();
	elemMax();


	// Impresión de la población despues de la cruza
	printf("\nNo.\tCruza\tPunto de cruza\tDescendencia\tValor x\t\tAptitud");
	k=0;
	for(i=0;i<inds;i++)
	{
		printf("\n%2d\t",selec[i]+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[selec[i]][j]);
		printf("\t    %3d\t\t   ",punCruz[k]);
		for(j=0;j<alelo;j++)
			printf("%d",cruz[i][j]);
		if(i%2==1)
			k++;
		printf("\t%4d\t\t%4d",aent[i],aapt[i]);
	}
	printf("\n\t\t\t\t\t\tSuma:\t\t%5.02f\n",sumApt);
	printf("\t\t\t\t\t\tPromedio:\t%5.02f\n",promApt);
	printf("\t\t\t\t\t\tMaximo:\t\t%4d\n",max);
	
	mutacion();
}

void ruletaBool(void)
{
	int aux; float r,suau=0;

	selec=(int *)malloc(inds*sizeof(int));

	srand(time(NULL));

	// Inicio de la selección por ruleta
	for(i=0;i<inds;i++)
	{
		aux=rand()%(((int)sumProb*100)+1);
		r=(float)aux/100;
		for(j=0;j<inds;j++)
		{
			suau=suau+aprob[j];
			if(suau>r)
			{
				selec[i]=j; // Se guarda la posición del individuo seleccionado
				break;
			}
		}
		suau=0;
	}
	// Fin de la selección por ruleta

	CruzaPorPunto();
}

void tablainicial(void)
{
	// Imprime la nueva poblacion
	printf("\n\nGeneracion %d:",gener);

	operaciones();
	elemMax();
	elemMin();

	printf("\nNo.\tPoblacion\tValor x\t\tAptitud\t\tProbabilidad");
	for(i=0;i<inds;i++)
	{
		printf("\n%2d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);
		printf("\t\t%4d\t\t%4d\t\t%5.02f",aent[i],aapt[i],aprob[i]);
	}
	printf("\n\t\t\tSuma:\t\t%8.02f     %8.02f\n",sumApt,sumProb);
	printf("\t\t\tPromedio:\t%5.02f\t\t%5.02f\n",promApt,promProb);
	printf("\t\t\tMaximo:\t\t%4d\t\t%5.02f\n",max,maxf);
	maxsel[m]=maxf; m++; // Guarda el valor maximo en un arreglo
	minsel[n]=minf; n++; // Guarda el valor minimo en un arreglo
	ruletaBool();
}

void indiBool(void)		//Genera individuos de bits
{
	srand(time(NULL)); // Semilla para realizar numeros aleatorios

	for(i=0;i<inds;i++)	
	{
		for(j=0;j<alelo;j++)
			a[i][j]=rand()%(2); // Alelo aleatorio
	}
	i=0; j=0;
	iniciar();
	pasaEntero(a);
	tablainicial();
}

void iniciogeneraciones()
{
	fin(); // Libera la memoria

	// Se solicida el tamaño de la población
	printf("Tamanio de poblacion [0-32]: "); scanf("%d",&inds);

	punCruz=(int *)malloc(inds/2*sizeof(int));

	puntosCruza();

	// Se solicitan las generaciones a realizar
	printf("Numero de generaciones (maximo 15): "); scanf("%d",&gen);

	a=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		a[i]=(int *)malloc(alelo*sizeof(int));

	if(inds%2==0)
		indiBool(); //Llama a indiBool
	else
	{
		printf("El tamaño de poblacion debe de ser \'par\'\n\n\n");
		iniciogeneraciones();
	}
}

// Genera los putnos de curza al azar
void puntosCruza(void)
{
	srand(time(NULL));
	for(i=0;i<inds/2;i++)
		punCruz[i]=rand()%alelo+1;
}

// Busca el elemento mas grande del arreglo y los guarda
void elemMax(void)
{
	max=0;
	for(i=0;i<inds;i++)
		if(aapt[i]>max)
			max=aapt[i];
	maxf=(float)max/promApt;
}

// Busca el elemento mas grande del arreglo y los guarda
void elemMin(void)
{
	int min=max;
	for(i=0;i<inds;i++)
		if(aapt[i]<min)
			min=aapt[i];
	minf=(float)min/promApt;
}