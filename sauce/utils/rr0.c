#include "cub69d.h"

int	my_abs(int n)
{
	if (n >= 0)
		return (n);
	return (n * -1);
}

void	draw_ray(t_able *table, t_cords hit, int clr)
{
	int		i;
	int		xy[2];
	int		steps;
	int		d_xy[2];
	double	inc_xy[2];

	d_xy[0] = hit.x - table->plr->cords->x;
	d_xy[1] = hit.y - table->plr->cords->y;
	if (my_abs(d_xy[0]) > my_abs(d_xy[1]))
		steps = my_abs(d_xy[0]);
	else
		steps = my_abs(d_xy[1]);
	inc_xy[0] = d_xy[0] / (double)steps;
	inc_xy[1] = d_xy[1] / (double)steps;
	xy[0] = table->plr->cords->x;
	xy[1] = table->plr->cords->y;
	i = -1;
		// printf("whaaat pixkel\n");
	while (++i < steps)
	{
		// printf("whaaat pixkel\n");
		my_mlx_pixel_put(table->mlx->img, (int)xy[0], (int)xy[1], clr);
		xy[0] += inc_xy[0];
		xy[1] += inc_xy[1];
	}
}

double	ray_dist(t_cords *plr, t_cords *cnt)
{
	double	sx;
	double	sy;

	sx = ((cnt->x - plr->x) * (cnt->x - plr->x));
	sy = ((cnt->y - plr->y) * (cnt->y - plr->y));
	return (sqrt((sx + sy)));
}

void	both_intersect(t_able *table, t_cords *flag_ih, t_cords *cnt_hv)
{
	double	dist_hv[2];

	dist_hv[0] = ray_dist(table->plr->cords, &cnt_hv[0]);
	dist_hv[1] = ray_dist(table->plr->cords, &cnt_hv[1]);
	if (dist_hv[0] > dist_hv[1])
		flag_ih[1].x = 1;
	else
		flag_ih[1].y = 1;
}

bool	chk_up(double angle)
{
	if (angle < PIw)
		return (true);
	return (false);
}

bool	chk_down(double angle)
{
	if (angle > PIw)
		return (true);
	return (false);
}

bool	chk_right(double angle)
{
	if (angle < PIn || angle > PIs)
		return (true);
	return (false);
}

bool	chk_left(double angle)
{
	if (angle > PIn && angle < PIs)
		return (true);
	return (false);
}

bool	wall_cnt(t_able *table, t_cords *nrst, t_cords step, char c)//ver
{
	printf("%c step.y %d\n", c, (int)my_abs(step.y));
	printf("%c step.x %d\n", c, (int)my_abs(step.x));
	printf("%c part of nrst[%f][%f]\n", c, nrst->y, nrst->x);
	printf("%c part of plr[%f][%f]\n", c, table->plr->cords->y, table->plr->cords->x);
	printf("%c part of map[%d][%d]\n", c, (int)(nrst->y + table->plr->cords->y)\
	, (int)(nrst->x + table->plr->cords->x));
	printf("%c part of map[y = %d, x = %d] = %d\n", c, (int)((nrst->y + table->plr->cords->y) / BLK) \
	, (int)((nrst->x + table->plr->cords->x) / BLK), table->map->map[(int)((nrst->y + table->plr->cords->y) / BLK )]\
	[(int)((nrst->x + table->plr->cords->x) / BLK)]);
	printf("angle = %f\n", table->plr->angl);
	if (table->map->map[(int)((nrst->y + table->plr->cords->y) / BLK )]\
	[(int)((nrst->x + table->plr->cords->x) / BLK)] == 1)
		return (false);
	nrst->x += step.x;
	nrst->y += step.y;
	return (true);
}

void	set_hit_cords(t_cords *hit, t_cords vals)
{
	hit->x = vals.x;
	hit->y = vals.y;
}

bool	chk_limit(double cord, char c)
{
	cord /= 64;
	printf("%c cord = %f\n", c, cord);
	// double a = 7 - my_abs(cord);
	if (cord > 7 || cord < 0)
		return (false);
	return (true);
}

