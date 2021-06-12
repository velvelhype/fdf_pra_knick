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
    if(key == 18)
        data->rotation += 0.1;
    if(key == 19)
        data->rotation -= 0.1;
    //add escape
    mlx_clear_window(data->mlx_ptr, data->win_ptr);

    draw(data);
    return (0) ;
}

// int main(int argc, char **argv)
// {
//     fdf *data;

//     data = (fdf*)malloc(sizeof(fdf));
//     read_file(argv[1], data);   
//     data->mlx_ptr = mlx_init();
//     data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
//     data->zoom = 20;

//     data->shift_x = 100;
//     data->shift_y = 100;
//     data->rotation = 1;

//     draw(data);
//     mlx_key_hook(data->win_ptr, deal_key, data);
//     mlx_loop(data->mlx_ptr);
// }

int main(int argc, char **argv)
{
    fdf *data;
    data = (fdf*)malloc(sizeof(fdf));
    read_file(argv[1], data);
    for(int i = 0; i < data->height; i++)
    {
        for(int j = 0; j < data->width; j++)
            ft_printf("%3d", data->z_matrix[i][j]);
    printf("\n");
    }
}