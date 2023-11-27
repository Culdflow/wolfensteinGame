
#compiler
CC = gcc

#flags
CFLAGS = -lmlx -L /usr/include/mlx -lXext -lX11 -Wincompatible-pointer-types

all:
	$(CC) -o main main.c pixelPut.c map.c $(CFLAGS)
