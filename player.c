#include <stdio.h>
#include "wolfenstein.h"

//make player move by x ok the x axis and y on the y axis
void playerMove(t_data *data, int x, int y)
{
  //change position variables in data's player
  if (!(x<=0 && data->player->posX <= x))
    data->player->posX += x;
  if (!(y<=0 && data->player->posY <= y))
    data->player->posY += y;
}
