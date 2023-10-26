/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:38:17 by aikram            #+#    #+#             */
/*   Updated: 2023/10/26 19:56:01 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub69d.h"

int	my_abs(int n)
{
	if (n >= 0)
		return (n);
	return (n * -1);
}

void	ray_contact(t_able *table);
void	ray_dir(t_able *table);

//initializes the raycasting variables
void	main_ray(t_able *table, int col)
{
	double	wdh;

	wdh = WDH;
	table->cam = 2 * col / wdh - 1;
	table->ray->cords.x = table->plr->cords->x;
	table->ray->cords.y = table->plr->cords->y;
	table->ray->dir.x = table->plr->del->x + table->plane->x * table->cam;
	table->ray->dir.y = table->plr->del->y + table->plane->y * table->cam;
	table->ray->map.x = table->plr->cords->x;
	table->ray->map.y = table->plr->cords->y;
	// if (!table->ray->dir.x)
	// 	table->ray->dstflag.x = 1;
	// else
		table->ray->ddist.x = my_abs(1 / table->ray->dir.x);//deltadistx
	// if (!table->ray->dir.y)
	// 	table->ray->dstflag.y = 1;
	// else
		table->ray->ddist.y = my_abs(1 / table->ray->dir.y);
	printf("e ddist.x %f\n", table->ray->ddist.x);
	printf("e ddist.y %f\n", table->ray->ddist.y);
	printf("plane.x %f\n", table->plane->x);
	printf("plane.y %f\n", table->plane->y);
	printf("camera %f\n", table->cam);
	table->ray->hit = false;
	ray_dir(table);
}

// calculates the direction of the ray(step value and )
void	ray_dir(t_able *table)
{
	if (table->ray->dir.x < 0)
	{
		table->ray->step.x = -1;
		table->ray->sdist.x = (table->ray->cords.x - table->ray->map.x) \
			* table->ray->ddist.x;
	}
	else
	{
		table->ray->step.x = 1;
		table->ray->sdist.x = (table->ray->map.x + 1.0 - table->ray->cords.x) \
			* table->ray->ddist.x;
	}
	if (table->ray->dir.y < 0)
	{
		table->ray->step.y = -1;
		table->ray->sdist.y = (table->ray->cords.y - table->ray->map.y) \
			* table->ray->ddist.y;
	}
	else
	{
		table->ray->step.y = 1;
		table->ray->sdist.y = (table->ray->map.x + 1.0 - table->ray->cords.y) \
			* table->ray->ddist.y;
	}
	ray_contact(table);
}
 
// chks if any ray came into contact with a wall!
void	ray_contact(t_able *table)
{
	int stop = 10;
	while (!table->ray->hit)
	{
		printf("sdist.x %f\n", table->ray->sdist.x);
		printf("sdist.y %f\n", table->ray->sdist.y);
		printf("ddist.x %f\n", table->ray->ddist.x);
		printf("ddist.y %f\n", table->ray->ddist.y);
		if (table->ray->sdist.x < table->ray->sdist.y)
		{
			table->ray->sdist.x += table->ray->ddist.x;
			table->ray->map.x += table->ray->step.x;
			table->ray->side = 0;
		}
		else
		{
			table->ray->sdist.y += table->ray->ddist.y;
			table->ray->map.y += table->ray->step.y;
			table->ray->side = 1;
		}
		printf("y %d\n", table->ray->map.y / 64);
		printf("x %d\n", table->ray->map.x / 64);
		if (table->map->map[table->ray->map.y / 64][table->ray->map.x / 64] == 1)
			table->ray->hit = 1;
		stop--;
		if (stop == 1)
			break ;
		exit(1);
	}
}

// void	cast_ray(t_able *table)
// {Ó
// 	int i;

// 	i = -1;
// 	while (++i < WDH)
// 	{
// 		//calculate ray position and direction
// 		double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
// 		double rayDirX = table->plr->del->x + table->plane->x * cameraX;
// 		double rayDirY = table->plr->del->y + table->plane->y * cameraX;

// 		//which box of the map we're in
// 		int mapX = int(table->plr->cords->x);
// 		int mapY = int(table->plr->cords->y);

// 		//length of ray from current position to next x or y-side
// 		double sideDistX;
// 		double sideDistY;

// 		//length of ray from one x or y-side to next x or y-side
// 		double deltaDistX = (rayDirX == 0) ? 1e30 : my_abs(1 / rayDirX);
// 		double deltaDistY = (rayDirY == 0) ? 1e30 : my_abs(1 / rayDirY);
// 		double perpWallDist;

// 		//what direction to step in x or y-direction (either +1 or -1)
// 		int stepX;
// 		int stepY;

// 		int hit = 0; //was there a wall hit?
// 		int side; //was a NS or a EW wall hit?
	
// 	//calculate step and initial sideDist
// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (table->plr->cords->x - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - table->plr->cords->x) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (table->plr->cords->y - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - table->plr->cords->y) * deltaDistY;
// 		}

// 		//perform DDA
// 		while (hit == 0)
// 		{
// 			//jump to next map square, either in x-direction, or in y-direction
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			//Check if ray has hit a wall
// 			if (worldMap[mapX][mapY] > 0) hit = 1;
// 		}
// 		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
// 		if(side == 0)	perpWallDist = (sideDistX - deltaDistX);
// 		else			perpWallDist = (sideDistY - deltaDistY);

// 		//Calculate height of line to draw on screen
// 		int lineHeight = (int)(h / perpWallDist);

// 		//calculate lowest and highest pixel to fill in current stripe
// 		int drawStart = -lineHeight / 2 + h / 2 + pitch;
// 		if(drawStart < 0) drawStart = 0;
// 		int drawEnd = lineHeight / 2 + h / 2 + pitch;
// 		if(drawEnd >= h) drawEnd = h - 1;

// 		//calculate value of wallX
// 		double wallX; //where exactly the wall was hit
// 		if(side == 0)	wallX = posY + perpWallDist * rayDirY;
// 		else			wallX = posX + perpWallDist * rayDirX;
// 		wallX -= floor((wallX));


// 	}

// }
