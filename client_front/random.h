#include <time.h>
#ifndef  ALEATORIO
	#define ALEATORIO
	double randNormalize(void); /*Obtiene un numero real entre 0 y 1*/
	int randInt (int izq, int der); /*Obtiene un numero aleatorio entero entre izq y der*/
	double randReal (double izq, double der); /*Obtiene un numero aleatorio real entre izq y der*/
	void randomize (void); /*Inicializa la semilla*/
#endif

