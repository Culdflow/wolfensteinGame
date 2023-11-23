#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wolfenstein.h"


//creates map with nested arrays
t_map createMap(int x,int y, int offset, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    //initializing map instance
    t_map mymap;
    mymap.x = x;
    mymap.y = y;
    
    //puts in map values
    for (int c_x = 0; c_x < x; c_x++)
    {
        
        for (int c_y = 0; c_y < y; c_y++)
        {
            mymap.map[c_x][c_y] = 1;
            //set coordinates
            mymap.map_coord[c_x][c_y][0]= offset + c_x * ((WINDOW_WIDTH -(offset*2))/x);
            mymap.map_coord[c_x][c_y][1]= offset + c_y * ((WINDOW_HEIGHT -(offset*2))/y);
            mymap.map_coord[c_x][c_y][2]= offset + (c_x+1) * ((WINDOW_WIDTH -(offset*2))/x);
            mymap.map_coord[c_x][c_y][3]= offset + (c_y+1) * ((WINDOW_HEIGHT -(offset*2))/y);

            
        }
    }   

    //returns t_map element
    return mymap;
}


