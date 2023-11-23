
#compiler
CC = gcc

#flags
CFLAGS = -lmlx -L /usr/include/mlx -lXext -lX11

all:
	$(CC) -o main main.c pixelPut.c map.c $(CFLAGS)
