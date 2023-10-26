#include "cub69d.h"
//using calloc!!!!


/* the ternary below is == to this!
if (y == 0 || y == 7)
	map->map[(y * 8) + x] = 1;
else if (x == 0 || x == 7)
	map->map[(y * 8) + x] = 1;
else
	map->map[(y * 8) + x] = 0;

 VVVVVVVVVVVVVVVVVVV
map->map[(y * 8) + x] = (y == 0 || y == 7 || x == 0 || x == 7) ? 1 : 0;
 */

// void	map_init(t_map *map, short element_sz)
// {
// 	int	y;
// 	int	x;

// 	y = -1;
// 	map->map_xy = (short)sqrt((double)element_sz);
// 	printf("%d\n", map->map_xy);
// 	map->map_s = element_sz;
// 	map->map = ft_calloc(element_sz, sizeof(int));
// 	while (++y < map->map_xy)
// 	{
// 		x = -1;
// 		while (++x < map->map_xy)
// 		{
// 			if (y == 0 || y == map->map_xy - 1)
// 				map->map[(y * map->map_xy) + x] = 1;
// 			else if (x == 0 || x == 7)
// 				map->map[(y * map->map_xy) + x] = 1;
// 			else
// 				map->map[(y * map->map_xy) + x] = 0;
// 		}
// 	}
// 	map->map[25] = 83; //S = 83, N = 78, W = 87, E = 69
// 	// for (int k = 0; k < 64; k++) {
// 	// 	printf("map[%d] => %d\n", k, map->map[k]);
// 	// }
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


void	map_init(t_map *map, short element_sz)
{
	int	y;
	int	x;

	y = -1;
	map->map_xy = (short)sqrt((double)element_sz);
	map->map_s = element_sz;
	map->map = calloc(map->map_xy, sizeof(int *));
	for (int i = 0; i < map->map_xy; i++)
		map->map[i] = calloc(map->map_xy, sizeof(int));
	while (++y < map->map_xy)
	{
		x = -1;
		while (++x < map->map_xy)
		{
			if (y == 0 || y == map->map_xy - 1)
				map->map[y][x] = 1;
			else if (x == 0 || x == 7)
				map->map[y][x] = 1;
			else
				map->map[y][x] = 0;
		}
	}
	//S = 83, N = 78, W = 87, E = 69
	map->map[3][1] = 69;//e
	map->map[3][1] = 87;//w
	map->map[3][1] = 83;//s
	map->map[3][1] = 78;//n
}

void	draw_map(t_able *table)
{
	t_map	*mp = table->map;
	t_mlx	*mx = table->mlx;
	int x, y = 0;
	int w, h = 0;
	int clr;

	while (y < mp->map_xy)
	{
		x = 0;
		h = y * BLK;
		while (x < mp->map_xy)
		{
			w = x * BLK;
			// int p = (y * 8) + x;
			if (mp->map[y][x] == 1)
				clr = 0x00FFFF00;
			else
				clr = 0x00090999;
			for (int f = h; f < (y + 1) * BLK; f++)
				for (int k = w; k < (x + 1) * BLK; k++) {

					my_mlx_pixel_put(mx->img, k, f, clr);
				}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mx->mlx_ptr, mx->win_ptr, mx->img->img_ptr, 0, 0);
}
