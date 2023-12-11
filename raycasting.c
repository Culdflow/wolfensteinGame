#include "wolfenstein.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592654
#define rayLength 100

ray createRay(t_data *data, Vec2 *vecStart, int angle)
{
  
  printf("angle = %d\n", angle);

  //create ray output
  ray out;
  out.startPos = vecStart;

  //create unit step
  Vec2 unitStep;
  unitStep.x = data->map->map_coord[0][0][2] - data->map->map_coord[0][0][0]; 
  unitStep.y = data->map->map_coord[0][0][3] - data->map->map_coord[0][0][1];  

  //create dof depth of field
  int dof = 3;

  //convert angle to rad
  float angleRad = (angle * PI) / 180; 

  //first intersection
  Vec2 inter1;

  //get map position for player position
  intVec2 playerMapPos = getMapPos(data, (int)vecStart->x, (int)vecStart->y);
  if (angle < 0) inter1.y = data->map->map_coord[playerMapPos.x][playerMapPos.y][1] - 1;
  else if (angle > 0)inter1.y = data->map->map_coord[playerMapPos.x][playerMapPos.y][3] + 1;
  else inter1.y = vecStart->y; 

  
  //setup x pos 
  inter1.x = vecStart->x + (vecStart->y - inter1.y) / tan(-angleRad);
  
  //setup vec map pos position of inter1 in map
  intVec2 vecMapPos;

  //setup error
  intVec2 ERROR;
  ERROR.x = 0;
  ERROR.y = 0;

  for (int i = 0;i < dof; i++)
  {
    //find pos in map
    vecMapPos = getMapPos(data,(int)inter1.x,(int)inter1.y);
    //if pos not in map
    if (vecMapPos.x = -1) {printf("ERROR ray end pos not in map\n"); break;}
    
    if (data->map->map[vecMapPos.x][vecMapPos.y] == 1)
      i = dof;

    if (angle < 0) {inter1.y -= unitStep.y; inter1.x += unitStep.y/tan(-angleRad);}
    else if (angle > 0) {inter1.y += unitStep.y; inter1.x += unitStep.y/tan(-angleRad);}
    if (inter1.x > 1000) inter1.x = 1000;
    if (inter1.y > 1000) inter1.y = 1000;
    if (inter1.x < 0) inter1.x = 0;
    if (inter1.y < 0) inter1.y = 0;



 
  }


  out.endPos = &inter1;
  drawRay(data, &out, 0x00FF00FF);
}

//draw ray
void drawRay(t_data *data, ray *myRay, int color)
{
 
  Vec2 *start = myRay->startPos;
  Vec2 *end = myRay->endPos;
  createLine(data, data->current_img, myRay->startPos->x, myRay->startPos->y, myRay->endPos->x, myRay->endPos->y, color);
}
