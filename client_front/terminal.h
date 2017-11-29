#ifndef FRONT_H
	#define FRONT_H




#define ERROR -1
#define OK 0
#define CLEAN_BUFFER while(getchar()!='\n')
#define MAX_BUFFER 80
#define GRANDE 2
#define CHICA 1
#define APAG 0
#define PREND 1
#define ERRNOM -2
#define SI 1
#define NO 0
#define PREFIJO 5
#define QUIT 5
#define SAVE 6
#define MAX_BUFFER 80

typedef struct {
	int fil;
	int col;
}tpos;
typedef struct{
	tpos ini;
	tpos fin;
}tmov;
typedef struct {
	int dimMax;
	int dim;
	tmov * vector;
}tvec;

typedef struct {
	tpos inicial;
	tpos final;
	char turno; /* 'A'o 'Z'*/
	int fichas[2]; /* en la posicion 0 estan las fichas de A y en la posicion 1 las fichas de Z*/
	int maquina;

} tjugada;
typedef struct {
	int fils;
	int cols;
	char **matriz;
} tdim;

#endif