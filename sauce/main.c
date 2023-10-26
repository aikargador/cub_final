#include "cub69d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

bool	allocate_plr(t_plr *plr) // chk if allocation failed and return false!
{
	plr->cords = ft_calloc(1, sizeof(t_cords));
	plr->del = ft_calloc(1, sizeof(t_cords));
	return (true);
}

int main() {
	t_able	table;
	t_mlx	mlx;
	t_map	map;

	
	table.mlx = &mlx;
	table.map = &map;
	table.plr = ft_calloc(1, sizeof(t_plr));
	table.keys[0] = 0;
	table.keys[1] = 0;
	table.keys[2] = 0;
	table.keys[3] = 0;
	table.blk_sz = 64;
	table.mv_speed = 1;
	table.chk = 0;

	allocate_plr(table.plr);
	table.plane = ft_calloc(1, sizeof(t_cords));
	table.ray = ft_calloc(1, sizeof(t_ray));
	table.plane->x = 0;
	table.plane->y = 0.66;
	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame
	table.plane->x = 0;
	table.plane->y = 0.66;
	table.plane->x = -1;
	table.plane->y = 0;

	mlx.mlx_ptr = mlx_init();
	create_new_image(&table, false);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WDH, HGT, "cub69d");
	if (!mlx.win_ptr)
	{
		free(mlx.win_ptr);
		return (1);//before that destroy everything else!
	}
	// mlx.img->img_ptr = mlx_new_image(mlx.mlx_ptr, WDH, HGT);
	// mlx.img->addr = mlx_get_data_addr(mlx.img->img_ptr, &mlx.img->bits_per_pixel, &mlx.img->line_length, &mlx.img->endian);
	map_init(&map, table.blk_sz);
	draw_map(&table);
	blayer_blacement(&table);
	printf("angl %f\n", table.plr->angl);
	event_handler(&table);
}

// t_img	*fn_new_image(t_info *info, int width, int height)
// {
// 	t_img	*img;

// 	img = malloc(sizeof(t_img));
// 	if (!img)
// 		return (NULL);
// 	img->img_ptr = mlx_new_image(info->mlx_ptr, width, height);
// 	if (!img->img_ptr)
// 		return (NULL);
// 	img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp,
// 			&img->size_line, &img->endian);
// 	if (!img->img_data)
// 		return (NULL);
// 	img->width = width;
// 	img->height = height;
// 	return (img);
// }

// static int	fn_run(t_info *info)
// {
// 	free_img(info);
// 	info->img = fn_new_image(info, info->width, info->height);
// 	if (info->img == NULL)
// 		return (IMG_FAIL);
// 	player_move(info);
// 	fn_display_screen(info);
// 	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img->img_ptr, 0,
// 		0);
// 	return (SUCCESS);
// }

// int	events(t_info *info)
// {
// 	info->win_ptr = mlx_new_window(info->mlx_ptr, info->width,
// 			info->height, "Cub3D");
// 	if (!info->win_ptr)
// 		return (MLX_FAIL);
// 	mlx_hook(info->win_ptr, 17, STRUCTURENOTIFYMASK, deal_exit, info);
// 	mlx_hook(info->win_ptr, KEYPRESS, KEYPRESSMASK, key_hit, info);
// 	mlx_hook(info->win_ptr, KEYRELEASE, KEYRELEASEMASK, key_release, info);
// 	info->error = mlx_loop_hook(info->mlx_ptr, fn_run, info);
// 	if (info->error != SUCCESS)
// 		return (info->error);
// 	mlx_loop(info->mlx_ptr);
// 	return (SUCCESS);
// }
