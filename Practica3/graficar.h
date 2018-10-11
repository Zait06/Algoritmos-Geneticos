/*
	Hernández López Ángel Zait
*/

#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define base 450

char da[16];
int ma=0,p=0;
float maf=0.0;
int gd = DETECT,gm; // Variables necesarios para el uso de graphics
int pix=0,pix2=0,y=0,y2=0;

void taby(void)
{
	strcpy(da,"0.00");
  	outtextxy(2,base-5,da);
	sprintf(da,"%.02f",maf); // Pasamos de un flotante a un string
  	outtextxy(2,base-ma-5,da);
  	sprintf(da,"%.02f",maf/2); // Pasamos de un flotante a un string
  	outtextxy(2,base-(ma/2)-5,da);
  	sprintf(da,"%.02f",maf/4); // Pasamos de un flotante a un string
  	outtextxy(2,base-(ma/4)-5,da);
  	sprintf(da,"%.02f",3*maf/4); // Pasamos de un flotante a un string
  	outtextxy(2,base-(3*ma/4)-5,da);
  	sprintf(da,"%.02f",maf/8); // Pasamos de un flotante a un string
  	outtextxy(2,base-(ma/8)-5,da);
  	sprintf(da,"%.02f",3*maf/8); // Pasamos de un flotante a un string
  	outtextxy(2,base-(3*ma/8)-5,da);
  	sprintf(da,"%.02f",5*maf/8); // Pasamos de un flotante a un string
  	outtextxy(2,base-(5*ma/8)-5,da);
  	sprintf(da,"%.02f",7*maf/8); // Pasamos de un flotante a un string
  	outtextxy(2,base-(7*ma/8)-5,da);
}

void valores(float *f,float *g, int h)
{
	// Tabla de valores
	pix=150;
	strcpy(da,"Gen");
	outtextxy(475,130,da);
	strcpy(da,"Max");
	outtextxy(515,130,da);
	strcpy(da,"Min");
	outtextxy(560,130,da);
	for(p=0;p<h;p++)
	{
		sprintf(da,"%d",p);
		outtextxy(480,pix,da); // Numero de generacion
		sprintf(da,"%.02f",f[p]);
		outtextxy(520,pix,da); // Valor maximo
		sprintf(da,"%.02f",g[p]);
		outtextxy(560,pix,da); // Valor minimo
		pix=pix+10;
	}
}

void colorVal(void)
{
	setcolor(4); // Color para el valor maximo
  	bar(450,20,470,40);
  	setcolor(7);
  	rectangle(450,20,470,40);
  	strcpy(da,"Valores maximos");
  	outtextxy(475,30,da);

  	setcolor(1);
  	bar(450,60,470,80);
  	setcolor(7); // Color para el valor minimo
  	rectangle(450,60,470,80);
  	strcpy(da,"Valores minimos");
  	outtextxy(475,70,da);
}

void grafMaxMin(float *a,float *b,int cant)
{
  	pix=20;pix2=45;y=0;y2=0;
  	int j=0;
  	int lau[cant]; int ang[cant];

  	printf("\n\n");

  	// Conversión de flotante a real
  	for(p=0;p<cant;p++)
  	{
 		lau[p]=a[p]*100;
 		ang[p]=b[p]*100;
  	}

  	initgraph(&gd,&gm,NULL); // Inicio del ambiente grafico
  	p=0;
  	while(p<cant) // Recorrera todos los valores del arreglo
  	{
	    y=lau[p]+30;
	    y2=ang[p]+30;
    	if(j<y)
      		j=y;
    	sprintf(da,"%d",p); // Pasamos de un entero a un string
    	outtextxy(10,pix2-15,da); // Texto que contiene el dato 'n' numero de generacion
    	setcolor(4); // Se le asigna el color a la barra (rojo)
    	bar(30,pix,y,pix2); // Se crea la barra con el valor máximo en esa generacion
    	setcolor(7); // Se le asigna un color al contorno del rectangulo (blanco)
    	rectangle(30,pix,y,pix2); // Contorno de la barra
    	setcolor(1); //Color para la barra (azul)
    	bar(30,pix,y2,pix2); // Barra con el valo minimo en esa generacion
    	setcolor(7); // Se le asigna un color al contorno del rectangulo (blanco)
    	rectangle(30,pix,y2,pix2);
    	pix=pix2; pix2=pix+25; // Movimiento de pixeles
    	p++; // Movimiento al siguiente valor del arreglo
  	}
  	
  	colorVal(); // Colores asignados a los valores con su significado
  	valores(a,b,cant); // Impresion de los valores maixmos y minimos

  	delay(15000); // Milisegundos que deja abierta la ventana del ambiente grafico
  	closegraph(); // Fin del ambiente grafico
}

void grafMaxMin2(float *a,float *b,int cant)
{
  	int pix=30,pix2=55,y=0,y2=0;
  	int lau[cant]; int ang[cant];
  	int yp=0,yp2=0; 

  	printf("\n\n");

  	//Conversion de flotante a entero
  	for(p=0;p<cant;p++)
  	{
 		lau[p]=a[p]*100;
 		ang[p]=b[p]*100;
 		if(maf<a[p])
    		maf=a[p];
  	}

  	initgraph(&gd,&gm,NULL); // Inicio del ambiente grafico
  	p=0;
  	while(p<cant-1) // Recorrera todos los valores del arreglo
  	{
    	y=lau[p]; // punto 1 max
    	yp=lau[p+1]; // punto 2 max
    	y2=ang[p]; // punto 1 min
    	yp2=ang[p+1]; // punto 2 min
    	if(ma<y)
	    	ma=y;
	    sprintf(da,"%d",p); // Pasamos de un entero a un string
	    outtextxy(pix,460,da); // Texto que contiene el dato 'n' numero de generacion
	    setcolor(1); //Color para la barra (azul)
	    line(pix,base-y2,pix2,base-yp2); // Linea del valor actual al siguiente
	    setcolor(4); // Se le asigna el color a la barra (rojo)
	    line(pix,base-y,pix2,base-yp); // Se crea una linea del valor actual al siguiente
	    pix=pix2; pix2=pix+25; // Movimiento de pixeles
	    p++; // Movimiento al siguiente valor del arreglo
  	}

  	sprintf(da,"%d",p); // Pasamos de un entero a un string
  	outtextxy(pix,460,da); // Texto que contiene el dato 'n' numero de generacion

  	colorVal(); // Colores asignados a las lineas con significado

  	// Se crea un recuadro para la grafica
  	setcolor(7);
  	rectangle(30,base-ma,pix,450);

  	taby(); // Impresion de valores en el eje vertical
  	valores(a,b,cant); // Impresion de los valores maximos y minimos

  	delay(15000); // Milisegundos que deja abierta la ventana del ambiente grafico
  	closegraph(); // Fin del ambiente grafico
}