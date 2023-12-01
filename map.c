#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wolfenstein.h"

int mainMap[20][20] = {{0,0,0,0,0},
                       {0,0,0,0,0},
                       {0,0,1,0,0},
                       {0,0,0,0,0},
                       {0,0,0,0,0}};


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
            map_.map_coord[c_x][c_y][0]= offset + c_x * ((WINDOW_WIDTH -(offset*2))/x);
            map_.map_coord[c_x][c_y][1]= offset + c_y * ((WINDOW_HEIGHT -(offset*2))/y);
            map_.map_coord[c_x][c_y][2]= offset + (c_x+1) * ((WINDOW_WIDTH -(offset*2))/x);
            map_.map_coord[c_x][c_y][3]= offset + (c_y+1) * ((WINDOW_HEIGHT -(offset*2))/y);

            
        }
    }   

    //returns t_map element
    return map_;
}

//when clicked track if clicked on a box to turn it into a wall
void whenClicked(t_data *data)
{
  for (int x = 0; x <= data->map->x; x++)
  {
    for (int y = 0; y <= data->map->y; y++)
    {
      if (data->mouseX >= data->map->map_coord[x][y][0] && 
          data->mouseX <= data->map->map_coord[x][y][2] && 
          data->mouseX >= data->map->map_coord[x][y][1] &&
          data->mouseX <= data->map->map_coord[x][y][3])
      {printf("clciked on square");}
    }
  }

}

