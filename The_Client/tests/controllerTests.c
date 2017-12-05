//controllerTests.c

#include <stdlib.h>
#include <stdio.h>
#include "expressions.h"
#include "controller.h"

/*
* 1) test if fillOccupiedMatrix is working fine
*/
/*Function to Test*/
//void fillOcuppiedMatrix(char ** occupiedSeats , int ** totalOccupied);
/*Function To Test*/
void testFillOccupiedMatrix();
char ** givenOccupiedArray();
void whenWeCreateTheOccupiedMatrix(char ** occupiedSeats , int ** totalOccupied);
void thenTheMatrixIsCorrect();

void controllerTests()
{
	testFillOccupiedMatrix();
}

void testFillOccupiedMatrix()
{
	char ** occupiedSeats = NULL;
	int  ** totalOccupied = malloc(3 * sizeof(int *));
	for(int i = 0 ; i < 3 ; i++){
		totalOccupied[i] = calloc(3 , sizeof (int) ) ;
	}

	occupiedSeats = givenOccupiedArray();
	whenWeCreateTheOccupiedMatrix(occupiedSeats , totalOccupied);
	thenTheMatrixIsCorrect(totalOccupied);

	for(int i = 0 ; i < 3 ; i++){
		free(totalOccupied[i]);
	}
	free(totalOccupied);
	free(occupiedSeats);



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

void whenWeCreateTheOccupiedMatrix(char ** occupiedSeats , int ** totalOccupied)
{
	fillOcuppiedMatrix(occupiedSeats , totalOccupied);
}

void thenTheMatrixIsCorrect(int  ** totalOccupied)
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