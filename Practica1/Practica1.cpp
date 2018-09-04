/*
   Hernández López Ángel Zait
   Algoritmos genéticos
   Primera practica: Histograma

   Compilación en terminal:
      g++ nombre.cpp -o nombre -lgraph

*/

#include <graphics.h> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
   int gd = DETECT,gm; // Variables necesarios para el uso de graphics
   int a[10]={10,2,8,15,30,29,45,1,5,4}; // Arreglo donde se encuentran los valores a graficar
   int i=0,pix=20,pix2=50,c[10],r,j,y;
   bool f=true; char da[5];

   srand(time(NULL)); // Semilla para realizar numeros aleatorios

   initgraph(&gd,&gm,NULL); // Inicio del ambiente grafico
   
   while(i<10) // Recorrera todos los valores del arreglo
   {  
      r=rand()%(16); // Generar numero aleatorio de 0 a 15
      for(j=0;j<i;j++)
      {
         if (r==c[j]) // Verifica si un color a sido repetido
            {f=false;break;}
         else
            {f=true;}
      }

      /*
         'y' es el largo de las barras, multiplicado por 10 y sumados 30
         para evitar conflicto en el pixel de inicio de la barra
      */

      y=(a[i]*10)+30;

      if(f) // Si el indicador es verdadero hara la barra
      {
         c[i]=r; // Guardamos el color
         sprintf(da,"%d",i+1); // Pasamos de un entero a un string
         outtextxy(10,(pix2-20),da); // Texto que contiene el dato 'n'
         setcolor(r); // Se le asigna el color a la barra
         bar(30,pix,y,pix2); // Se crea la barra
         setcolor(7); // Se le asigna un color al contorno de la barra (blanco)
         rectangle(30,pix,y,pix2); // Se crea el contorno de la barra
         sprintf(da,"%d",a[i]);
         outtextxy((y+10),(pix2-20),da); // Texto que contiene el valor del dato contenido en 'n'
         pix=pix2; pix2=pix+30; // Movimiento de pixeles
         i++; // Movimiento al siguiente valor del arreglo
      }
      else
         continue;
   }

   delay(15000); // Milisegundos que deja abierta la ventana del ambiente grafico
   closegraph(); // Fin del ambiente grafico
   return 0;
}