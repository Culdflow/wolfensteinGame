#ifndef _Wolfenstein_H
#define _Wolfenstein_H


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


//define struct t_data
typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
    t_map *map;
    int mouseX;
    int mouseY;
    t_img *current_img;
    t_img *img2;
    t_img *last_img;
}	t_data;


// --------------------DECLARATION OF FUNCTIONS---------------------------------------------------


int mouse_pos(t_data *data);
//map.c
t_map createMap(int x,int y, int offset, int WINDOW_WIDTH, int WINDOW_HEIGHT);
//pixelPut.c
void createMapImg(t_data *data, t_img *img, t_map *map, int WINDOW_WIDTH, int WINDOW_HEIGHT, int offset);
void createRectangle(t_data *data, t_img *img, int x1_, int y1_, int x2_, int y2_,int color, int WINDOW_WIDTH, int WINDOW_HEIGHT);
void createLine(t_data *data, t_img *img, int x1_, int y1_, int x2_, int y2_, int color, int WINDOW_WIDTH, int WINDOW_HEIGHT);
void highlight_box(t_data *data, t_img *img, int WINDOW_WIDTH, int WINDOW_HEIGHT);
void highlight(t_data *data, t_img *img, int x1, int x2, int y1, int y2, int WINDOW_WIDTH, int WINDOW_HEIGHT);
void my_mlx_pixel_put(t_img *data, int x, int y, int color);
#endif




