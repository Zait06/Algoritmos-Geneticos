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
int **ox,**pmx,**pbc,**obc,**cx;
int *selec,*punCruz; // Arrelo para almacenar a los padres seleccionado

void OrderCrossover(void);
void PartiallyMapppedCrossover(void);
void PositionBasedCrossover(void);
void OrderBasedCrossover(void);
void CycleCrossover(void);

void iniciar(void)
{
	a=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		a[i]=(int *)malloc(alelo*sizeof(int));

	cruz=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		cruz[i]=(int *)malloc(alelo*sizeof(int));

	ox=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		ox[i]=(int *)malloc(alelo*sizeof(int));

	pmx=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		pmx[i]=(int *)malloc(alelo*sizeof(int));

	pbc=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		pbc[i]=(int *)malloc(alelo*sizeof(int));

	obc=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		obc[i]=(int *)malloc(alelo*sizeof(int));

	cx=(int **)malloc(inds*sizeof(int *));
	for(i=0;i<inds;i++)
		cx[i]=(int *)malloc(alelo*sizeof(int));
}

void fin(void)
{
	free(a);	free(cruz);
	free(ox);	free(pmx);
	free(pbc);	free(obc);
	free(cx);
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

void inicioPermutacion(void)
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
		inicioPermutacion();
	}
	else
	{
		iniciar();
		indiEnte();
	}
}

void OrderCrossover(void)
{
	int start,final,aux;
	int *pos;
	int dat[2][alelo], otdat[2][alelo];
	int ques=0,l=0,m=0;
	pos=(int *)malloc(alelo*sizeof(int));

	srand(time(NULL)); // Semilla para realizar numeros aleatorios

	for(i=0;i<inds;i++)
		for(j=0;j<alelo;j++)
			ox[i][j]=-5;

	for(i=0;i<inds;i=i+2)
	{
		start=rand()%(alelo-1);
		final=rand()%(alelo-1);

		if(start>final)
		{
			aux=start;
			start=final;
			final=aux;
		}

		for(j=start,k=0;j<=final;j++,k++)
		{
			ox[i][j]=a[i][j];
			ox[i+1][j]=a[i+1][j];
			dat[0][k]=a[i][j];
			dat[1][k]=a[i+1][j];
		}

		aux=k;
		l=0;m=0;

		for(j=0;j<alelo;j++)
		{
			// Hijo 1
			for(k=0;k<aux;k++)
			{
				if(dat[0][k]==a[i+1][j])
					{ques=0;break;}
				else
					{ques=1;}
			}
			if(ques==1)
			{
				otdat[0][l]=a[i+1][j];
				l++;
			}

			// Hijo 2
			for(k=0;k<aux;k++)
			{
				if(dat[1][k]==a[i][j])
					{ques=0;break;}
				else
					{ques=1;}
			}
			if(ques==1)
			{
				otdat[1][m]=a[i][j];
				m++;
			}
		}

		k=0;l=0;j=0;
		while(j<alelo)
		{
			if(ox[i][j]==-5)
			{
				ox[i][j]=otdat[0][k];
				k++;
			}

			if(ox[i+1][j]==-5)
			{
				ox[i+1][j]=otdat[1][l];
				l++;
			}

			j++;
		}
	}
}

void PartiallyMapppedCrossover(void)
{
	int start,final,aux;
	int *pos;
	int dat[2][alelo], otdat[2][alelo];
	int ques=0,l=0,m=0;
	pos=(int *)malloc(alelo*sizeof(int));

	srand(time(NULL)); // Semilla para realizar numeros aleatorios

	for(i=0;i<inds;i=i+2)
	{
		start=rand()%(alelo-1);
		final=rand()%(alelo-1);

		if(start>final)
		{
			aux=start;
			start=final;
			final=aux;
		}

		for(j=0;j<start;j++)
		{
			pmx[i][j]=-5;
			pmx[i+1][j]=-5;
		}
		
		for(j=start,k=0;j<final;j++,k++)
		{
			pmx[i][j]=a[i+1][j];
			dat[0][k]=a[i+1][j];
			pmx[i+1][j]=a[i][j];
			dat[1][k]=a[i][j];
		}

		aux=k;

		for(j=final;j<alelo;j++)
		{
			pmx[i][j]=-5;
			pmx[i+1][j]=-5;
		}

		l=0;m=0;
		for(j=0,k=0;j<alelo;j++,k++)
		{
			if(l<aux)
			{
				if(dat[0][l]==a[i][j])
				{
					otdat[0][l]=a[i][j];
					j=0;l++;
				}
			}

			if(m<aux)
			{
				if(dat[1][m]==a[i+1][k])
				{
					otdat[1][m]=a[i][k];
					k=0;m++;
				}
			}
		}

		l=0;m=0;j=0;
		while(j<alelo)
		{
			if(pmx[i][j]==-5)
			{
				pmx[i][j]=otdat[0][l];
				l++;
			}

			if(pmx[i+1][j]==-5)
			{
				pmx[i+1][j]=otdat[1][m];
				m++;
			}

			j++;
		}
	}
}

