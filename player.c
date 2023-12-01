#include <stdio.h>
#include "wolfenstein.h"
#include <math.h>

#define PI 3.141592654

//make player move by x ok the x axis and y on the y axis
void playerMove(t_data *data, int step)
{
  //convert dir to radiant
  int radiant = (data->player->dir * PI)/180;
  
  //calculate new y and new x
  int newX = step * cos(radiant);
  int newY = step * sin(radiant);

  data->player->posX += newX;
  data->player->posY += newY;
  
}

