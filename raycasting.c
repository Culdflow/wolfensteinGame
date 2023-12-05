#include "wolfenstein.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592654


ray createRay(t_data *data, Vec2 *vecStart, int angle)
{
  float rx, ry, ox, oy, dof = 0;
  
  //setup error return
  Vec2 ERR;
  ERR.x = -1;
  ERR.y = -1;
  ray ERROR;
  ERROR.startPos = &ERR;
  ERROR.endPos = &ERR;

  //setup pointers
  t_player *player = data->player;
  t_map *map = data->map;
  
  //setup getmapPos
  Vec2 mapPos = getMapPos(data, vecStart->x, vecStart->y);
  if (mapPos.x == -1){printf("player not in map\n"); return ERROR;}
  int newMapPos[2] = {mapPos.x, mapPos.y};
  
  //setup helpful variables
  float rad = (angle * PI) / 180;
  float atan = 1/tan(rad);
  
  //setup output ray
  ray out;
  out.startPos = vecStart;
  out.angle = angle;
  printf("angle = %d\n", angle);


  //if looking up set ray position accordingly
  if (angle < 0 ) //looking up
  {
    ry = map->map_coord[newMapPos[0]][newMapPos[1]][1];
    rx = (player->pos->y - ry)*atan + player->pos->x;
    oy = map->map_coord[newMapPos[0]-1][newMapPos[1]][1] - ry;
    ox = -oy * atan;
    printf("updated (up) ry = %f, rx = %f, oy = %f, ox = %f", ry, rx, oy, ox);  

  }
  //if looking down set ray position accordingly
  else if (angle > 0)
  {
    ry = map->map_coord[newMapPos[0]][newMapPos[1]][3];
    rx = (player->pos->y - ry)*atan + player->pos->x;
    oy = map->map_coord[newMapPos[0]+1][newMapPos[1]][3] - ry;
    ox = -oy * atan;
    printf("updated (down) ry = %f, rx = %f, oy = %f, ox = %f", ry, rx, oy, ox);  
  }
  //if ray looking straight right or straight left
  else 
  {
    rx = player->pos->x;
    ry = player->pos->y;
    dof = 3;
  }
  //loop for depth of view
  while (dof < 3)
  {
    //printf("dof = %f\n", dof);
    //get map pos
    mapPos = getMapPos(data, rx, ry);
    if (mapPos.x == -1){printf("ray not in map\n"); return ERROR;}
    newMapPos[0] = mapPos.x; newMapPos[1] = mapPos.y;
    //if wall stop
    if (map->map[newMapPos[0]][newMapPos[1]] == 1)
    {
      dof = 3;
    }
    //else keep looking forward
    else
    {
      printf("didnt hit wall rx = %f ry = %f\n", rx, ry);
      printf("ox = %f oy = %f\n", ox, oy);
      rx += ox;
      ry += oy;
      dof += 1;
    }
  }
  Vec2 endPos;
  endPos.x = rx;
  endPos.y = ry;
  out.endPos = &endPos;
  drawRay(data, &out, 0x0000FF00);
  return out;
}

//draw ray
void drawRay(t_data *data, ray *myRay, int color)
{
  Vec2 *start = myRay->startPos;
  Vec2 *end = myRay->endPos;
  createLine(data, data->current_img, start->x, start->y, end->x, end->y, color);
}
