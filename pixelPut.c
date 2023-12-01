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


//creates 2D view of the map
void createMapImg(t_data *data, t_image *img, t_map *map, int WINDOW_WIDTH, int WINDOW_HEIGHT, int offset)
{
    //creates background
    createRectangle(data, img, offset, offset, WINDOW_WIDTH-offset, WINDOW_HEIGHT-offset, 0xFF801050, WINDOW_WIDTH, WINDOW_HEIGHT);

    //creates outline 
    for (int x = 0; x <= data->map->x ; x++) 
        {
          for (int y = 0; y <= data->map->y ; y++)
          {
          
            drawSquare(data, img, data->map->map_coord[x][y][0], data->map->map_coord[x][y][2], data->map->map_coord[x][y][1], data->map->map_coord[x][y][3], 0x00101010, WINDOW_WIDTH, WINDOW_HEIGHT);
              if (data->map->map[x][y] == 1)
              { createRectangle(data, img, (data->map->map_coord[x][y][0])+1, (data->map->map_coord[x][y][1])+1, (data->map->map_coord[x][y][2])-1, (data->map->map_coord[x][y][3])-1, 0x00FFFFFF, WINDOW_WIDTH, WINDOW_HEIGHT);
              }


          } 
        }
}

//highlight boxes when mouse is on them
void highlight_box(t_data *data, t_image *img, int WINDOW_WIDTH, int WINDOW_HEIGHT)
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
      {drawSquare(data, img, data->map->map_coord[x][y][0], data->map->map_coord[x][y][2], data->map->map_coord[x][y][1], data->map->map_coord[x][y][3], 0x00FFFF00, WINDOW_WIDTH, WINDOW_HEIGHT);}    
    }
  }
}

//draw highlights when mouse is on them
void drawSquare(t_data *data, t_image *img, int x1, int x2, int y1, int y2, int color, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
  // draw lines
  createLine(data, img, x1, y1, x2, y1, color, WINDOW_WIDTH, WINDOW_HEIGHT);
  createLine(data, img, x1, y2, x2, y2, color, WINDOW_WIDTH, WINDOW_HEIGHT);
  createLine(data, img, x1, y1, x1, y2, color, WINDOW_WIDTH, WINDOW_HEIGHT);
  createLine(data, img, x2, y1, x2, y2, color, WINDOW_WIDTH, WINDOW_HEIGHT);
}
//draws a line using 4 values
void createLine(t_data *data,t_image *img, int x1_, int y1_, int x2_, int y2_, int color, int WINDOW_WIDTH, int WINDOW_HEIGHT)
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
void createRectangle(t_data *data, t_image *img, int x1_, int y1_, int x2_, int y2_,int color, int WINDOW_WIDTH, int WINDOW_HEIGHT)
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

void drawPlayer(t_data *data, t_image *img, t_player *pl)
{
  my_mlx_pixel_put(img, pl->posX, pl->posY, 0x00FF0050);
}

void clearImage(t_image *img, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
  for(int x = 0; x < WINDOW_WIDTH; x++)
  {
    for(int y = 0; y < WINDOW_HEIGHT; y++)
      my_mlx_pixel_put(img, x, y, 0x00000000);
  }
}
