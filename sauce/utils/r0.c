#include "cub69d.h"

/*
	new vars introduced here!

	t_cords	nrst;
	t_cords	edge;
	t_cords	step;
*/
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <math.h>

// # define BLK 64
// # define DtR PIw / 180
// # define PIw 3.1415926536
// # define PIe PIw * 2
// # define PIn PIw / 2
// # define PIs (3 * PIw) / 2

// typedef struct s_cords {
// 	double	x;
// 	double	y;
// }				t_cords;

// typedef struct s_tplr {
// 	double	angl;
// 	t_cords	*cords;
// } t_plr;

// typedef struct s_map {
// 	int		**map;
// 	short	map_s;
// 	short	map_xy;
// }				t_map;

// typedef struct s_table {
// 	t_plr	*plr;
// 	t_map	*map;
// } t_able;

int	my_abs(int n)
{
	if (n >= 0)
		return (n);
	return (n * -1);
}

// void	map_init(t_map *map, short element_sz)
// {
// 	int	y;
// 	int	x;

// 	y = -1;
// 	map->map_xy = (short)sqrt((double)element_sz);
// 	map->map_s = element_sz;
// 	map->map = calloc(map->map_xy, sizeof(int *));
// 	for (int i = 0; i < map->map_xy; i++)
// 		map->map[i] = calloc(map->map_xy, sizeof(int));
// 	while (++y < map->map_xy)
// 	{
// 		x = -1;
// 		while (++x < map->map_xy)
// 		{
// 			if (y == 0 || y == map->map_xy - 1)
// 				map->map[y][x] = 1;
// 			else if (x == 0 || x == 7)
// 				map->map[y][x] = 1;
// 			else
// 				map->map[y][x] = 0;
// 		}
// 	}
// 	map->map[3][1] = 83;
// }

// void	print_map(int **map, int dimes)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (++i < dimes) {
// 		j = -1;
// 		while (++j < dimes) {
// 			printf("%d, ", map[i][j]);
// 		}
// 		printf("\n");
// 	}
// }


bool	h_chk_if_hit_wall(t_able *table, t_cords nrst, t_cords *step, int i)//hor
{
	if (!i && table->map->map[(int)((nrst.y * table->map->map_xy) + nrst.x)])
		return (true);
	step->y = BLK;
	if (table->plr->angl > 0 && table->plr->angl < PIw)
		step->y *= -1;
	step->x = step->y / tan(table->plr->angl);
	if (table->map->map[(int)(nrst.y + table->plr->cords->y) / BLK][(int)(nrst.x + table->plr->cords->x) / BLK])
		return (true);
	return (false);
}

// bool	h2_chk_if_hit_wall(t_able *table, t_cords *nrst, t_cords step)//ver
// {
// 	printf("ang = %f\n", table->plr->angl);
// 	printf("ang = %f\n", tan(table->plr->angl));
// 	printf("nx = %f and in cords => %f\n", nrst->x,(nrst->x / BLK));
// 	printf("ny = %f and in cords => %f\n", nrst->y,(nrst->y / BLK));
// 	printf("px = %f and in cords => %f\n", table->plr->cords->x,(table->plr->cords->x / BLK));
// 	printf("py = %f and in cords => %f\n", table->plr->cords->y,(table->plr->cords->y / BLK) * table->map->map_xy);
// 	printf("npx = %f and in cords => %f\n", nrst->x + table->plr->cords->x,((nrst->x + table->plr->cords->x) / BLK));
// 	printf("npy = %f and in cords => %f\n", nrst->y + table->plr->cords->y,((nrst->y + table->plr->cords->y) / BLK) * table->map->map_xy);
// 	printf("npy nom = %f and in cords => %f\n", nrst->y + table->plr->cords->y,((nrst->y + table->plr->cords->y) / BLK));
// 	printf("part of map[y = %d, x = %d]\n", (int)((nrst->y + table->plr->cords->y) / BLK), (int)((nrst->x + table->plr->cords->x) / BLK));
// 	printf("part of map[%d]\n", table->map->map[(int)(nrst->y + table->plr->cords->y) / BLK][(int)(nrst->x + table->plr->cords->x) / BLK]);
// 	if (table->map->map[(int)(nrst->y + table->plr->cords->y) / BLK][(int)(nrst->x + table->plr->cords->x) / BLK])
// 		return (true);
// 	nrst->x += step.x;
// 	nrst->y += step.y;
// 	return (false);
// }

