/*
	Hernández López Ángel Zait
*/

#include "permutacion.h"

int main ()
{
	system("clear");
	inicioPermutacion();
	OrderCrossover();
	//PartiallyMapppedCrossover();
	PositionBasedCrossover();
	OrderBasedCrossover();
	//CycleCrossover();
	imprDescen();
	printf("\n\nHernández López Ángel Zait\n\n");

	return 0;
}