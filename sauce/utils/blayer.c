#include "cub69d.h"

void	blayer_blacement(t_able *table) { // ternary usage!
	int		i;

	for (i = 0; i < 64; i++)
		if (ft_strchr("NSEW", table->map->map[i / 8][i % 8]))
			break ;
	int	iy = i / 8;
	int	ix = i - (8 * iy);
	table->plr->cords->y = ((double)iy * BLK) + (BLK / 2);
	table->plr->cords->x = ((double)ix * BLK) + (BLK / 2);
	printf("y => %f\n", table->plr->cords->y);
	printf("x => %f\n", table->plr->cords->x);
	// table->plr->angl = (table->map->map[iy][ix] == 69) ? 0 : (table->map->map[iy][ix] == 83) ? \
	// PIs : (table->map->map[iy][ix] == 87) ? PIw : PIn;
	if (table->map->map[iy][ix] == 78)
		table->plr->angl = PIn;
	else if (table->map->map[iy][ix] == 83)
		table->plr->angl = PIs;
	else if (table->map->map[iy][ix] == 87)
		table->plr->angl = PIw;
	else
		table->plr->angl = PIe;
	table->plr->del->y = sin(table->plr->angl) * table->mv_speed;
	table->plr->del->x = cos(table->plr->angl) * table->mv_speed;
	for (double v = table->plr->cords->y - 2; v <= (table->plr->cords->y + 2); v++) {
		if (v == table->plr->cords->y - 2 || v == table->plr->cords->y + 2)
			for (double w = table->plr->cords->x - 1; w <= table->plr->cords->x + 1; w++)
				my_mlx_pixel_put(table->mlx->img, w, v, 0x00FFFFFF);
		else
			for (double w = table->plr->cords->x - 2; w <= table->plr->cords->x + 2; w++)
				my_mlx_pixel_put(table->mlx->img, w, v, 0x00FFFFFF);
	}
	// my_mlx_pixel_put(&table->mlx->img, table->plr->cords->x, table->plr->cords->y, 0x00FFFFFF);
	mlx_put_image_to_window(table->mlx->mlx_ptr, table->mlx->win_ptr, table->mlx->img->img_ptr, 0, 0);
}

void	blayer_movement(t_able *table) {
	for (double v = table->plr->cords->y - 2; v <= (table->plr->cords->y + 2); v++) {
		if (v == table->plr->cords->y - 2 || v == table->plr->cords->y + 2)
			for (double w = table->plr->cords->x - 1; w <= table->plr->cords->x + 1; w++)
				my_mlx_pixel_put(table->mlx->img, w, v, 0x00FFFFFF);
		else
			for (double w = table->plr->cords->x - 2; w <= table->plr->cords->x + 2; w++)
				my_mlx_pixel_put(table->mlx->img, w, v, 0x00FFFFFF);
	}
}
