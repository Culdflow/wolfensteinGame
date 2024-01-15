#include "wolfenstein.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592654
#define maxRayLength 350

//create ray list
ray *createRayList(t_data *data, int angle, ray *OGRay,  ray *ray, int i)
{
  printf("creating ray nb %d\n", i);

  if (i == data->player->fov - 1)
  {
    printf("last ray\n");
    ray = createRay(data, data->player->pos, angle + i);
    ray->tag = 'e';
    printf("tag done\n");
    return OGRay;
  }
  ray = createRay(data, data->player->pos, angle + i);
  return createRayList(data, angle, OGRay, ray->nextRay, i+1);
}


//creates a ray
ray *createRay(t_data *data, Vec2 *vecStart, int angle)
{
  printf("new ray\n");
  //create ray output
  printf("ray out?\n");
  ray *out = malloc(sizeof(ray));
  printf("declaration passed\n");
  out->startPos = vecStart;
  printf("done\n");
  //setup ray error
  ray *rayERROR;
  Vec2 *ERRstart;
  ERRstart->x = 50;
  ERRstart->y = 50;
  Vec2 *ERRend;
  ERRend->x = 950;
  ERRend->y = 50;
  printf("is it this?\n");
  rayERROR->startPos = ERRstart;
  rayERROR->endPos = ERRend;

  //setup Vec error
  intVec2 ERROR;
  ERROR.x = 0;
  ERROR.y = 0;

  //create unit step
  Vec2 unitStep;
  unitStep.x = data->map->map_coord[0][0][2] - data->map->map_coord[0][0][0]; 
  unitStep.y = data->map->map_coord[0][0][3] - data->map->map_coord[0][0][1];  
  printf("unitstep passed\n");
  //create dof depth of field
  int dof = 0;

  //convert angle to rad
  float angleRad = (abs(angle) * PI) / 180; 

  //first intersection
  Vec2 interY;
  Vec2 interX;

  //get y map position for player position
  intVec2 playerMapPos = getMapPos(data, (int)vecStart->x, (int)vecStart->y);
  printf("playermappos passed\n");

  if (playerMapPos.x == -1) return rayERROR;

//----------------------SETUP BASE RAYCAST VALUES---------------------------------------------------------------------

  //setup interY wich checks for collisions on y
  if (angle < 0) {interY.y = data->map->map_coord[playerMapPos.x][playerMapPos.y][1]-1;}
  else if (angle > 0) {interY.y = data->map->map_coord[playerMapPos.x][playerMapPos.y][3]+1;}
  else interY.y = vecStart->y; 


  //get interX wich checks for collisions on X
  if (angle > - 90 && angle < 90) {interX.x = data->map->map_coord[playerMapPos.x][playerMapPos.y][2]+1;}
  else if (angle < - 90 || angle > 90) {interX.x = data->map->map_coord[playerMapPos.x][playerMapPos.y][0]-1;}
  else interX.x = vecStart->x;
  
  //setup x pos
  if (angle < 0) interX.y = vecStart->y + (vecStart->x - interX.x) * tan(angleRad);
  else interX.y = vecStart->y - (vecStart->x - interX.x) * tan(angleRad);
  interY.x = vecStart->x + abs(vecStart->y - interY.y) / tan(angleRad);

//----------------------------------------------------------------------------------------------------------------------
  printf("passed interY parmaters\n");
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
  hyp.x = hypot(lengthX.x, lengthX.y);
  hyp.y = hypot(lengthY.x, lengthY.y);

  Vec2 ogHyp;
  ogHyp.x = hyp.x;
  ogHyp.y = hyp.y;
  
  //if found wall == 1 found wall in x if found wall == 2 found wall in y
  int foundWall = 0;

//---------------------------------------------LOOP----------------------------------------------------------------------
  for (int i = 0;i < dof; i++)
  {
    
    
    vecMapPosY = getMapPos(data, (int)interY.y, (int)interY.x);
    vecMapPosX = getMapPos(data, (int)interX.y, (int)interX.x);
    printf("vecmapos passed\n");
    //IF HIT WALL
    if (data->map->map[vecMapPosY.y][vecMapPosY.x] == 1) 
    {
      if (foundWall != 2 && foundWall != 3) foundWall += 2; 
    }

    if (data->map->map[vecMapPosX.y][vecMapPosX.x] == 1) 
    {
      if (foundWall != 1 && foundWall != 3) foundWall += 1; 
    }



    
    if (foundWall < 2)
    {
      if (angle < 0) 
      {
        interY.y -= unitStep.y;
        interY.x += unitStep.y/tan(angleRad);
      }
      else if (angle > 0) 
      {
        interY.y += unitStep.y;
        interY.x += unitStep.y/tan(angleRad);
      }
      

    }
    if (foundWall < 1 || foundWall == 2)
    {
      if (angle > - 90 && angle < 90)
      {
        interX.x += unitStep.x;
        if (angle < 0) interX.y -= unitStep.y * tan(angleRad);
        else interX.y += unitStep.y * tan(angleRad);
      }
      else if (angle < - 90 || angle > 90)
      {
        interX.x -= unitStep.x;
        if (angle < 0) interX.y += unitStep.y * tan(angleRad);
        else interX.y -= unitStep.y * tan(angleRad);
      }

    }
    lengthX.x = abs(interX.x - vecStart->x);
    lengthX.y = abs(interX.y - vecStart->y);

    lengthY.x = abs(interY.x - vecStart->x);
    lengthY.y = abs(interY.y - vecStart->y);

    hyp.y = hypot(lengthY.x, lengthY.y);
    hyp.x = hypot(lengthX.x, lengthX.y);
         
  }
  
//-------------------------------------------------------------------------------------------------------------------------------------
  printf("passed loop\n");
  //set ray out dependant on wich ray is shorter
  if (foundWall == 2 && hyp.y < hyp.x) {out->endPos = &interY;}
  else if (foundWall == 1 && hyp.x < hyp.y) {out->endPos = &interX;}
  else 
  {
    if (hyp.y < hyp.x) out->endPos = &interY;
    else out->endPos = &interX;
  }
  if (out->endPos == &interY) out->length = hyp.y;
  else out->length = hyp.x;
  
  float playerAngleRad = (abs(data->player->dir) * PI) / 180;

  out->length *= cos(angleRad - playerAngleRad);

 //drawSquare(data, data->current_img, interX.x - 2, interX.y - 2, interX.x + 2, interX.y + 2, 0x00FF0000); 
 //drawSquare(data, data->current_img, interY.x - 2, interY.y - 2, interY.x + 2, interY.y + 2, 0x00FF0000); 
  
  
  //check limits
  if (out->endPos->x > data->sizeX) out->endPos->x = data->sizeX;
  if (out->endPos->x < 0) out->endPos->x = 0;
  if (out->endPos->y > data->sizeY) out->endPos->y = data->sizeY;
  if (out->endPos->y < 0) out->endPos->y = 0;

  printf("passed ray\n");


  return out;
}

//draw ray
void drawRay(t_data *data, ray *myRay, int color)
{
  printf("drawing ray\n");
  if (myRay->tag == 'e')
  {
    createLine(data, data->current_img, myRay->startPos->x, myRay->startPos->y, myRay->endPos->x, myRay->endPos->y, color);
    return;
  }
  printf("if passed\n");
  createLine(data, data->current_img, myRay->startPos->x, myRay->startPos->y, myRay->endPos->x, myRay->endPos->y, color);
  drawRay(data, myRay->nextRay, color);
  freeRay(data, data->Ray);
}

void freeRay(t_data *data, ray *ray)
{
  if (ray->tag == 'e')
  {
    free(ray);
    return;
  }
  freeRay(data, ray->nextRay);
  free(ray);
}
