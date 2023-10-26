/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:21:47 by aikram            #+#    #+#             */
/*   Updated: 2023/10/26 18:04:45 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub69d.h"

/* d */
void	plyr_rt(t_able *table)
{
	table->plr->angl -= 0.1;
	if (table->plr->angl < 0)
		table->plr->angl += PIe;
	table->plr->del->x = cos(table->plr->angl) * table->mv_speed;
	table->plr->del->y = sin(table->plr->angl) * table->mv_speed;
	return ;
}

/* a */
void	plyr_rrt(t_able *table)
{
	table->plr->angl += 0.1;
	if (table->plr->angl > PIe)
		table->plr->angl -= PIe;
	table->plr->del->x = cos(table->plr->angl) * table->mv_speed;
	table->plr->del->y = sin(table->plr->angl) * table->mv_speed;
	return ;
}

// void	player_rotate(t_able *table)
// {
// 	double	dir_vec;
// 	double	plane;

// 	dir_vec = table->plr->del->x;
// 	plane = table->plane->x;
// 	table->plr->del->x = table->plr->del->x * cos(table->plr->angl * 0.05)
// 		- table->plr->del->y * sin(table->plr->angl * 0.05);
// 	table->plr->del->y = dir_vec * sin(table->plr->angl * 0.05)
// 		+ table->plr->del->y * cos(table->plr->angl * 0.05);
// 	table->plane->x = table->plane->x * cos(table->plr->angl * 0.05)
// 		- table->plane->y * sin(table->plr->angl * 0.05);
// 	table->plane->y = plane * sin(table->plr->angl * 0.05)
// 		+ table->plane->y * cos(table->plr->angl * 0.05);
// }

bool	plyr_mv_forward(t_able *table)
{
	int pp[2];
	pp[0] = (int)((table->plr->cords->y + table->plr->del->y \
	* table->mv_speed) / BLK);
	pp[1] = (int)((table->plr->cords->x + table->plr->del->x \
	* table->mv_speed) / BLK);
	printf("map[%d][%d] = %d\n", pp[0], pp[1], table->map->map[pp[0]][pp[1]]);
	if (table->map->map[pp[0]][pp[1]] == 1)
		return (false);
	printf("did not return\n");
	printf("delx %f\n", table->plr->del->x);
	printf("dely %f\n", table->plr->del->y);
	printf("plrx %f\n", table->plr->cords->x);
	printf("plry %f\n", table->plr->cords->y);
	table->plr->cords->x += table->plr->del->x * table->mv_speed;
	table->plr->cords->y -= table->plr->del->y * table->mv_speed;
	return (true);
}

bool	plyr_mv_backward(t_able *table)
{
	int pp[2];
	pp[0] = (int)((table->plr->cords->y - table->plr->del->y \
	* table->mv_speed) / BLK);
	pp[1] = (int)((table->plr->cords->x - table->plr->del->x \
	* table->mv_speed) / BLK);
	printf("map[%d][%d] = %d\n", pp[0], pp[1], table->map->map[pp[0]][pp[1]]);
	if (table->map->map[pp[0]][pp[1]] == 1)
		return (false);
	printf("did not return\n");
	table->plr->cords->x -= table->plr->del->x * table->mv_speed;
	table->plr->cords->y += table->plr->del->y * table->mv_speed;
	return (true);
}

bool	plyr_rt_and_mv(t_able *table, int rt, int mv)
{
	if (rt)
		plyr_rt(table);
	else
		plyr_rrt(table);
	(void)rt;
	// player_rotate(table);
	if (mv)
		return (plyr_mv_forward(table));
	else
		return (plyr_mv_backward(table));
}

/*
	west: west forward and backward working!
	


*/