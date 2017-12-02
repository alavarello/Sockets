#ifndef SERIALIZE_PLANE_H
#define SERIALIZE_PLANE_H
#include "structs.h"

char * serialize_plane(tPlane * t);
tPlane * deserialize_plane(char * buff);
char * serialize_plane_array(tPlaneArray * planeArray);
tPlaneArray * deserialize_plane_array(char * buff);

#endif
