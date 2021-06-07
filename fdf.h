#ifndef FDF_H
# define FDF_H

#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include <stdio.h>

typedef struct 
{
    int width;
    int height;
    int **z_matrix;
    int zoom;
    int color;

    void *mlx_ptr;
    void *win_ptr;
}       fdf;

void    read_file(char *file_name, fdf *data);

void    breseham(int x, int y, int x1, int y1, fdf *data);

void    draw(fdf *data);

#endif