#include <stdio.h>
#include <stdlib.h>
#include <mlx/mlx.h>
#include "wolfenstein.h"

//creates button instance
button createButton(int BDcolor, int INcolor, int BDwidth, int posX, int posY, int sizeX, int sizeY, void (*function)(void))
{
  button new_button;
  new_button.borderColor = BDcolor;
  new_button.insideColor = INcolor;
  new_button.borderWidth = BDwidth;
  new_button.posX = posX;
  new_button.posY = posY;
  new_button.sizeX = sizeX;
  new_button.sizeY = sizeY;
  new_button.function = function;
  return new_button;
}

//draw button to screen
void drawButton(t_data *data, t_image *img, button *butt)
{
//----------------------------------VARIABLE DECLARATION------------------------------------------------------------
  intVec2 endPos;
  endPos.x = butt->posX + butt->sizeX;
  endPos.y = butt->posY + butt->sizeY;
 
  intVec2 startFill;
  startFill.x = butt->posX + butt->borderWidth;
  startFill.y = butt->posY + butt->borderWidth;
  intVec2 endFill;
  endFill.x = endPos.x - butt->borderWidth;
  endFill.y = endPos.y - butt->borderWidth;
//-----------------------------------------------------------------------------------------------------------------

  //draw button
  createRectangle(data, img, butt->posX, butt->posY, endPos.x, endPos.y, butt->borderColor);
  createRectangle(data, img, startFill.x, startFill.y, endFill.x, endFill.y, butt->insideColor);
}

 
