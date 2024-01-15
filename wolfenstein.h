#ifndef _Wolfenstein_H
#define _Wolfenstein_H

//---------------------------DECLARE STRUCTS-----------------------------------------------
typedef struct s_ray ray;

//---------------------------DEFINE STRUCTS------------------------------------------------

//define debug_struct
typedef struct s_debug
{
    int list[20];
}   debug;

//define button struct
typedef struct s_button
{
    int   borderColor;
    int   insideColor;
    int   borderWidth;
    int   posX;
    int   posY;
    int   sizeX;
    int   sizeY;
    void  (*function)(void);
}   button;

//define intVector2 struct
typedef struct s_intVec2
{
    int   x;
    int   y;
}   intVec2;

//define Vector2 struct
typedef struct s_vector2
{
    double  x;
    double  y;
}   Vec2;

//define struct ray
typedef struct s_ray
{
    Vec2 *startPos;
    Vec2 *endPos;
    int     angle;
    float   length;
    char    tag;
    ray  *nextRay;
}   ray;



//define struct t_img
typedef struct s_image
{
    void *img;
    char *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     sizeX;
    int     sizeY;
}   t_image;



//define struct t_map
typedef struct s_map
{
    int     x;
    int     y;
    int     map[20][20];
    int     map_coord[20][20][4];
}   t_map;


//define player
typedef struct s_player
{
    Vec2 *pos;
    int     speed;
    int     dir;
    int     fov;
} t_player;


//define struct t_data
typedef struct s_data
{
    void     *mlx_ptr;
    void     *win_ptr;
    int         sizeX;
    int         sizeY;
    t_map    *map;
    int         mouseX;
    int         mouseY;
    int         oldMouseX;
    ray      *Ray;
    t_image  *current_img;
    t_image  *img2;
    t_image  *last_img;
    t_player *player;
    debug *debug;
}	t_data;


// --------------------DECLARATION OF FUNCTIONS---------------------------------------------------


int mouse_pos(t_data *data);
//map.c
t_map createMap(int x,int y, int offset, int WINDOW_WIDTH, int WINDOW_HEIGHT);
void createMapImg(t_data *data, t_image *img, t_map *map, int WINDOW_WIDTH, int WINDOW_HEIGHT, int offset);
intVec2 getMapPos(t_data *data, int posX, int posY);
int whenClicked(int keycode, t_data *data);
//pixelPut.c
void createRectangle(t_data *data, t_image *img, int x1_, int y1_, int x2_, int y2_,int color);
void createLine(t_data *data, t_image *img, int x1_, int y1_, int x2_, int y2_, int color);
void highlight_box(t_data *data, t_image *img);
void drawSquare(t_data *data, t_image *img, int x1, int y1, int x2, int y2, int color);
void my_mlx_pixel_put(t_data *data, t_image *img, int x, int y, int color);
void clearImage(t_data *data, t_image *img, int WINDOW_WIDTH, int WINDOW_HEIGHT);
void addDebug(t_data *data, char *string);
void emptyDebug(t_data *data);
//player.c
void playerMove(t_data *data, double step);
void drawPlayer(t_data *data, t_image *img, t_player *pl);
//mouse.c
void updatePlayerDir(t_data *data);
//raycasting.c
ray *createRay(t_data *data, Vec2 *start, int angle);
void drawRay(t_data *data, ray *myRay, int color);
ray *createRayList(t_data *data, int angle, ray *OGRay,  ray *ray, int i);
void freeRay(t_data *data, ray *ray);
//button.c
button createButton(int BDcolor, int INcolor, int BDwidth, int posX, int posY, int sizeX, int sizeY, void (*function)(void));
void drawButton(t_data *data, t_image *img, button *butt);
//buttonCommands.c
void buttonSwitch(void);


#endif




