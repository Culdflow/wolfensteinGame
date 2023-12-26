#include "wolfenstein.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592654
#define maxRayLength 350

ray createRay(t_data *data, Vec2 *vecStart, int angle)
{
  printf("angle = %d\n", angle);

  //create ray output
  ray out;
  out.startPos = vecStart;

  //setup ray error
  ray rayERROR;
  Vec2 ERRstart;
  ERRstart.x = 50;
  ERRstart.y = 50;
  Vec2 ERRend;
  ERRend.x = 950;
  ERRend.y = 50;
  rayERROR.startPos = &ERRstart;
  rayERROR.endPos = &ERRend;

  //setup Vec error
  intVec2 ERROR;
  ERROR.x = 0;
  ERROR.y = 0;

  //create unit step
  Vec2 unitStep;
  unitStep.x = data->map->map_coord[0][0][2] - data->map->map_coord[0][0][0]; 
  unitStep.y = data->map->map_coord[0][0][3] - data->map->map_coord[0][0][1];  

  //create dof depth of field
  int dof = 2;

  //convert angle to rad
  float angleRad = (abs(angle) * PI) / 180; 

  //first intersection
  Vec2 interY;
  Vec2 interX;

  //get y map position for player position
  printf("getting map position from start position...\n");
  intVec2 playerMapPos = getMapPos(data, (int)vecStart->x, (int)vecStart->y);
  printf("done\n");


  if (playerMapPos.x == -1) return rayERROR;

//----------------------SETUP BASE RAYCAST VALUES---------------------------------------------------------------------

  //setup interY wich checks for collisions on y
  printf("setting up interY...\n");
  if (angle < 0) {interY.y = data->map->map_coord[playerMapPos.x][playerMapPos.y][1];}
  else if (angle > 0) {interY.y = data->map->map_coord[playerMapPos.x][playerMapPos.y][3];}
  else interY.y = vecStart->y; 
  printf("done\n");


  //get interX wich checks for collisions on X
  printf("setting up interX....\n");
  if (angle > - 90 && angle < 90) {interX.x = data->map->map_coord[playerMapPos.x][playerMapPos.y][2];}
  else if (angle < - 90 || angle > 90) {interX.x = data->map->map_coord[playerMapPos.x][playerMapPos.y][0];}
  else interX.x = vecStart->x;
  printf("done\n");
  
  //setup x pos
  printf("setting up y pos for interX...\n");
  if (angle < 0) interX.y = vecStart->y + (vecStart->x - interX.x) * tan(angleRad);
  else interX.y = vecStart->y - (vecStart->x - interX.x) * tan(angleRad);
  printf("done\n");
  printf("setting up x pos for interY...\n");
  interY.x = vecStart->x + abs(vecStart->y - interY.y) / tan(angleRad);
  printf("done\n");

//----------------------------------------------------------------------------------------------------------------------

  //setup vec map pos position of interY in map
  intVec2 vecMapPosY;
  intVec2 vecMapPosX;

  Vec2 lengthX;
  lengthX.x = abs(interX.x - vecStart->x);
  lengthX.y = abs(interX.y - vecStart->y);

  Vec2 lengthY;
  lengthY.x = abs(interY.x - vecStart->x);
  lengthY.y = abs(interY.y - vecStart->y);
  
  Vec2 hyp;
  hyp.x = abs(sqrt(pow(lengthX.x + lengthX.y,2)));
  hyp.y = abs(sqrt(pow(lengthY.x + lengthY.y,2)));

  Vec2 ogHyp;
  ogHyp.x = hyp.x;
  ogHyp.y = hyp.y;
  
  //if found wall == 1 found wall in x if found wall == 2 found wall in y
  int foundWall = 0;

//---------------------------------------------LOOP----------------------------------------------------------------------
  printf("going into loop...\n");
  for (int i = 0;i < dof; i++)
  {
    
    //find pos in map
    printf("finding interX and interY pos in map...\n");
    
    printf("interY.y = %f\n", interY.y);
    printf("interY.x = %f\n", interY.x);
    printf("interX.y = %f\n", interX.y);
    printf("interX.x = %f\n", interX.x);
    
    vecMapPosY = getMapPos(data, (int)interY.y, (int)interY.x);
    vecMapPosX = getMapPos(data, (int)interX.y, (int)interX.x);
    printf("done\n");

    //if pos not in map
    printf("returning error if pos not in map..\n");
    if (vecMapPosY.x == -1) {printf("interY x = %d  ", (int)interY.x); printf("interY y = %d\n", (int)interY.y); /*return rayERROR;*/}
    if (vecMapPosX.x == -1) {printf("interX x = %d  ", (int)interX.x); printf("interX y = %d\n", (int)interX.y); /*return rayERROR;*/}
    printf("NO ERROR\n");

    //IF HIT WALL
    printf("checking if ray hit wall...\n");
    if (data->map->map[vecMapPosY.y][vecMapPosY.x] == 1) 
    {
      if (foundWall != 2) foundWall += 2; 
      printf("found wall in y\n"); 
      printf("map pos Y = %d\n", vecMapPosY.y); 
      printf("map pos X = %d\n", vecMapPosY.x);
    }

    if (data->map->map[vecMapPosX.y][vecMapPosX.x] == 1) 
    {
      if (foundWall != 1) foundWall += 1; 
      printf("found wall in x\n"); 
      printf("map pos Y = %d\n", vecMapPosX.y); 
      printf("map pos X = %d\n", vecMapPosX.x);
    }

    printf("done\n");

    lengthX.x = abs(interX.x - vecStart->x);
    lengthX.y = abs(interX.y - vecStart->y);

    lengthY.x = abs(interY.x - vecStart->x);
    lengthY.y = abs(interY.y - vecStart->y);

    printf("hypX = %f\n", hyp.x);
    printf("hypY = %f\n", hyp.y);
    printf("foundWall == %d\n", foundWall);
    if (foundWall < 2)
    {
      printf("checking if looking up...\n");
      if (angle < 0) 
      {
        printf("LOOKING UP\n");
        printf("updating interY value...\n");
        interY.y -= unitStep.y;
        interY.x += unitStep.y/tan(angleRad);
        printf("done\n");
      }
      else if (angle > 0) 
      {
        printf("LOOKING DOWN\n");
        printf("updating interY value...\n");
        interY.y += unitStep.y;
        interY.x += unitStep.y/tan(angleRad);
        printf("done\n");
      }
      hyp.y = abs(sqrt(pow(lengthY.x + lengthY.y,2)));

    }
    if (foundWall < 1 || foundWall == 2)
    {

      printf("CHECKING IF LOOKING RIGHT\n");
      if (angle > - 90 && angle < 90)
      {
        printf("LOOKING RIGHT\n");
        printf("updating interX value...\n");
        interX.x += unitStep.x;
        if (angle < 0) interX.y -= unitStep.y * tan(angleRad);
        else interX.y += unitStep.y * tan(angleRad);
        printf("done\n");
      }
      else if (angle < - 90 || angle > 90)
      {
        printf("LOOKING LEFT\n");
        printf("updating interX value...\n");
        interX.x -= unitStep.x;
        if (angle < 0) interX.y += unitStep.y * tan(angleRad);
        else interX.y -= unitStep.y * tan(angleRad);
        printf("done\n");
      }
      hyp.x = abs(sqrt(pow(lengthX.x + lengthX.y,2)));

    }

         
  }
  
//-------------------------------------------------------------------------------------------------------------------------------------

  //set ray out dependant on wich ray is shorter
  if (foundWall == 2 && hyp.y < ((dof - 1) * unitStep.y + ogHyp.y)) out.endPos = &interY;
  else if (foundWall == 1 && hyp.x < ((dof - 1) * unitStep.x + ogHyp.x)) out.endPos = &interX;
  else 
  {
    if (hyp.y < hyp.x) out.endPos = &interY;
    else out.endPos = &interX;
  }
  
  //check limits
  if (out.endPos->x > data->sizeX) out.endPos->x = data->sizeX;
  if (out.endPos->x < 0) out.endPos->x = 0;
  if (out.endPos->y > data->sizeY) out.endPos->y = data->sizeY;
  if (out.endPos->y < 0) out.endPos->y = 0;

  //----------------DEBUGGING-------------------
  printf("angle = %d\n", angle);
  printf("startPos X = %f\n", vecStart->x);
  printf("startPos Y = %f\n", vecStart->y);
  printf("endPos X = %f\n", out.endPos->x);
  printf("endPos Y = %f\n", out.endPos->y);
  //--------------------------------------------


  return out;
}

//draw ray
void drawRay(t_data *data, ray *myRay, int color)
{
 
  Vec2 *start = myRay->startPos;
  Vec2 *end = myRay->endPos;
  createLine(data, data->current_img, myRay->startPos->x, myRay->startPos->y, myRay->endPos->x, myRay->endPos->y, color);
}
