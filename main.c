#include <stdlib.h>
#include <stdio.h>

#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx/mlx.h>
#include "wolfenstein.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define WINDOW_OFFSET 300

#define MLX_ERROR 1

//handles keypresses 
int	handle_keypress(int keysym, t_data *data)
{
    //if escape is pressed close window
    if (keysym == XK_Escape)
    {
        
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL;
    }
    return (0);
}


//is called every frame
int	render(t_data *data)
{
    /* if window has been destroyed, we don't want to put the pixel ! */
    if (data->win_ptr != NULL)
    {
     // mouse_pos(data);
      //if (data->last_img != data->current_img)
      //{
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->current_img->img, 0, 0);      
        data->last_img = data->current_img;
      //}
    }
    return (0);
}

//test print mouse position
int mouse_pos(t_data *data)
{
  int x;
  int y;
  mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &x, &y); 
  data->mouseX = x;
  data->mouseY = y;
}


int	main(void)
{   
    //initialize struct elements
    t_data	data;
    t_map map = createMap(10, 10, WINDOW_OFFSET, WINDOW_WIDTH, WINDOW_HEIGHT);
       
    //test for map
/*    printf("map x = %d\n", map.x);
    printf("map y = %d\n", map.y);
    for (int x=0;x<map.x;x++)
    {
        for (int y=0;y<map.y;y++)
        {
          for (int o = 0; o < 4; o++)
          {
            printf("%d", map.map_coord[x][y][o]);
          }
          printf("\n");
        }
        printf("\n");
    } */
    
    //if error is detected in mlx_ptr print out MLX ERROR
    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (MLX_ERROR);

    //create new window in data.win_ptr
    data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");

    //if error is detected in win_ptr print out MLX ERROR
    if (data.win_ptr == NULL)
    {
        free(data.win_ptr);
        return (MLX_ERROR);
    }
    

    //create image in img
    t_img img;
    img.img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    createMapImg(&data, &img, &map, WINDOW_WIDTH, WINDOW_HEIGHT,WINDOW_OFFSET);
    createLine(&data, &img, 0,0,0,1000,0x0000FF00, WINDOW_WIDTH, WINDOW_HEIGHT);

    data.last_img = NULL;
    data.current_img = &img;


    /* Setup hooks */ 
    mlx_loop_hook(data.mlx_ptr, &render, &data);
    mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_loop(data.mlx_ptr);

    /* we will exit the loop if there's no window left, and execute this code */
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
}
