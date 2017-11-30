//expressions.c

#include "expressions.h"

int isNumber(char c)
{
	if( c <= '9' && c>= '0'){
		return 1;
	}

	return 0;
}

int isAlpha(char c)
{
	if( c <= 'Z' && c>= 'A'){
		return 1;
	}

	return 0;
}

int isValidSeatExpression(char * seat)
{	

	char c1 = seat[0];
	char c2 = seat[1];
	char c3 = seat[2];

	if(isNumber(c1) && isNumber(c2) && isAlpha(c3) && seat[3] == 0){
		return 1;
	}else{
		return 0;
	}

}

int checkSeatNumberFormat(char * seat , tFlight *  currentFlight)
{
	int row = getNumber(seat);
	int column = getColumn(seat);

	tPlane * plane = getPlane(currentFlight);

	if(row <= 0  || row >= plane->rows + 1){
		return 0;
	}

	if(column < 0 || column >= (plane->left + plane->middle + plane->right)){
		return 0;
	}

	return 1;



}

int getColumn(char * seat){

	char c3 = seat[2];

	return c3 - 'A';

}

int getNumber(char * seat){

	char c1 = seat[0];
	char c2 = seat[1];

	int a = c1 - '0';
	int b = c2 - '0';

	return a*10 + b;

}