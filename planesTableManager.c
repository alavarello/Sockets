#include "structs.h"
#include "constants.h"
#include "planesTableManager.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern sqlite3 *db;

void printPlaneArray(tPlaneArray planeArray){
  int i;
  printf("PLANE SIZE: %d\n",planeArray.size );
  for(i=0; i< planeArray.size; i++){
    printf("%s\n",planeArray.planeArray[i]->model ); 
    printf("Rows:%d R:%d M:%d L:%d\n",planeArray.planeArray[i]->rows,planeArray.planeArray[i]->right,planeArray.planeArray[i]->middle,planeArray.planeArray[i]->left); 
  }
}

int getNumberOfPlanes(){
  int rc, numberOfPlanes;
  sqlite3_stmt *res;
  //getting the number of flights
    char * sqlPlaneCount = "SELECT count(*) FROM planes";
    rc = sqlite3_prepare_v2(db, sqlPlaneCount, -1, &res, 0);
    sqlite3_step(res);
    numberOfPlanes = sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    return numberOfPlanes;
}

tPlane** expandPlaneArray(tPlane** planeArray, long size){
  int i;
  planeArray = malloc(size*sizeof(tPlane*));
  for(i=0; i<size; i++){
    planeArray[i] = malloc(sizeof(tPlane));
    planeArray[i]->model = malloc(sizeof(char)*MODEL_CHAR_MAX);
  }
  return planeArray;
}


tPlaneArray * getPlaneArray(){
  char *err_msg = 0;
  sqlite3_stmt * res;
  tPlane** planeArray = NULL;
  tPlaneArray* planeArrayStruct; 
  int rc, numberOfPlanes, i;

  //ESTO tiene que ser atomico;
    numberOfPlanes = getNumberOfPlanes();

    //getting the planes
    char *sql = "SELECT * FROM planes";
       
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    //------------------
    planeArray = expandPlaneArray(planeArray, numberOfPlanes);
    i = 0;
    while(sqlite3_step(res) == SQLITE_ROW){
      strcpy(planeArray[i]->model,(char*)sqlite3_column_text(res, MODEL_COLUMN));
      planeArray[i]->rows = sqlite3_column_int(res, ROWS_COLUMN);
      planeArray[i]->right = sqlite3_column_int(res, RIGHT_COLUMN);
      planeArray[i]->middle = sqlite3_column_int(res, MIDDLE_COLUMN);
      planeArray[i]->left = sqlite3_column_int(res, LEFT_COLUMN);
      i++; 
    }
    sqlite3_finalize(res);
    planeArrayStruct = malloc(sizeof(tPlaneArray));
    planeArrayStruct->planeArray = planeArray;
    planeArrayStruct->size = numberOfPlanes;
    return planeArrayStruct;
}


int insert_plane(char * model, int rows, int left, int middle, int right)
{

  char * sql = "INSERT INTO PLANES VALUES(?,?,?,?,?);";
  sqlite3_stmt * res;
  int rc;
  char * err_msg;

  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  if(rc != SQLITE_OK)
  {
    return ERROR;
  }

  sqlite3_bind_text(res, 1, model, -1, NULL);
  sqlite3_bind_int(res, 2, rows);
  sqlite3_bind_int(res, 3, left);
  sqlite3_bind_int(res, 4, middle);
  sqlite3_bind_int(res, 5, right);

  rc = sqlite3_step(res);

  if(rc != SQLITE_DONE)
  {
    printf("An error has occured\n");
    return ERROR;
  }

  sqlite3_finalize(res);

  return OK;

}
