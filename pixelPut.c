#include "wolfenstein.h"
#include <mlx/mlx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//draws a pixel on the screen
void	my_mlx_pixel_put(t_data *data, t_image *img, int x, int y, int color)
{
	char	*dst;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	  *(unsigned int*)dst = color;
}




//highlight boxes when mouse is on them
void highlight_box(t_data *data, t_image *img)
{
   //run through map to check if your cursor is on  a box
  for (int x = 0; x<= data->map->x; x++)
  {
    for (int y=0; y<= data->map->y; y++)
    {
      if(data->mouseX > data->map->map_coord[x][y][0] &&
          data->mouseX < data->map->map_coord[x][y][2] &&
          data->mouseY > data->map->map_coord[x][y][1] &&
          data->mouseY < data->map->map_coord[x][y][3])
      {drawSquare(data, img, data->map->map_coord[x][y][0], data->map->map_coord[x][y][1], data->map->map_coord[x][y][2], data->map->map_coord[x][y][3], 0x00FFFF00);}    
    }
  }
}

//draw square
void drawSquare(t_data *data, t_image *img, int x1, int y1, int x2, int y2, int color)
{
  // draw lines
  createLine(data, img, x1, y1, x2, y1, color);
  createLine(data, img, x1, y2, x2, y2, color);
  createLine(data, img, x1, y1, x1, y2, color);
  createLine(data, img, x2, y1, x2, y2, color);
}
//draws a line using 4 values
void createLine(t_data *data,t_image *img, int x1_, int y1_, int x2_, int y2_, int color)
{
    //initialize variables
    int X1;
    int X2;
    int Y1;
    int Y2;

    float diffX;
    float diffY;
   
    //organize x and y seperately
    if(x1_ <= x2_)
    {X1 = x1_; X2 = x2_;}
    else
    {X1 = x2_; X2 = x1_;} 

    if(y1_ <= y2_)
    {Y1 = y1_; Y2 = y2_;}
    else
    {Y1 = y2_; Y2 = y1_;}

    //calculate diff
    diffX = abs(x2_) - abs(x1_);
    diffY = abs(y2_) - abs(y1_);
    

      float step;
      Vec2 strtPix;
      Vec2 endPix;
      int intStep;
      if (diffX > diffY)
      {
        if (diffX > 0) {strtPix.x = x1_; strtPix.y = y1_; endPix.x = x2_; endPix.y = y2_;}
        else {strtPix.x = x2_; strtPix.y = y2_; endPix.x = x1_; endPix.y = y1_;}
        step = strtPix.y;
        if (endPix.x > data->sizeX) endPix.x = data->sizeX;
        if (endPix.y > data->sizeY) endPix.y = data->sizeY;
        if (endPix.x < 0) endPix.x = 0;
        if (endPix.y < 0) endPix.y = 0;
        

        for(int x = strtPix.x; x < endPix.x; x++)
        {
          intStep = (int)step;
          my_mlx_pixel_put(data, img, x, intStep, color);
          step += diffY / diffX;
        }

      }
      else 
      {
        if (diffY > 0) {strtPix.x = x1_; strtPix.y = y1_; endPix.x = x2_; endPix.y = y2_;}
        else {strtPix.x = x2_; strtPix.y = y2_; endPix.x = x1_; endPix.y = y1_;}

        step = strtPix.x;
        for(int y = strtPix.y; y < endPix.y; y++)
        {
          intStep = (int)step;
          my_mlx_pixel_put(data, img, intStep, y, color);
          step += diffX / diffY;          
        }
      }
}



//creates a rectangle using 2 positions on the screen
void createRectangle(t_data *data, t_image *img, int x1_, int y1_, int x2_, int y2_,int color)
{
    //initializing variables
    int X1;
    int X2;
    int Y1;
    int Y2;

    //sorting x and y values
    if(x1_ <= x2_)
    {X1 = x1_; X2 = x2_;}
    else
    {X1 = x2_; X2 = x1_;} 

    if(y1_ <= y2_)
    {Y1 = y1_; Y2 = y2_;}
    else
    {Y1 = y2_; Y2 = y1_;} 
    

    //draws rectangle
    for (int x = X1; x <= X2; x++)
    {
        for (int y = Y1; y <= Y2; y++)
        {
            my_mlx_pixel_put(data, img, x, y, color);
        }

    }
}



void clearImage(t_data *data, t_image *img, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
  for(int x = 0; x < WINDOW_WIDTH; x++)
  {
    for(int y = 0; y < WINDOW_HEIGHT; y++)
      my_mlx_pixel_put(data, img, x, y, 0x00000000);
  }
}
