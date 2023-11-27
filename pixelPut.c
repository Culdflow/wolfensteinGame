#include "wolfenstein.h"
#include <mlx/mlx.h>
#include <stdio.h>

//draws a pixel on the screen
void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


//creates 2D view of the map
void createMapImg(t_data *data, t_img *img, t_map *map, int WINDOW_WIDTH, int WINDOW_HEIGHT, int offset)
{
    t_img p_img = *img;
      
    //creates background
    createRectangle(data, &p_img, offset, offset, WINDOW_WIDTH-offset, WINDOW_HEIGHT-offset, 0x50505050, WINDOW_WIDTH, WINDOW_HEIGHT);

    //creates outline 
    for (int x = offset; x <= WINDOW_WIDTH -offset; x = x + (WINDOW_WIDTH-(offset*2))/map->x) 
        {
            for (int i = offset; i < WINDOW_HEIGHT -offset; i++ )
            {
                my_mlx_pixel_put(&p_img, x, i, 0x00FF0000);
               
            }

        }
    for (int y = offset; y <= WINDOW_HEIGHT -offset; y = y + (WINDOW_HEIGHT-(offset*2))/map->y)
        {
            for (int i = offset; i < WINDOW_WIDTH-offset; i++ )
            {
                my_mlx_pixel_put(&p_img, i, y, 0x00FF0000);
               
            }

        }
}

//highlight boxes when mouse is on them
void highlight_box(t_data *data, t_img *img, int WINDOW_WIDTH, int WINDOW_HEIGHT)
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
      {highlight(data, img, data->map->map_coord[x][y][0], data->map->map_coord[x][y][2], data->map->map_coord[x][y][1], data->map->map_coord[x][y][3], WINDOW_WIDTH, WINDOW_HEIGHT);}    
    }
  }
}

//draw highlights when mouse is on them
void highlight(t_data *data, t_img *img, int x1, int x2, int y1, int y2, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
  // draw lines
  createLine(data, img, x1, y1, x2, y1, 0x00FFFF00, WINDOW_WIDTH, WINDOW_HEIGHT);
  createLine(data, img, x1, y2, x2, y2, 0x00FFFF00, WINDOW_WIDTH, WINDOW_HEIGHT);
  createLine(data, img, x1, y1, x1, y2, 0x00FFFF00, WINDOW_WIDTH, WINDOW_HEIGHT);
  createLine(data, img, x2, y1, x2, y2, 0x00FFFF00, WINDOW_WIDTH, WINDOW_HEIGHT);
}
//draws a line using 4 values
void createLine(t_data *data,t_img *img, int x1_, int y1_, int x2_, int y2_, int color, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    //initialize variables
    int X1;
    int X2;
    int Y1;
    int Y2;

    //organize x and y seperately
    if(x1_ <= x2_)
    {X1 = x1_; X2 = x2_;}
    else
    {X1 = x2_; X2 = x1_;} 

    if(y1_ <= y2_)
    {Y1 = y1_; Y2 = y2_;}
    else
    {Y1 = y2_; Y2 = y1_;} 

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
      printf("ERROR diagonal lines not supported in function createLine\n");
    } 
}


//creates a rectangle using 2 positions on the screen
void createRectangle(t_data *data, t_img *img, int x1_, int y1_, int x2_, int y2_,int color, int WINDOW_WIDTH, int WINDOW_HEIGHT)
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
