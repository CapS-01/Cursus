#include "../minilibx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include "so_long.h"
#include <X11/keysym.h>
/*
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
*/
/*
typedef struct s_graph
{
	void	*wall;
	void	*empty;
	void	*collect;
	void	*exit;
	void    *player;
	void	*winner;
} t_graph;
*/
typedef struct	i_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	img_data;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
//	t_graph	*graph;
} t_data;
 
int on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}
void	my_mlx_pixel_put(img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int on_keypress(int keysym, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\\n", keysym);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	(void)data;
	printf("%d\n", keycode);
/*
	if (keycode == 45)
	       	printf("Hello from key_hook!\n");
	if (keycode == 13)
		printf("W\n");
	else if (keycode == 2)
		printf("S\n");
	else if (keycode == 5)
		printf("A\n");
	printf("\nHere_Key_Event");
*/	return (0);
} 
int main(void)
{
	t_data data;
	img_data	image;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
        	printf("2_WHATTT");	
		return (1);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "hi :)");
	image.img = mlx_new_image(data.mlx_ptr, 200, 200);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	my_mlx_pixel_put(&image, 200, 200, 0x00FF0000);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, image.img, 0, 0);
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
     	// MLX Hook	
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
