
#compiler
CC = gcc

#flags
CFLAGS = -lm -lmlx -L /usr/include/mlx -lXext -lX11 -Wincompatible-pointer-types

all:
	$(CC) -o main main.c pixelPut.c map.c player.c $(CFLAGS)
