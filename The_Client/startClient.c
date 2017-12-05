#include "controller.h"

int main(void)
{
	int res ;
	int attempts = 0 ;
	do
	{
		logAction("Attempting to connect");
		attempts++;
		sleep(2);
		res = initiateSocket();

	}while(res == -1 && attempts < MAX_ATTEMPTS);

	if(attempts < MAX_ATTEMPTS)
	{
		printMenu();
		readMenu();

	}
	else
	{
		logError("Unable to connect");
	}
	return 0;
}
