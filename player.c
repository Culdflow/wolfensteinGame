#include <stdio.h>
#include "wolfenstein.h"
#include <math.h>

#define PI 3.141592654

//make player move by x ok the x axis and y on the y axis
void playerMove(t_data *data, double step)
{
  //convert dir to radiant
  double radiant = (data->player->dir * PI)/180;
  printf("dir = %d\n", data->player->dir);
  //calculate new y and new x
  double newX = step * cos(radiant);
  double newY = step * sin(radiant);
  
  printf("new x = %f\n", newX);
  printf("new y = %f\n", newY);
  data->player->posX += newX;
  data->player->posY += newY;
  
}

