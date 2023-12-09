#include "wolfenstein.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592654
#define rayLength 100

ray createRay(t_data *data, Vec2 *vecStart, int angle)
{
  ray out;
  out.startPos = vecStart;
  //convert angle to radiant
  float angleRad = (angle * PI) / 180;
  
  //get map endPos
  intVec2 startMapPos;
  startMapPos = getMapPos(data, vecStart->x, vecStart->y);
  //setup unit step size
  intVec2 unitStepSize;
  //calculate unit step size
  unitStepSize.x = data->map->map_coord[startMapPos.x][startMapPos.y + 1][0] - data->map->map_coord[startMapPos.x][startMapPos.y][0];
  unitStepSize.y = data->map->map_coord[startMapPos.x + 1][startMapPos.y][1] - data->map->map_coord[startMapPos.x][startMapPos.y][1];
  
  intVec2 unitTop;
  unitTop.x = data->map->map_coord[startMapPos.x][startMapPos.y][0];
  unitTop.y = data->map->map_coord[startMapPos.x][startMapPos.y][1];

  intVec2 unitBottom;
  unitBottom.x = data->map->map_coord[startMapPos.x][startMapPos.y][2];
  unitBottom.y = data->map->map_coord[startMapPos.x][startMapPos.y][3];
 
  Vec2 r;

 

  //setup endpos
  Vec2 endPos;
  //if looking up
  if (angle < 0) {r.y = vecStart->y - unitTop.y; endPos.y = vecStart->y + (r.y * sin(angleRad));}
  //else
  else if (angle > 0) {r.y = unitBottom.y - vecStart->y;  endPos.y = vecStart->y + (r.y * sin(angleRad));}
  else if (angle == 0 || angle % 180 == 0) {r.y = 0; endPos.y = vecStart->y;}
  else {r.y = 0; endPos.y = 0;}
  //if looking left
  if (angle < - 90 || angle > 90) {r.x = vecStart->x - unitTop.x; endPos.x = vecStart->x + (r.x * cos(angleRad));}
  //else
  else if (angle > - 90 && angle < 90) {r.x = unitBottom.x - vecStart->x; endPos.x = vecStart->x + (r.x * cos(angleRad));}
  else if (angle % 90 == 0) {r.x = 0; endPos.x = vecStart->x;}
  else {r.x = 0; endPos.y = 0;}
  
  int dof = 0;

  //while (dof < 5)
  //{
    //Vec2 mapPosArr;
    //mapPosArr.x = data->map->map_coord[][][]
    //if (data->map->map[intr.x][intr.y] == 1)
    //{
      //dof = 5;
      //endPos = r;
    //}

    //dof += 1;
  //}

  out.endPos = &endPos;
  drawRay(data, &out, 0x0000FF00);
  
}

//draw ray
void drawRay(t_data *data, ray *myRay, int color)
{
  printf("start x = %f\n", myRay->startPos->x);
  printf("start y = %f\n", myRay->startPos->y);
  printf("end x = %f\n", myRay->endPos->x);
  printf("end y = %f\n", myRay->endPos->y);
 
  Vec2 *start = myRay->startPos;
  Vec2 *end = myRay->endPos;
  createLine(data, data->current_img, myRay->startPos->x, myRay->startPos->y, myRay->endPos->x, myRay->endPos->y, color);
}
