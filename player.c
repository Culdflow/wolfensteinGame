#include <stdio.h>
#include "wolfenstein.h"
#include <math.h>

#define PI 3.141592654

//make player move by x ok the x axis and y on the y axis
void playerMove(t_data *data, double step)
{
  //convert dir to radiant
  double radiant = (data->player->dir * PI)/180;
  //calculate new y and new x
  double newX = step * cos(radiant);
  double newY = step * sin(radiant);
  
  data->player->posX += newX;
  data->player->posY += newY;
  
}

//draw player to screen
void drawPlayer(t_data *data, t_image *img, t_player *pl)
{
  my_mlx_pixel_put(img, pl->posX, pl->posY, 0x00FF0050);
  my_mlx_pixel_put(img, pl->posX+1, pl->posY, 0x00FF0050);
  my_mlx_pixel_put(img, pl->posX-1, pl->posY, 0x00FF0050);
  my_mlx_pixel_put(img, pl->posX, pl->posY+1, 0x00FF0050);
  my_mlx_pixel_put(img, pl->posX, pl->posY-1, 0x00FF0050);

}
