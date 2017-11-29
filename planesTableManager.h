//planesTableManager.h

#ifndef PLANESTABLEMANAGER_H
#define PLANESTABLEMANAGER_H
#include "structs.h"

void printPlaneArray(tPlaneArray planeArray);
int getNumberOfPlanes();
tPlane** expandPlaneArray(tPlane** planeArray, long size);
tPlaneArray * getPlaneArray();
int insert_plane(char * model, int rows, int left, int middle, int right);

#endif