void PositionBasedCrossover(void)
{
	int start,final,aux,cant;
	int *pos;
	int dat[2][alelo], otdat[2][alelo];
	int ques=0,l=0,m=0;
	pos=(int *)malloc(alelo*sizeof(int));

	srand(time(NULL)); // Semilla para realizar numeros aleatorios

	for(i=0;i<inds;i++)
		for(j=0;j<alelo;j++)
			pbc[i][j]=-5;

	cant=rand()%(alelo);

	for(i=0;i<inds;i=i+2)
	{	
		for(j=0;j<cant;j++)
		{
			// Posición del dato elegido
			start=rand()%(alelo);
			pbc[i][start]=a[i][start];
			dat[0][j]=a[i][start];

			final=rand()%(alelo);
			pbc[i+1][final]=a[i+1][final];
			dat[1][j]=a[i+1][final];
		}

		aux=cant;
		l=0;m=0;

		for(j=0;j<alelo;j++)
		{
			// Hijo 1
			for(k=0;k<aux;k++)
			{
				if(dat[0][k]==a[i+1][j])
					{ques=0;break;}
				else
					{ques=1;}
			}
			if(ques==1)
			{
				otdat[0][l]=a[i+1][j];
				l++;
			}

			// Hijo 2
			for(k=0;k<aux;k++)
			{
				if(dat[1][k]==a[i][j])
					{ques=0;break;}
				else
					{ques=1;}
			}
			if(ques==1)
			{
				otdat[1][m]=a[i][j];
				m++;
			}
		}

		k=0;l=0;j=0;
		while(j<alelo)
		{
			if(pbc[i][j]==-5)
			{
				pbc[i][j]=otdat[0][k];
				k++;
			}

			if(pbc[i+1][j]==-5)
			{
				pbc[i+1][j]=otdat[1][l];
				l++;
			}

			j++;
		}
	}
}

void OrderBasedCrossover(void)
{
	int aux,aux1,cant;
	int *pos;
	int dat[2][alelo], otdat[2][alelo];
	int ques=0,l=0,m=0;
	pos=(int *)malloc(alelo*sizeof(int));

	srand(time(NULL)); // Semilla para realizar numeros aleatorios

	cant=rand()%(alelo);

	int start[cant];
	int final[cant];

	for(i=0;i<cant;i++)
	{
		start[i]=rand()%(alelo);
		final[i]=rand()%(alelo);
	}

	for(i=0;i<inds;i=i+2)
	{	

		for(j=0;j<alelo;j++)
		{
			obc[i][j]=a[i+1][j];
			obc[i+1][j]=a[i][j];
		}

		l=0; m=0; aux=0; aux1=0;
		for(j=0,k=0;j<alelo;j++,k++)
		{
			if(l<cant)
			{
				if(obc[i][j]==start[l])
				{
					obc[i][j]=-5; l++;
					dat[0][aux]=a[i+1][j];
					j=0; aux++;
				}
			}

			if(m<cant)
			{
				if(obc[i+1][k]==final[m])
				{
					obc[i+1][k]=-5; m++;
					dat[1][aux1]=a[i][k];
					k=0; aux1++;
				}
			}
		}

		k=0;l=0;j=0;
		while(j<alelo)
		{
			if(obc[i][j]==-5)
			{
				obc[i][j]=dat[0][k];
				k++;
			}

			if(obc[i+1][j]==-5)
			{
				obc[i+1][j]=dat[1][l];
				l++;
			}

			j++;
		}
	}	
}

void CycleCrossover(void)
{
	int aux,aux1,cant;
	int dat[2][alelo], otdat[2][alelo];
	int ques=0,l=0,m=0;

	srand(time(NULL)); // Semilla para realizar numeros aleatorios

	int pos[alelo];
	int valores[alelo];

	for(i=0;i<inds;i=i+2)
	{
		for(j=0;j<alelo;j++)
		{
			pos[j]=-5;
			valores[j]=-5;
		}

		pos[0]=0;
		valores[0]=a[i][0];
		valores[1]=a[i+1][0];
		k=0; l=1; m=0;
			
	}
}

void imprDescen(void)
{
	printf("Order Crossover:\n");
	printf("No.\t  Padres\t\bDescendencia\n");
	for(i=0;i<inds;i++)
	{
		printf("%3d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);

		printf("\t");
		for(j=0;j<alelo;j++)
			printf("%d",ox[i][j]);

		printf("\n");
	}

	printf("\n\nPosition Based Crossover:\n");
	printf("No.\t  Padres\t\bDescendencia\n");
	for(i=0;i<inds;i++)
	{
		printf("%3d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);

		printf("\t");
		for(j=0;j<alelo;j++)
			printf("%d",pbc[i][j]);

		printf("\n");
	}

	printf("\n\nOrder Based Crossover:\n");
	printf("No.\t  Padres\t\bDescendencia\n");
	for(i=0;i<inds;i++)
	{
		printf("%3d\t",i+1);
		for(j=0;j<alelo;j++)
			printf("%d",a[i][j]);

		printf("\t");
		for(j=0;j<alelo;j++)
			printf("%d",obc[i][j]);

		printf("\n");
	}
}
