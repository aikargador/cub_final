/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:35:10 by aikram            #+#    #+#             */
/*   Updated: 2023/10/26 17:19:41 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub69d.h"

void	annihilate_img(t_able *table)
{
	if (table->mlx->img)
	{
		mlx_destroy_image(table->mlx->mlx_ptr, table->mlx->img->img_ptr);
		free(table->mlx->img);
		table->mlx->img = NULL;
	}
}

// bool	free_and_return()

int	display_image(t_able *table)
{
	int	w;

	w = -1;
	while (++w < WDH)
	{
		// (void)table;
		main_ray(table, w);
		// main_ray(table);
		// ray_dir(table);
		// ray_contact(table);
	}
	return 0;
}

bool	create_new_image(t_able *table, bool destroy)
{
	if (destroy)
		annihilate_img(table);
	// table->mlx->win_ptr = mlx_new_window(table->mlx->mlx_ptr, \
	// WDH, HGT, "cub69d");
	// if (!table->mlx->win_ptr)
	// {
	// 	free(table->mlx->win_ptr);
	// 	return (false);
	// }//protect the varz below!
	table->mlx->img = ft_calloc(1, sizeof(t_img));
	if (!table->mlx->img)
		return 69;//call error and exit func!
	table->mlx->img->img_ptr = mlx_new_image(table->mlx->mlx_ptr, WDH, HGT);
	if (!table->mlx->img->img_ptr)
		return 69;//call error and exit func!
	table->mlx->img->addr = mlx_get_data_addr(table->mlx->img->img_ptr,\
	&table->mlx->img->bits_per_pixel, &table->mlx->img->line_length, \
	&table->mlx->img->endian);
	if (!table->mlx->img->addr)
		return 69;//call error and exit func!
	return (true);
}

// t_img	*fn_new_image(t_able *table, int width, int height)
// {
// 	t_img	*img;

// 	img = malloc(sizeof(t_img));
// 	if (!img)
// 		return (NULL);
// 	img->img_ptr = mlx_new_image(table->mlx_ptr, width, height);
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


// info->error = mlx_loop_hook(info->mlx_ptr, fn_run, info);
// if (info->error != SUCCESS)
// 	return (info->error);