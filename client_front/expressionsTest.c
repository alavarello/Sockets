//expressionsTest
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
prototypes of functions to be tested*/
int isNumber(char c);

int isAlpha(char c);

int isValidSeatExpression(char * seat);

//int checkSeatNumberFormat(char * seat , tFlight *  currentFlight);

int getColumn(char * seat);

int getNumber(char * seat);

/* Beginning of tests*/

int mainTestExpressions()
{
	isNumberTest();
	isAlphaTest();
}

void isNumberTest()
{
	int i;
	int length ;
	char * test = "a1b2c3d4e5f6g7h8i9j0";

	length = strlen(test);

	for(i = 0; i < length; i++){
		if(i%2 == 0){
			if(isNumber(test[i])){
				printf("Error in isNumber\n");
				return;
			}
		}else{
			if(!isNumber(test[i])){
				printf("Error in isNumber\n");
				return;
			}
		}
	}

	printf("isNumber test successfull\n");

}

void isAlphaTest()
{
	int i;
	int length ;
	char * test = "a1b2c3d4e5f6g7h8i9j0";

	length = strlen(test);

	for(i = 0; i < length; i++){
		if(i%2 == 1){
			if(isAlpha(test[i])){
				printf("Error in isAlpha\n");
				return;
			}
		}else{
			if(!isAlpha(test[i])){
				printf("Error in isAlpha\n");
				return;
			}
		}
	}

	printf("isAlpha test successfull\n");

}