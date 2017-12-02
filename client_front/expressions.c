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
	if( toupper(c) <= 'Z' && toupper(c)>= 'A'){
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

int getColumn(char * seat)
{

	char c3 = seat[2];

	return c3 - 'A';

}

int getNumber(char * seat)
{

	char c1 = seat[0];
	char c2 = seat[1];

	int a = c1 - '0';
	int b = c2 - '0';

	return a*10 + b;

}

int isValidFlightAndPlaneCodeExpression(char * thing){

	if(isAlpha(thing[0]) && isAlpha(thing[1]) && isNumber(thing[2]) && isNumber(thing[3]) && isNumber(thing[4]) && thing[5] == 0)
		return 1;

	return 0;
}

int isValidOriginDestination(char * place){

	if(isAlpha(place[0]) && isAlpha(place[1]) && isAlpha(place[2]) && place[3] == 0)
		return 1;

	return 0;
}

int isValidTime(char * time){

	if(isValidTimeHour(time[0], time[1]) && time[2] == ':' && isValidTimeMinutes(time[3], time[4]) && time[5] == 0)
		return 1;

	return 0;
}

int isValidTimeHour (char n1, char n2){
	
	int i1 = n1 - '0';
	int i2 = n2 - '0';

	if(!isNumber(n1) || !isNumber(n2))
		return 0;

	if(i1 == 0 || i1 == 1)
		return 1;

	if(i1 == 2 && i2 < 5)
		return 1; 

	return 0;
}

int isValidTimeMinutes(char n1, char n2){

	int i1 = n1 - '0';

	if(!isNumber(n1) || !isNumber(n2))
		return 0;

	if(i1 > 5)
		return 0;

	return 1;
}

int isValidDate(char * date){

	int y = isValidYear(date[6], date[7], date[8], date[9]);

	if(y == 0)
		return 0;

	if(date[2] == '/' && isValidDayAndMonth(date[0], date[1], date[3], date[4], y) && date[5] == '/' && date[10] == 0)
		return 1;

	return 0;
}

int isValidDayAndMonth(char d1, char d2, char m1, char m2, int y){

	int d;
	int m;

	if(!isNumber(d1) || !isNumber(d2) || !isNumber(m1) || !isNumber(m2))
		return 0;

	d = ((d1 - '0') * 10) + (d2 - '0');
	m = ((m1 - '0') * 10) + (m2 - '0');

	if(d > 31 || m > 12)
		return 0;

	if(y == 2017 && d < 5 && m <= 12)
		return 0;

	if(m == 4 || m == 6 || m == 9 || m == 11){
		if(d == 31)
			return 0;

		return 1;
	}

	if(m == 2 && d > 28)
		return 0;

	return 1;
}

int isValidYear(char y1, char y2, char y3, char y4){
	
	int y;

	if(!isNumber(y1) || !isNumber(y2) || !isNumber(y3) || !isNumber(y4))
		return 0;

	y = ((y1 - '0') * 1000) + ((y2 - '0') * 100) + ((y3 - '0') * 10) + (y4 - '0');

	if(y < 2017)
		return 0;

	return y;
}

int checkLogicalTimeDifference(char * timeDeparture, char * timeArrival, char * dateDeparture, char * dateArrival){

	int d = dateDiff(dateArrival, dateDeparture);
	int t;

	if(d < 0)
		return 0;

	t = timeDiff(timeArrival, timeDeparture);

	if(d == 0 && t <= 0)
		return 0;

	return 1;
}

int dateDiff(char * big, char * small){

	int m1, m2, m, d1, d2, d;

	int y1 = ((big[6] - '0') * 1000) + ((big[7] - '0') * 100) + ((big[8] - '0') * 10) + (big[9] - '0');
	int y2 = ((small[6] - '0') * 1000) + ((small[7] - '0') * 100) + ((small[8] - '0') * 10) + (small[9] - '0');

	int y = y1 - y2;

	if(y != 0)
		return y;

	m1 = ((big[3] - '0') * 10) + (big[4] - '0');
	m2 = ((small[3] - '0') * 10) + (small[4] - '0');

	m = m1 - m2;

	if(m != 0)
		return m;

	d1 = ((big[0] - '0') * 10) + (big[1] - '0');
	d2 = ((small[0] - '0') * 10) + (small[1] - '0');

	d = d1 - d2;

	return d;
}

int timeDiff(char * big, char * small){

	int m1, m2, m;

	int	h1 = ((big[0] - '0') * 10) + (big[1] - '0');
	int h2 = ((small[0] - '0') * 10) + (small[1] - '0');

	int h = h1 - h2;

	if(h != 0)
		return h;

	m1 = ((big[3] - '0') * 10) + (big[4] - '0');
	m2 = ((small[3] - '0') * 10) + (small[4] - '0');

	m = m1 - m2;

	return m;
}