bool	vert_intersect(t_able *table, t_cords *hit)
{
	t_cords	nrst;
	t_cords	edge;
	t_cords	step;

	if (table->plr->angl == PIs || table->plr->angl == PIn)
		return (false);
	edge.x = (((int)table->plr->cords->x / BLK) * BLK) + BLK;
	step.x = BLK;
	if (chk_left(table->plr->angl)) // facing up
	{
		// printf("\n\nwat\n\n");
		step.x *= -1;
		edge.x = (((int)table->plr->cords->x / BLK) * BLK) - 1;
	}
	nrst.x = edge.x - table->plr->cords->x;
	step.y = my_abs(BLK) * tan(table->plr->angl);
	nrst.y = (int)my_abs(nrst.x) * tan(table->plr->angl);
	printf("v step.y %f\n", step.y);
	if (chk_down(table->plr->angl))
	{
		nrst.y *= -1;
		step.y *= -1;
	}
	// while (!wall_cnt(table, &nrst, step, 'v'))
	// 	if (!chk_limit(table->plr->cords->y + nrst.y, 'v'))
	bool ret_val = true;
	bool cont = true;
	while (ret_val && cont)
	{
		ret_val = chk_limit(table->plr->cords->y + nrst.y, 'v');
		if (!ret_val)
			return (false);
		cont = wall_cnt(table, &nrst, step, 'v');
	}
	set_hit_cords(hit, nrst);
	return (true);
}

bool	hort_intersect(t_able *table, t_cords *hit)
{
	t_cords	nrst;
	t_cords	edge;
	t_cords	step;

	if (table->plr->angl == PIw || table->plr->angl == PIe || !table->plr->angl)
		return (false);
	edge.y = (((int)table->plr->cords->y / BLK) * BLK) + BLK;
	step.y = BLK;
	if (chk_up(table->plr->angl)) // facing up
	{
		step.y = -BLK;
		edge.y = (((int)table->plr->cords->y / BLK) * BLK) - 1;
	}
	nrst.y = edge.y - table->plr->cords->y;
	nrst.x = (int)my_abs(nrst.y) / tan(table->plr->angl);
	step.x = BLK / tan(table->plr->angl);
	if (chk_left(table->plr->angl))
	{
		nrst.x *= -1;
		step.x *= -1;
	}
	// while (chk_limit(table->plr->cords->x + nrst.x, 'h'))
	// 	if (!wall_cnt(table, &nrst, step, 'h'))
	// while (!wall_cnt(table, &nrst, step, 'h'))
	// 	if (!chk_limit(table->plr->cords->x + nrst.x, 'h'))
			// return (false);
	bool ret_val = true;
	bool cont = true;
	while (ret_val && cont)
	{
		ret_val = chk_limit(table->plr->cords->x + nrst.x, 'h');
		if (!ret_val)
			return (false);
		cont = wall_cnt(table, &nrst, step, 'h');
	}
	set_hit_cords(hit, nrst);
	return (true);
}

void	intersections(t_able *table)
{
	t_cords	flag_ih[2];
	t_cords	cnt_hv[2];

	flag_ih[0].x = 0;
	flag_ih[0].y = 0;
	flag_ih[1].x = 0;
	flag_ih[1].y = 0;
	if (hort_intersect(table, &cnt_hv[0]))
		flag_ih[0].y = 1;
	if (vert_intersect(table, &cnt_hv[1]))
		flag_ih[0].x = 1;
	if (flag_ih[0].y && flag_ih[0].y)
		both_intersect(table, flag_ih, cnt_hv);
	else if (flag_ih[0].x)
		flag_ih[1].x = 1;
	else
		flag_ih[1].y = 1;
	if (flag_ih[1].y) {
		printf("\ndry111\n\n");
		draw_ray(table, cnt_hv[0], 0x0011); // last param is just clr remove it later
	}
	else {
		printf("\ndry222\n\n");
		draw_ray(table, cnt_hv[1], 0x0011);
	}
}

// void	main_ray(t_able *table)
// {
// 	(void)table;
// 	printf("\n\nstart\n\n");
// 	intersections(table);
// 	printf("\n\nend\n\n");
// }
