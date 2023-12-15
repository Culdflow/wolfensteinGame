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
  Vec2 interY;
  Vec2 interX;

  //get y map position for player position
  intVec2 playerMapPos = getMapPos(data, (int)vecStart->x, (int)vecStart->y);

  //setup interY wich checks for collisions on y
  if (angle < 0) {interY.y = data->map->map_coord[playerMapPos.x][playerMapPos.y][1]-1; interY.x = vecStart->x - abs(vecStart->y - interY.y) / tan(angleRad);}
  else if (angle > 0) {interY.y = data->map->map_coord[playerMapPos.x][playerMapPos.y][3]+1; interY.x = vecStart->x + abs(vecStart->y - interY.y) / tan(angleRad);}
  else interY.y = vecStart->y; 

  //get interX wich checks for collisions on x00FF00FF
  if (angle > - 90 && angle < 90) {interX.x = data->map->map_coord[playerMapPos.x][playerMapPos.y][2]+1; interX.y = vecStart->y - abs(vecStart->x - interX.x) / tan(angleRad);}
  else if (angle < - 90 || angle > 90) {interX.x = data->map->map_coord[playerMapPos.x][playerMapPos.y][0]-1; interX.y = vecStart->y + abs(vecStart->x - interX.x) / tan(angleRad);}
  else interX.x = vecStart->x;
  //setup x pos
  interX.y = vecStart->x - abs(vecStart->x - interX.x) / tan(angleRad);
  interY.x = vecStart->y - abs(vecStart->y - interY.y) / tan(angleRad);
  
  //setup vec map pos position of interY in map
  intVec2 vecMapPosY;
  intVec2 vecMapPosX;
  
  //setup error
  intVec2 ERROR;
  ERROR.x = 0;
  ERROR.y = 0;

  Vec2 lengthX;
  lengthX.x = abs(interX.x - vecStart->x);
  lengthX.y = abs(interX.y - vecStart->y);

  Vec2 lengthY;
  lengthY.x = abs(interY.x - vecStart->x);
  lengthY.y = abs(interY.y - vecStart->y);

  Vec2 hyp;
  hyp.x = sqrt(pow(lengthX.x,2) + pow(lengthX.y,2));
  hyp.y = sqrt(pow(lengthY.x,2) + pow(lengthY.y,2));

  for (int i = 0;i < dof; i++)
  {
    
    //find pos in map
    vecMapPosY = getMapPos(data, (int)interY.y, (int)interY.x);
    vecMapPosX = getMapPos(data, (int)interX.y, (int)interX.x);
    //if pos not in map
    if (vecMapPosY.x == -1) {printf("ERROR vecMapPosY ray end pos not in map\n"); vecMapPosY = ERROR;}
    if (vecMapPosX.x == -1) {printf("ERROR vecMapPosX ray end pos not in map\n"); vecMapPosX = ERROR;}
    if (data->map->map[vecMapPosY.y][vecMapPosY.x] == 1) {i = dof; printf("found wall in y\n");}
    if (data->map->map[vecMapPosX.y][vecMapPosX.x] == 1) {i = dof; printf("found wall in x\n");}
    if (hyp.y < hyp.x)
    {
      if (angle < 0) 
      {
        interY.y -= unitStep.y;
        interY.x -= unitStep.y/tan(angleRad);   
      }
      else if (angle > 0) 
      {
        interY.y += unitStep.y;
        interY.x += unitStep.y/tan(angleRad);
      }
    }
    else 
    {
      if (angle > - 90 && angle < 90)
      {
        interX.x += unitStep.x;
        interX.y += unitStep.x*tan(angleRad);
      }
      else if (angle < - 90 || angle > 90)
      {
        interX.x -= unitStep.x;
        interX.y -= unitStep.x*tan(angleRad);
      }

    }

  }



  out.endPos = &interY;
  drawRay(data, &out, 0x00FF00FF);
}

//draw ray
void drawRay(t_data *data, ray *myRay, int color)
{
 
  Vec2 *start = myRay->startPos;
  Vec2 *end = myRay->endPos;
  createLine(data, data->current_img, myRay->startPos->x, myRay->startPos->y, myRay->endPos->x, myRay->endPos->y, color);
}
