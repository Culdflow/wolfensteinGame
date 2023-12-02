#include "wolfenstein.h"
#include <stdio.h>


void updatePlayerDir(t_data *data)
{
  data->player->dir += (data->mouseX - data->oldMouseX)/4;
}
