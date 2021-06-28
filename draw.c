#include "fdf.h"
#include <math.h>

#define MAX1(a, b) (a > b ? a : b)
#define MOD(a) ((a < 0) ?  -a : a)

t_color col_step_forward(t_color col, t_color col_step)
{
    col.red += col_step.red;
    col.green += col_step.green;
    col.blue += col_step.blue;

    return  col;
}

t_color rgb_open(int color)
{
    t_color back;

    back.red = color / (256 * 256);
    color -= back.red * 256 * 256;
    back.green = color / (256);
    color -= back.green * 256;
    back.blue = color;

    return back;
}

t_color col_step_make(int start_col, int end_col, int max)
{
    t_color col_step;
    t_color open_start = rgb_open(start_col);
    t_color open_end = rgb_open(end_col);
    col_step.red = (open_end.red - open_start.red) / max;
    col_step.green = (open_end.green - open_start.green) / max;
    col_step.blue = (open_end.blue - open_start.blue) / max;

    return col_step;
}

int rgb_zip(t_color col)
{
	int ret;
	ret = 0;
	ret += col.red * 256 * 256;
	ret += col.green * 256;
	ret += col.blue;

	return (ret);
}

float   mod(float i)
{
    return (i < 0) ? -i : i;
}

void    isometric(float *x, float *y, int z, fdf *data)
{
    *x = (*x - *y) * cos(data->rotation) ;
    *y = (*x + *y) * sin(data->rotation)  - z;
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

    t_color start = rgb_open(0xffffff);
    t_color end = rgb_open(0xffffff);

    data->color = (z || z1) ? 0x00ff00 : 0xffffff;
    if (z > z1)
        start = rgb_open(0x00ff00);
    else if (z1 > z)
        end = rgb_open(0x00ff00);

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
    t_color col_step = col_step_make(rgb_zip(start), rgb_zip(end), max);

    if (z - z1)
    {
        while((int)(x - x1) || (int)(y - y1))
        {
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, rgb_zip(start));
            x += x_step;
            y += y_step;
            start = col_step_forward(start, col_step);
            data->color += rgb_zip(start);
        }
    }
    else
    {
        while((int)(x - x1) || (int)(y - y1))
        {
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->color);
            x += x_step;
            y += y_step;
        }
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