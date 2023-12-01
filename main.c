#include <stdlib.h>
#include <stdio.h>

#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx/mlx.h>
#include <mlx/mlx_int.h>
#include "wolfenstein.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define WINDOW_OFFSET 100

#define MLX_ERROR 1

//handles keypresses 
int	handle_keypress(int keysym, t_data *data)
{
    //if escape is pressed close window
    switch (keysym)
    {
      case XK_Escape:
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL;
        break;

      case XK_q:
        data->player->dir -= 1;
        break;

      case XK_d:
        data->player->dir += 1;
        break;
      
      case XK_z:
        playerMove(data, 10);
        break;

      case XK_s:
        playerMove(data, -10);
        break;
    }
    return (0);
}


//is called every frame
int	render(t_data *data)
{
    /* if window has been destroyed, we don't want to put the pixel ! */
    if (data->win_ptr != NULL)
    {
      clearImage(data->current_img, WINDOW_WIDTH, WINDOW_HEIGHT);
      //track mouse position
      mouse_pos(data);
      createMapImg(data, data->current_img, data->map, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_OFFSET); 
      highlight_box(data, data->current_img, WINDOW_WIDTH, WINDOW_HEIGHT);
      drawPlayer(data, data->current_img, data->player); 
      //if image did not change from last frame don't print it to the screen
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
    t_player player;
    player.posX = 50;
    player.posY = 50;
    player.dir = 0;
    data.player = &player;
    t_map map = createMap(5, 5, WINDOW_OFFSET, WINDOW_WIDTH, WINDOW_HEIGHT);
    data.map = &map;

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
    t_image img;
    t_image img2;
    img.img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (img.img == NULL)
      return (MLX_ERROR);
    //img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    //createMapImg(&data, &img, &map, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_OFFSET);
    img2.img = mlx_xpm_file_to_image(data.mlx_ptr, "./images/Image.xpm", &img2.sizeX, &img2.sizeY);
    if (img2.img == NULL)
      return (MLX_ERROR);
    img2.addr = mlx_get_data_addr(img2.img, &img2.bits_per_pixel, &img2.line_length, &img2.endian);

 
    data.last_img = NULL;
    data.current_img = &img;
    data.img2 = &img2;
    

    //mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, &img.img, 0, 0);   
    /* Setup hooks */ 
    mlx_loop_hook(data.mlx_ptr, &render, &data);
    mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_loop(data.mlx_ptr);

    /* we will exit the loop if there's no window left, and execute this code */
    mlx_destroy_display(data.mlx_ptr);
    printf("fart\n");
    free(data.mlx_ptr);
}
