//expressionsTest
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
prototypes of functions to be tested*/
int isNumber(char c);

int isAlpha(char c);

int isValidSeatExpression(char * seat);

int checkLogicalTimeDifference(char * timeDeparture, char * timeArrival, char * dateDeparture, char * dateArrival);

/* we consider as valid dates those since the due day of the assignment*/
int isValidDate(char * date);

//int checkSeatNumberFormat(char * seat , tFlight *  currentFlight);

int getColumn(char * seat);

int getNumber(char * seat);

/*prototypes of tests*/
void isNumberTest();
void isAlphaTest();
void testValidExpDates();

/* Beginning of tests*/

int mainTestExpressions()
{
	isNumberTest();
	isAlphaTest();
	testValidExpDates();

	return 1;
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

void printResults(char * s){
	if(isValidDate(s))
		printf("\n%s is a valid date\n", s);
	else
		printf("\n%s is an invalid date\n", s);
}

void printResultsLogicalTime(char * departureDate, char * arrivalDate, char * departureT, char * arrivalT){
	if(checkLogicalTimeDifference(departureT, arrivalT, departureDate, arrivalDate))
		printf("\nLogical time difference with %s as departure day, %s as arrival day, %s as departure time and %s as arrival time\n", departureDate, arrivalDate, departureT, arrivalT);
	else
		printf("\nIllogical time difference with %s as departure day, %s as arrival day, %s as departure time and %s as arrival time\n", departureDate, arrivalDate, departureT, arrivalT);
}

void testValidExpDates(){
	char * valid = "03/02/2018";
	char * valid2 = "02/01/2018";

	char * time = "00:00";

	char * invalid = "04/12/2017";
	char * invalid2 = "00/00/0000";
	char * invalid3 = "1/1/2018";

	printResults(valid);
	printResults(valid2);
	printResults(invalid);
	printResults(invalid2);
	printResults(invalid3);

	printResultsLogicalTime(valid, valid2, time, time);
	printResultsLogicalTime(valid2, valid, time, time);
}
