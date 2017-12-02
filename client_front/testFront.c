//testFront.c

#include <stdlib.h>
#include <stdio.h>
#include "expressions.h"

/*
*This archive will have tests for functions in the model part of the front,
*Visual functions like the plane drawing have been tested by watching the 
*program run in different situations
*/

/*
* 1) test if fillOccupiedMatrix is working fine
*/
/*Function to Test*/
void fillOcuppiedMatrix2(char ** occupiedSeats , int totalOccupied[3][3]);
/*Function To Test*/
void testFillOccupiedMatrix();
char ** givenOccupiedArray();
void whenWeCreateTheOccupiedMatrix(char ** occupiedSeats , int totalOccupied[3][3]);
void thenTheMatrixIsCorrect();

int mainTestFront()
{
	testFillOccupiedMatrix();
	return 1;
}

void fillOcuppiedMatrix2(char * * occupiedSeats , int totalOccupied[3][3])
{
	int i = 0;
	int number;
	int column;

	while(occupiedSeats[i] != NULL)
	{
		number = getNumber(occupiedSeats[i]); 
		column = getColumn(occupiedSeats[i]);
		totalOccupied[number-1][column] = 1;


		i++;
	}


}

void testFillOccupiedMatrix()
{
	char ** occupiedSeats;
	int totalOccupied[3][3] = {{0,0,0} , {0,0,0} , {0,0,0} };

	occupiedSeats = givenOccupiedArray();
	whenWeCreateTheOccupiedMatrix(occupiedSeats , totalOccupied);
	thenTheMatrixIsCorrect(totalOccupied);



}

char ** givenOccupiedArray()
{
	char ** seats = malloc(4 * sizeof(*seats));

	seats[0] = "01B";
	seats[1] = "02A";
	seats[2] = "03C";
	seats[3] = NULL;

	return seats;
}

void whenWeCreateTheOccupiedMatrix(char ** occupiedSeats , int  totalOccupied[3][3])
{
	fillOcuppiedMatrix2(occupiedSeats , totalOccupied);
}

void thenTheMatrixIsCorrect(int totalOccupied[3][3])
{
	int a = totalOccupied[0][1];
	int b = totalOccupied[1][0];
	int c = totalOccupied[2][2];
	int d = totalOccupied[0][2];

	if(a != 1 || b != 1 || c != 1 || d != 0){
		printf("fillOccupiedMatrix test failed\n");
	}else{
		printf("fillOccupiedMatrix test succesfull\n");
	}

}

/*
*end test 1
*/