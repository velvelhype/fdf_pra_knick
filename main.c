#include "fdf.h"

int deal_key(int key, fdf *data)
{
    ft_printf("%d\n", key);
    
   if(key == 126)
        data->shift_y -= 40;
    if(key == 125)
        data->shift_y += 40;
   if(key == 123)
        data->shift_x -= 40;
    if(key == 124)
        data->shift_x += 40;

    mlx_clear_window(data->mlx_ptr, data->win_ptr);

    draw(data);
    return (0) ;
}

int main(int argc, char **argv)
{
    fdf *data;

    data = (fdf*)malloc(sizeof(fdf));
    read_file(argv[1], data);   
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, 600, 600, "FDF");
    data->zoom = 30;

    data->shift_x = 100;
    data->shift_y = 100;

    draw(data);
    mlx_key_hook(data->win_ptr, deal_key, data);
    mlx_loop(data->mlx_ptr);
}