bool	v2_chk_if_hit_wall(t_able *table, t_cords *nrst, t_cords step, char c)//ver
{
	// printf("%c ang = %f\n", c, tan(table->plr->angl));
	// printf("%c nx = %f and in cords => %f\n", c, nrst->x,(nrst->x / BLK));
	// printf("%c ny = %f and in cords => %f\n", c, nrst->y,(nrst->y / BLK));
	// printf("%c px = %f and in cords => %f\n", c, table->plr->cords->x,(table->plr->cords->x / BLK));
	// printf("%c py = %f and in cords => %f\n", c, table->plr->cords->y,(table->plr->cords->y / BLK) * table->map->map_xy);
	// printf("%c npx = %f and in cords => %f\n", c, nrst->x + table->plr->cords->x,((nrst->x + table->plr->cords->x) / BLK));
	// printf("%c npy = %f and in cords => %f\n", c, nrst->y + table->plr->cords->y,((nrst->y + table->plr->cords->y) / BLK) * table->map->map_xy);
	// printf("%c npy nom = %f and in cords => %f\n", c, nrst->y + table->plr->cords->y,((nrst->y + table->plr->cords->y) / BLK));
	// printf("%c ppart of map[y = %d, x = %d]\n", c, (int)((table->plr->cords->y) / BLK), (int)((table->plr->cords->x) / BLK));
	// printf("%c part of map[y = %d, x = %d]\n", c, (int)((nrst->y + table->plr->cords->y) / BLK), (int)((nrst->x + table->plr->cords->x) / BLK));
	// printf("%c part of map[%d]\n", c, table->map->map[(int)(nrst->y + table->plr->cords->y) / BLK][(int)(nrst->x + table->plr->cords->x) / BLK]);
	if (table->map->map[(int)(nrst->y + table->plr->cords->y) / BLK][(int)(nrst->x + table->plr->cords->x) / BLK])
		return (true);
	nrst->x += step.x;
	nrst->y += step.y;
	return (false);
}

// bool	v_chk_if_hit_wall(t_able *table, t_cords nrst, t_cords *step, int i)//ver
// {
// 	if (!i && table->map->map[(int)((nrst.y * table->map->map_xy) + nrst.x)])
// 		return (true);
// 	step->x = BLK;
// 	if (table->plr->angl > PIn && table->plr->angl < PIs)
// 		step->x *= -1;
// 	// step->y = step->x / tan(table->plr->angl);
// 	step->y = table->plr->cords->y + ((table->plr->cords->y - step->x) * tan(table->plr->angl));
// 	printf("ang = %f\n", table->plr->angl);
// 	printf("ang = %f\n", tan(table->plr->angl));
// 	// printf("%d\n", table->map->map_xy);
// 	printf("x = %f\n", step->x);
// 	printf("y = %f\n", step->y);
// 	if (table->map->map[(int)((step->y * table->map->map_xy) + step->x)])
// 		return (true);
// 	return (false);
// }

void	set_hit_cords(t_cords *hit, t_cords vals)
{
	hit->x = vals.x;
	hit->y = vals.y;
}

bool	reach_first_vert_intersection(t_able *table, t_cords *hit)//using x to chk the columns
{
	t_cords	nrst;
	t_cords	edge;
	t_cords	step;
	int		i;

	i = 0;
	if (table->plr->angl == PIn || table->plr->angl == PIs)
		return (false);
	if (table->plr->angl < PIn || table->plr->angl > PIs)// facing right
		edge.x = ((table->plr->cords->x / BLK) * BLK) + BLK;
	else if (table->plr->angl > PIn && table->plr->angl < PIs)
		edge.x = ((int)(table->plr->cords->x / BLK) * BLK) - 1;
	// printf("edge x = %f\n", edge.x);
	nrst.x = edge.x - table->plr->cords->x; // protect the vals, prob seggs fault
	// printf("nx = %f and in cords => %f\n", nrst.x, (nrst.x / BLK));
	nrst.y = my_abs(nrst.x) * tan(table->plr->angl); // this value will be same for every cycle so better just calculate it once dawg!
	if (table->plr->angl < PIw && table->plr->angl > 0)
		nrst.y *= -1;
	step.x = BLK;
	if (table->plr->angl > PIn && table->plr->angl < PIs)
		step.x *= -1;
	printf("step x => %f\n", step.x);
	printf("step x => %f\n", table->plr->cords->x);
	// step.y = table->plr->cords->y + ((table->plr->cords->x - step.x) * tan(table->plr->angl));
	step.y = BLK * tan(table->plr->angl);
	printf("step y => %f\n", step.y);
	while (!v2_chk_if_hit_wall(table, &nrst, step, 'v') && i < 10) {
		printf("i = %d\n", i);
		i++;
	}
	set_hit_cords(hit, nrst);
	return (true);
}

