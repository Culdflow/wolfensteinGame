#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wolfenstein.h"

int mainMap[20][20] = {{1,1,1,1,1,1,1,1,1,1},
                       {1,0,0,0,0,0,0,0,0,1},
                       {1,0,1,0,1,0,0,0,1,1},
                       {1,1,0,0,0,0,0,0,0,1},
                       {1,1,0,0,0,0,0,0,0,1},
                       {1,1,0,0,0,0,0,0,0,1},
                       {1,1,0,0,0,0,0,0,0,1},
                       {1,1,0,0,0,0,0,0,0,1},
                       {1,1,0,0,0,0,0,0,0,1},
                       {1,0,0,0,1,0,0,0,0,1}};


//creates map with nested arrays
t_map createMap(int x,int y, int offset, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    //initializing map instance
    t_map map_;
    map_.x = x;
    map_.y = y;
    
    //puts in map values
    for (int c_x = 0; c_x < x; c_x++)
    {
        for (int c_y = 0; c_y < y; c_y++)
        {
            map_.map[c_x][c_y] = mainMap[c_x][c_y];
            //set coordinates
            map_.map_coord[c_y][c_x][0]= offset + c_x * ((WINDOW_WIDTH -(offset*2))/x);
            map_.map_coord[c_y][c_x][1]= offset + c_y * ((WINDOW_HEIGHT -(offset*2))/y);
            map_.map_coord[c_y][c_x][2]= offset + (c_x+1) * ((WINDOW_WIDTH -(offset*2))/x);
            map_.map_coord[c_y][c_x][3]= offset + (c_y+1) * ((WINDOW_HEIGHT -(offset*2))/y);
        }
    }   

    //returns t_map element
    return map_;
}


//creates 2D view of the map
void createMapImg(t_data *data, t_image *img, t_map *map, int WINDOW_WIDTH, int WINDOW_HEIGHT, int offset)
{
    //creates outline
    drawSquare(data, img, offset, offset, WINDOW_WIDTH-offset, WINDOW_HEIGHT-offset, 0x00FFFFFF);  
    //creates walls 
    for (int x = 0; x <= data->map->x ; x++) 
        {
          for (int y = 0; y <= data->map->y ; y++)
          {
              if (data->map->map[x][y] == 1)
              { createRectangle(data, img, (data->map->map_coord[x][y][0]), (data->map->map_coord[x][y][1]), (data->map->map_coord[x][y][2]), (data->map->map_coord[x][y][3]), 0x00FFFFFF);}
          } 
        }
}

//when clicked track if clicked on a box to turn it into a wall
void whenClicked(t_data *data)
{
  for (int x = 0; x <= data->map->x; x++)
  {
    for (int y = 0; y <= data->map->y; y++)
    {

    }
  }

}

//returns the position you are in the map
intVec2 getMapPos(t_data *data, int posX, int posY)
{
  intVec2 ERROR;
  ERROR.x = -1;
  ERROR.y = -1;
  //instance vector 2 
  intVec2 mapPos;
  mapPos = ERROR;

  //cycle through map
  for (int x = 0; x <= data->map->x; x++)
  {
    for (int y = 0; y <= data->map->y; y++)
    {
     //if mouse 
     if ( posX > data->map->map_coord[x][y][0] && 
          posX <= data->map->map_coord[x][y][2] && 
          posY > data->map->map_coord[x][y][1] &&
          posY <= data->map->map_coord[x][y][3])
      {
        mapPos.x = x;
        mapPos.y = y;
      }
    }
  }
  if (mapPos.x == ERROR.x)
    {printf("coord not in map\n");return ERROR;}
  return mapPos;
}
