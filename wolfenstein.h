#ifndef _Wolfenstein_H
#define _Wolfenstein_H


//define struct t_data
typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
}	t_data;


//define struct t_img
typedef struct s_img
{
    void *img;
    char *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_img;



//define struct t_map
typedef struct s_map
{
    int x;
    int y;
    int map[20][20];
    int map_coord[20][20][4];
}   t_map;

// --------------------DECLARATION OF FUNCTIONS---------------------------------------------------

//map.c
t_map createMap(int x,int y, int offset, int WINDOW_WIDTH, int WINDOW_HEIGHT);
//pixelPut.c
t_img createMapImg(t_data *data, t_map *map, int WINDOW_WIDTH, int WINDOW_HEIGHT, int offset);
t_img createRectangle(t_data *data, int x1_, int y1_, int x2_, int y2_,int color, int WINDOW_WIDTH, int WINDOW_HEIGHT);

#endif




