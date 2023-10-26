/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:48:55 by aikram            #+#    #+#             */
/*   Updated: 2023/10/26 18:04:22 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub69d.h"

int ft_close(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit (0); //make sure to clear em memmo
	// return (0);
}

void	handle_movements(t_able *table)
{
	if (table->keys[3] && table->keys[0]) // w a
		plyr_rt_and_mv(table, 0, 1);
	else if (table->keys[3] && table->keys[2]) // w d
		plyr_rt_and_mv(table, 1, 1);
	else if (table->keys[1] && table->keys[0]) // s a
		plyr_rt_and_mv(table, 0, 0);
	else if (table->keys[1] && table->keys[2]) // s d
		plyr_rt_and_mv(table, 1, 0);
	else if (table->keys[0]) // a
		 plyr_rrt(table);
	else if (table->keys[1]) // s
		plyr_mv_backward(table);
	else if (table->keys[2]) // d
		plyr_rt(table);
	else if (table->keys[3]) // w
		plyr_mv_forward(table);
	// if (table->keys[0] || table->keys[1] || table->keys[2] || table->keys[3])
	// 	main_ray(table);
}

int	handle_keypress(int keysym, t_able *table)
{
	// printf("tangl %f\n", table->plr->angl);
	// printf("%d\n", keysym);
	if (keysym == 53) {
		mlx_destroy_window(table->mlx->mlx_ptr, table->mlx->win_ptr);
		exit (0); //make sure to clear em memmo
	}
	else if (keysym == 0)
		table->keys[0] = 1;
	else if (keysym == 1)
		table->keys[1] = 1;
	else if (keysym == 2)
		table->keys[2] = 1;
	else if (keysym == 13)
		table->keys[3] = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_able *table)
{
	// printf("tangl %f\n", table->plr->angl);
	if (keysym == 0)
		table->keys[0] = 0;
	else if (keysym == 1)
		table->keys[1] = 0;
	else if (keysym == 2)
		table->keys[2] = 0;
	else if (keysym == 13)
		table->keys[3] = 0;
	return (0);
}

int	handle_events(t_able *table)// 2.0
{
	// printf("aangl %f\n", table->plr->cords.x);
	// printf("aangl %f\n", table->plr->angl);
	// printf("addr %p\n", table);
	table->chk++; //tmp
	handle_movements(table);
	blayer_movement(table);
	create_new_image(table, true);
	draw_map(table);
	blayer_movement(table);
	if (table->chk < 20) //tmp
		display_image(table);
	mlx_put_image_to_window(table->mlx->mlx_ptr, table->mlx->win_ptr, table->mlx->img->img_ptr, 0, 0);
	return (0);
}

void	event_handler(t_able *table)
{
	// printf("addr %p\n", table);
	// printf("zangl %f\n", table->plr->angl);
	mlx_loop_hook(table->mlx->mlx_ptr, (int (*)(void *))handle_events, table);// u can keep track of return vals here!
	mlx_hook(table->mlx->win_ptr, 03, 1L<<1, &handle_keyrelease, &table);
	mlx_hook(table->mlx->win_ptr, 02, 1L<<0, &handle_keypress, &table);
	mlx_hook(table->mlx->win_ptr, 17, 0, ft_close, &table->mlx);
	mlx_loop(table->mlx->mlx_ptr);
}


// void	init_raycast(t_info *info, int x)
// {
// 	info->raycast.camera = 2 * x / (double)(info->width) - 1;
// 	info->raycast.rpos.x = info->pos.x;
// 	info->raycast.rpos.y = info->pos.y;
// 	info->raycast.rdir.x = info->raycast.dir.x + info->raycast.plane.x
// 		* info->raycast.camera;
// 	info->raycast.rdir.y = info->raycast.dir.y + info->raycast.plane.y
// 		* info->raycast.camera;
// 	info->raycast.rmap.x = (int)info->raycast.rpos.x;
// 	info->raycast.rmap.y = (int)info->raycast.rpos.y;
// 	info->raycast.rdisd.x = fabs(1 / info->raycast.rdir.x);
// 	info->raycast.rdisd.y = fabs(1 / info->raycast.rdir.y);
// 	printf("e ddist.x %f\n", info->raycast.rdisd.x);
// 	printf("e ddist.y %f\n", info->raycast.rdisd.y);
// 	info->raycast.hit = 0;
// }
