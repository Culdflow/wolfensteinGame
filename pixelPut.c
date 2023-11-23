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
t_img createMapImg(t_data *data, t_map *map, int WINDOW_WIDTH, int WINDOW_HEIGHT, int offset)
{
    //create img instance
    t_img img;
    img.img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);

    //creates background
    img = createRectangle(data, offset, offset, WINDOW_WIDTH-offset, WINDOW_HEIGHT-offset, 0x50505050, WINDOW_WIDTH, WINDOW_HEIGHT);

    //creates outline 
    for (int x = offset; x <= WINDOW_WIDTH -offset; x = x + (WINDOW_WIDTH-(offset*2))/map->x) 
        {
            printf("going to next line x = %d\n", x);
            for (int i = offset; i < WINDOW_HEIGHT -offset; i++ )
            {
                my_mlx_pixel_put(&img, x, i, 0x00FF0000);
               
            }

        }
    for (int y = offset; y <= WINDOW_HEIGHT -offset; y = y + (WINDOW_HEIGHT-(offset*2))/map->y)
        {
            printf("going to next line x = %d\n", y);
            for (int i = offset; i < WINDOW_WIDTH-offset; i++ )
            {
                my_mlx_pixel_put(&img, i, y, 0x00FF0000);
               
            }

        }
    return img;
}



//creates a rectangle using 2 positions on the screen
t_img createRectangle(t_data *data, int x1_, int y1_, int x2_, int y2_,int color, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    //initializing variables
    t_img img;
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
    
    //creating img instance
    img.img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
    

    //draws rectangle
    for (int x = X1; x <= X2; x++)
    {
        for (int y = Y1; y <= Y2; y++)
        {
            my_mlx_pixel_put(&img, x, y, color);
        }

    }

    //outputs img_ptr
    return img;

}
