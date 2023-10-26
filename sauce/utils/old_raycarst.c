/*
# @brief Initialize the raycast
* @param t_able_*table
* @param int_x 
*/
void	init_raycast(t_able *table, int x)
{
	table->raycast.camera = 2 * x / (double)(table->width) - 1;
	table->raycast.rpos.x = table->pos.x;
	table->raycast.rpos.y = table->pos.y;
	table->raycast.rdir.x = table->raycast.dir.x + table->raycast.plane.x
		* table->raycast.camera;
	table->raycast.rdir.y = table->raycast.dir.y + table->raycast.plane.y
		* table->raycast.camera;
	table->raycast.rmap.x = (int)table->raycast.rpos.x;
	table->raycast.rmap.y = (int)table->raycast.rpos.y;
	table->raycast.rdisd.x = fabs(1 / table->raycast.rdir.x);
	table->raycast.rdisd.y = fabs(1 / table->raycast.rdir.y);
	table->raycast.hit = 0;
}

/*
# @brief Will calculate the direction of the ray that has been sent out to the 
# grid intersection
* @example
* 1. (table->rc.rdir.x < 0): Throwing the ray direction towards left in the 
* x-axis. and vice versa for the else statement. 
* 2. (table->rc.rdir.y < 0): Throwing the ray direction upwards and vice versa. 
? @return
--> Calculates rc.rdist.x and rc.rdisty which represents the ray need to 
--> travel along the x-axis
--> and y-axis to intersect the grid lines from horizontal and vertical points. 
*/
void	direction_ray(t_able *table)
{
	if (table->raycast.rdir.x < 0)
	{
		table->raycast.step.x = -1;
		table->raycast.rdist.x = (table->raycast.rpos.x - table->raycast.rmap.x) 
			* table->raycast.rdisd.x;
	}
	else
	{
		table->raycast.step.x = 1;
		table->raycast.rdist.x = (table->raycast.rmap.x + 1.0
				- table->raycast.rpos.x) * table->raycast.rdisd.x;
	}
	if (table->raycast.rdir.y < 0)
	{
		table->raycast.step.y = -1;
		table->raycast.rdist.y = (table->raycast.rpos.y - table->raycast.rmap.y) 
			* table->raycast.rdisd.y;
	}
	else
	{
		table->raycast.step.y = 1;
		table->raycast.rdist.y = (table->raycast.rmap.y + 1.0
				- table->raycast.rpos.y) * table->raycast.rdisd.y;
	}
}

/*
# @brief The rays keeps going untill it hits a wall
* @example
* The ray keeps looping as it keeps hitting 0 which allows the user to increase 
* the step and dist.x of the ray which later entails calls the function to check 
* the ray whether it hit either of the conditions specified which leads to loop 
* exiting out of loop. 
--> rc.wall 0 and 2 means left and right,
	1 and 3 means up and down for the rays to move.
*/
void	hit_ray(t_able *table)
{
	while (table->raycast.hit == 0)
	{
		if (table->raycast.rdist.x < table->raycast.rdist.y)
		{
			table->raycast.rdist.x += table->raycast.rdisd.x;
			table->raycast.rmap.x += table->raycast.step.x;
			if (table->raycast.rdir.x < 0)
				table->raycast.wall = 0;
			else
				table->raycast.wall = 2;
		}
		else
		{
			table->raycast.rdist.y += table->raycast.rdisd.y;
			table->raycast.rmap.y += table->raycast.step.y;
			if (table->raycast.rdir.y < 0)
				table->raycast.wall = 1;
			else
				table->raycast.wall = 3;
		}
		if (my_check_rc(table) == 1)
			table->raycast.hit = 1;
	}
}

/*
# @brief It will calculate the size of the ray once hit the wall 
* @details
* - Checks which driection of the ray it hit the wall (x or y)
* - Calculates the [prependicular distance] to the wall along the direction ray
* - Using the table->height to calculate the raycast height in vertical sense
* - Calculates the wall slice where to start the wall from and where to end
* - Added the texxture.id to give different textures to the wall 
*/
void	size_ray(t_able *table)
{
	if (table->raycast.wall == 0 || table->raycast.wall == 2)
		table->raycast.dist = (table->raycast.rmap.x - table->raycast.rpos.x
				+ (1 - table->raycast.step.x) / 2) / table->raycast.rdir.x;
	else
		table->raycast.dist = (table->raycast.rmap.y - table->raycast.rpos.y + (1
					- table->raycast.step.y) / 2) / table->raycast.rdir.y;
	table->raycast.rh = ((table->height / table->raycast.dist));
	table->raycast.wstart = ((-table->raycast.rh)) / 2 + table->height / 2;
	if (table->raycast.wstart < 0)
		table->raycast.wstart = 0;
	table->raycast.wend = table->raycast.rh / 2 + table->height / 2;
	if (table->raycast.wend >= table->height)
		table->raycast.wend = table->height - 1;
	table->raycast.textur.id = (table->map.tab_map[table->raycast.rmap.y]
		[table->raycast.rmap.x] - '0') - 1;
}

void	wall_textur(t_able *table)
{
	double	wallx;

	if (table->raycast.wall == 0 || table->raycast.wall == 2)
		wallx = table->raycast.rpos.y + table->raycast.dist
			* table->raycast.rdir.y;
	else
		wallx = table->raycast.rpos.x + table->raycast.dist
			* table->raycast.rdir.x;
	wallx -= floor((wallx));
	table->raycast.textur.x = (int)(wallx * 64.0);
	if ((table->raycast.wall == 0 || table->raycast.wall == 2)
		&& table->raycast.rdir.x > 0)
		table->raycast.textur.x = 64 - table->raycast.textur.x - 1;
	if ((table->raycast.wall == 1 || table->raycast.wall == 3)
		&& table->raycast.rdir.y < 0)
		table->raycast.textur.x = 64 - table->raycast.textur.x - 1;
	if_and_elseforest(table);
	table->raycast.step_textur = 1.0 * 64 / table->raycast.rh;
	table->raycast.textur_pos = (table->raycast.wstart - table->height / 2
			+ table->raycast.rh / 2) * table->raycast.step_textur;
}
