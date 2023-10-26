int	events(t_able *table)
{
	table->win_ptr = mlx_new_window(table->mlx_ptr, table->width,
			table->height, "Cub3D");
	if (!table->win_ptr)
		return (MLX_FAIL);
	mlx_hook(table->win_ptr, 17, STRUCTURENOTIFYMASK, deal_exit, table);
	mlx_hook(table->win_ptr, KEYPRESS, KEYPRESSMASK, key_hit, table);
	mlx_hook(table->win_ptr, KEYRELEASE, KEYRELEASEMASK, key_release, table);
	table->error = mlx_loop_hook(table->mlx_ptr, fn_run, table);
	if (table->error != SUCCESS)
		return (table->error);
	mlx_loop(table->mlx_ptr);
	return (SUCCESS);
}

					|
					V

static int	fn_run(t_able *table)
{
	free_img(table);
	table->img = fn_new_image(table, table->width, table->height);
	if (table->img == NULL)
		return (IMG_FAIL);
	player_move(table);
	fn_display_screen(table);
	mlx_put_image_to_window(table->mlx_ptr, table->win_ptr, table->img->img_ptr, 0,
		0);
	return (SUCCESS);
}

					|
					V


t_img	*fn_new_image(t_able *table, int width, int height)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img_ptr = mlx_new_image(table->mlx_ptr, width, height);
	if (!img->img_ptr)
		return (NULL);
	img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->img_data)
		return (NULL);
	img->width = width;
	img->height = height;
	return (img);
}

					|
					V

int	fn_display_screen(t_able *table)
{
	int	x;

	x = 0;
	while (x < table->width - 1)
	{
		init_raycast(table, x);
		direction_ray(table);
		hit_ray(table);
		size_ray(table);//should do! and onwards!!!
		wall_textur(table);
		table->error = display_col(table, x++);
		if (table->error != SUCCESS)
			return (table->error);
		table->raycast.zbuffer[x] = table->raycast.dist;
	}
	table->error = init_sprite(table);
	if (table->error != SUCCESS)
		return (table->error);
	return (SUCCESS);
}

					|
					V

