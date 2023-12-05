#include "wolfenstein.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592654


ray createRay(t_data *data, Vec2 *start, int angle)
{
  float rx, ry, ox, oy, dof = 0;

  ray ERROR;
  ERROR.startPos->x = -1;

  t_player *player = data->player;
  t_map *map = data->map;
  Vec2 mapPos = getMapPos(data, start->x, start->y);
  if (mapPos.x == -1){printf("player not in map"); return ERROR;}
  int newMapPos[2] = {mapPos.x, mapPos.y};

  float rad = (angle * PI) / 180;
  float atan = 1/tan(rad);
  
  ray out;
  out.startPos = start;
  out.angle = angle;

  if (angle < 0) //looking up
  {
    ry = map->map_coord[newMapPos[0]][newMapPos[1]][1];
    rx = (player->pos->y - ry)*atan + player->pos->x;
    oy = map->map_coord[newMapPos[0]][newMapPos[1]-1][1] - ry;
    ox = -oy * atan;
  }
  else if (angle > 0)
  {
    ry = map->map_coord[newMapPos[0]][newMapPos[1]][3];
    rx = (player->pos->y - ry)*atan + player->pos->x;
    oy = map->map_coord[newMapPos[0]][newMapPos[1]+1][3] - ry;
    ox = -oy * atan;
  }
  else 
  {
    rx = player->pos->x;
    ry = player->pos->y;
    dof = 2;
  }
  
  while (dof < 2)
  {
    mapPos = getMapPos(data, start->x, start->y);
    if (mapPos.x == -1){printf("player not in map"); return ERROR;}
    newMapPos[0] = mapPos.x; newMapPos[1] = mapPos.y;
    if (map->map[newMapPos[0]][newMapPos[1]] == 1)
    {
      dof = 2; //hit wall
    }
    else
    {
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
