#include "wolfenstein.h"
#include <mlx/mlx.h>
#include <stdio.h>

//draws a pixel on the screen
void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
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

//draw highlights when mouse is on them
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

    int diff1;
    int diff2;
   
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
    diff1 = X2 - X1;
    diff2 = Y2 - Y1;
    //printf("ray start pos X = %d\n", X1);
    //printf("ray start pos Y = %d\n", Y1);
    //printf("ray end pos X = %d\n", X2);
    //printf("ray end pos Y = %d\n", Y2);
    

    //if the line is vertical
    if ( X1 == X2 )
    {
      for (int i = Y1; i <= Y2; i++ )
        {my_mlx_pixel_put(img, X1, i, color);}
    }
    //if line is horizontal
    else if (Y1 == Y2)
    { 
      for (int i = X1; i <= X2; i++ )
        {my_mlx_pixel_put(img, i, Y1, color);}
    }
    //if line is diagonal
    else 
    {
      if (diff1 >= diff2)
      {
        int new_y = Y1;
        int rate;
        for (int i = X1; i < diff1 + X1; i++)
        {
          if (( X2 - i) != 0 && ( Y2 - new_y) != 0)
          {
          rate = (X2 - i) / (Y2 - new_y);
          if (i % rate == 0 )
            {new_y += 1;}
          else{break;}
          }

          my_mlx_pixel_put(img, i, new_y, color);
        }
      }
      else 
      {
        int new_x = X1;
        int rate;
        for (int i = Y1; i < diff2 + Y1; i++)
        {
          if (( Y2 - i) != 0 && ( X2 - new_x) != 0)
          {
          rate = (Y2 - i) / (X2 - new_x);
          if (i % rate == 0 )
            {new_x += 1;}
          }
          else{break;}
          //printf("putting pixel in X = %d\n", new_x);
          //printf("putting pixel in Y = %d\n", i);
          my_mlx_pixel_put(img, new_x, i, color);        
        }
      }
    drawSquare(data, img, X2-2, Y2-2, X2+2, Y2+2, 0x00FF0000);
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
            my_mlx_pixel_put(img, x, y, color);
        }

    }
}



void clearImage(t_image *img, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
  for(int x = 0; x < WINDOW_WIDTH; x++)
  {
    for(int y = 0; y < WINDOW_HEIGHT; y++)
      my_mlx_pixel_put(img, x, y, 0x00000000);
  }
}
