#include "structs.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char * serialize_plane(tPlane * t)
{
  int bytes = 0;
  char * buff, * aux;


  bytes = (MODEL_CHAR_MAX*sizeof(char) + 4*sizeof(int));

  buff = malloc(bytes);
  aux = buff;

  memcpy(aux, t->model, MODEL_CHAR_MAX);
  aux += MODEL_CHAR_MAX;

  memcpy(aux, &(t->rows), sizeof(t->rows));
  aux += sizeof(t->rows);

  memcpy(aux, &(t->left), sizeof(t->left));
  aux += sizeof(t->left);

  memcpy(aux, &(t->middle), sizeof(t->middle));
  aux += sizeof(t->middle);

  memcpy(aux, t->right, sizeof(t->right));
  aux += sizeof(t->right);

  return buff;

}

tPlane * deserialize_plane(char * buff)
{

  tPlane * res = malloc(sizeof(tPlane));

  res->model = malloc(MODEL_CHAR_MAX*sizeof(char));
  memcpy(res->model, buff, MODEL_CHAR_MAX);
  buff += MODEL_CHAR_MAX;

  res->rows = malloc(sizeof(res->rows));
  memcpy(res->rows, buff, sizeof(res->rows));
  buff += sizeof(res->rows);

  res->left = malloc(sizeof(res->left));
  memcpy(res->left, buff, sizeof(res->left));
  buff += sizeof(res->left);

  res->middle = malloc(sizeof(sizeof(res->middle)));
  memcpy(res->middle, buff, sizeof(res->middle));
  buff += sizeof(res->middle);

  res->right = malloc(sizeof(sizeof(res->right)));
  memcpy(res->right, buff, sizeof(res->right));
  buff += sizeof(res->right);

  return res;

}


char * serialize_plane_array(tPlaneArray * planeArray)
{
  int bytes = 0, i;
  char * buff, * aux, *plane;


  bytes = (MODEL_CHAR_MAX*sizeof(char) + 4*sizeof(int));

  buff = malloc(planeArray->size*bytes + sizeof(long));
  aux = buff;
  memcpy(aux, &(planeArray->size), sizeof(long));
  aux += sizeof(long);

  for(i = 0; i < planeArray->size; i++) {

    plane = serialize_plane(planeArray->planeArray[i]);
    memcpy(aux, plane, bytes);
    free(plane);
    aux += bytes;
  }
  return buff;

}

tPlaneArray * deserialize_plane_array(char * buff)
{
  int i;
  int bytes;

  tPlaneArray * res = malloc(sizeof(tPlaneArray));
  memcpy(&(res->size), buff, sizeof(res->size));
  buff += sizeof(res->size);

  bytes = (MODEL_CHAR_MAX*sizeof(char) + 4*sizeof(int));


  res->planeArray = malloc(res->size*sizeof(tPlane*));

  for(i = 0; i < res->size; i++)
  {
    res->planeArray[i] = deserialize_plane(buff);
    buff += bytes;
  }
  return res;
}
