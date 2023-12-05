#include "wolfenstein.h"
#include <stdio.h>


void updatePlayerDir(t_data *data)
{
  if (data->player->dir < - 180) {data->player->dir += 360;}
  if (data->player->dir > 180) {data->player->dir -= 360;}
  data->player->dir -= (data->mouseX - data->oldMouseX)/3;
}
