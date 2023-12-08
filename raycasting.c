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
  //setup endpos
  Vec2 endPos;
  printf("angle = %d\n", angle);
  //if looking up
  if (angle < 0 && angle) endPos.y = vecStart->y + (rayLength * sin(angleRad));
  //else
  else if (angle > 0) endPos.y = vecStart->y + (rayLength * sin(angleRad));
  else if (angle == 0 || angle % 180 == 0) endPos.y = vecStart->y;
  else endPos.y = 0;
  //if looking left
  if (angle < - 90 || angle > 90) endPos.x = vecStart->x + (rayLength * cos(angleRad));
  //else
  else if (angle > - 90 && angle < 90) endPos.x = vecStart->x + (rayLength * cos(angleRad));
  else if (angle % 90 == 0)endPos.x = vecStart->x;
  else endPos.y = 0;

  out.endPos = &endPos;
  printf("out start x = %f\n", out.startPos->x);
  printf("out start y = %f\n", out.startPos->y);
  printf("out end x = %f\n", out.endPos->x);
  printf("out end y = %f\n", out.endPos->y);
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