bool	reach_first_horz_intersection(t_able *table, t_cords *hit)
{
	t_cords	nrst;
	t_cords	edge;
	t_cords	step;
	int		i;

	i = 0;
	if (table->plr->angl == PIw || table->plr->angl == PIe)
		return (false);
	if (table->plr->angl < PIw && table->plr->angl > 0) // facing up
		edge.y = ((table->plr->cords->y / BLK) * BLK) - 1;
	else if (table->plr->angl > PIw && table->plr->angl < PIe)
		edge.y = ((table->plr->cords->y / BLK) * BLK) + BLK;
	nrst.y = edge.y - table->plr->cords->y; // protect the vals, prob seggs fault
	nrst.x = my_abs(nrst.y) * tan(table->plr->angl);
	if (table->plr->angl > PIn && table->plr->angl > PIs)
		nrst.x *= -1;
	step.y = BLK;
	step.x = BLK / tan(table->plr->angl);
	while (!v2_chk_if_hit_wall(table, &nrst, step, 'h'))
		i++;
	set_hit_cords(hit, nrst);
	return (true);
}

void	dda_draw_ray(t_able *table, t_cords hit, int clr)
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
	while (++i)
	{
		my_mlx_pixel_put(&table->mlx->img, (int)xy[0], (int)xy[1], clr);
		printf("drx x = %d\n", xy[0]);
		printf("drx y = %d\n", xy[1]);
		xy[0] += inc_xy[0];
		xy[1] += inc_xy[1];
	}
}

float	distance_of_ray(t_cords *plr, t_cords wll)
{
	return (sqrt(((wll.x - plr->x) * (wll.x - plr->x)) + ((wll.y - plr->y) * (wll.y - plr->y))));
}

void	interseggs(t_able *table)
{
	t_cords	flag;
	t_cords	v_cnt;
	t_cords	h_cnt;
	t_cords	hit;
	double	dist_hiv[3];

	flag.x = 0;
	flag.y = 0;
	if (reach_first_vert_intersection(table, &v_cnt))
		flag.y = 1;
	if (reach_first_horz_intersection(table, &h_cnt))
		flag.x = 1;
	if (flag.x && flag.y)
	{
		dist_hiv[0] = distance_of_ray(table->plr->cords, h_cnt);
		dist_hiv[2] = distance_of_ray(table->plr->cords, v_cnt);
		if (dist_hiv[0] > dist_hiv[2]) {
			dist_hiv[1] = dist_hiv[2];
			hit.y = v_cnt.y;
			hit.x = v_cnt.x;
			printf("apoint of contact x = %f\n", v_cnt.x);
			printf("apoint of contact y = %f\n", v_cnt.y);
		}
		else {
			dist_hiv[1] = dist_hiv[0];
			printf("bpoint of contact x = %f\n", h_cnt.x);
			printf("bpoint of contact y = %f\n", h_cnt.y);
			hit.y = h_cnt.y;
			hit.x = h_cnt.x;
		}
	}
	else if (flag.x) {
		dist_hiv[1] = distance_of_ray(table->plr->cords, h_cnt);
		printf("cpoint of contact x = %f\n", h_cnt.x);
		printf("cpoint of contact y = %f\n", h_cnt.y);
		hit.y = h_cnt.y;
		hit.x = h_cnt.x;
	}
	else {
		dist_hiv[1] = distance_of_ray(table->plr->cords, v_cnt);
		printf("dpoint of contact x = %f\n", v_cnt.x);
		printf("dpoint of contact y = %f\n", v_cnt.y);
		hit.y = v_cnt.y;
		hit.x = v_cnt.x;
	}
	printf("distance_of_ray = %f\n", dist_hiv[1]);
	dda_draw_ray(table, hit, 0x0efad0);
}


void main_ray (t_able *table) {
	// t_able table;
	// t_cords crds;
	// t_plr plr;
	// t_map map;
	// crds.x = 96;
	// crds.y = 224;
	// plr.cords = &crds;
	// plr.angl = PIw - 1;
	// table.plr = &plr;
	// table.map = &map;
	// map_init(&map, 64);
	// print_map(map.map, map.map_xy);
	interseggs(table);
}