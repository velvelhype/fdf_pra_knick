#include "fdf.h"
#include <math.h>

#define MAX1(a, b) (a > b ? a : b)
#define MOD(a) ((a < 0) ?  -a : a)

float   mod(float i)
{
    return (i < 0) ? -i : i;
}

void    isometric(float *x, float *y, int z, fdf *data)
{
    // *x = (*x - *y) * cos(data->rotation);
    *x = (*x - *y) * cos(data->rotation) ;
    *y = (*x + *y) * sin(data->rotation) - z;
    // must change
    // isometric(&x, &y, z, data);
    // isometric(&x1, &y1, z1, data);
}

void    breseham(float x, float y, float x1, float y1, fdf *data)
{
    float   x_step;   
    float   y_step;
    int max;
    int z;
    int z1;

    z = data->z_matrix[(int)y][(int)x];
    z1 = data->z_matrix[(int)y1][(int)x1];

    x *= data->zoom;
    y *= data->zoom;
    x1 *= data->zoom;
    y1 *= data->zoom;

    data->color = (z || z1) ? 0x00ff00 : 0xffffff;

    isometric(&x, &y, z, data);
    isometric(&x1, &y1, z1, data);

    x += data->shift_x;
    y += data->shift_y;
    x1 += data->shift_x;
    y1 += data->shift_y;

    x_step = x1 - x;
    y_step = y1 - y;  
    max = MAX(MOD(x_step), MOD(y_step));
    x_step /= max; 
    y_step /= max;

    while((int)(x - x1) || (int)(y - y1))
    {
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->color);
        x += x_step;
        y += y_step;
    }
}

void    draw(fdf *data)
{
    int x;
    int y;

    y = 0;
    while (y < data->height )
    {
        x = 0;
        while(x < data->width )
        {
            if(x < data->width - 1)
                breseham(x, y, x+1, y, data);
            if(y < data->height -1)
                breseham(x, y, x, y+1, data);
            x++;
        }
        y++;
    }
}