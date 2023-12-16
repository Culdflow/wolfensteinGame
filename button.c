#include <stdio.h>
#include <stdlib.h>
#include <mlx/mlx.h>
#include "wolfenstein.h"

void drawButton(t_data *data, t_image *img, button *butt)
{
  intVec2 endPos;
  endPos.x = butt->posX + butt->sizeX;
  endPos.y = butt->posY + butt->sizeY;
  createRectangle(data, img, butt->posX, butt->posY, endPos.x, endPos.y, butt->borderColor);
  intVec2 startFill;
  startFill.x = butt->posX + butt->borderWidth;
  startFill.y = butt->posY + butt->borderWidth;
  intVec2 endFill;
  endFill.x = endPos.x - butt->borderWidth;
  endFill.y = endPos.y - butt->borderWidth;
  createRectangle(data, img, startFill.x, startFill.y, endFill.x, endFill.y, butt->insideColor);
}
