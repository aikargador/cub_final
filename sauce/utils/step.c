#include "cub69d.h"

// hinter -> horizontal intersection!
// firstinter -> first intersection!

/* new varz
-> ra.y
-> Ya
-> Xa
*/




/*

	2. Finding Ya
	If the ray is facing up
		Ya=-BLK;
	If the ray is facing down
		Ya=BLK;

	3. Finding Xa
	Xa = BLK/tan(60) = 36;

	4. We can get the coordinate of C as follows:
	C.x=A.x+Xa = 115+36 = 151;
	C.y=A.y+Ya = 191-BLK = 127;
	Convert this into grid coordinate by 
	dividing each component with BLK.
	The result is
	C.x = 151/BLK = 2 (grid coordinate),
	C.y = 127/BLK = 1 (grid coordinate)
	So the grid coordinate of C is (2, 1).
	(C programmer's note: Remember we always round down,
	this is especially true since
	you can use right shift by 8 to divide by BLK).

	5. Grid (2,1) is checked.
	Again, there is no wall, so the ray is extended
	to D.
	
	6. We can get the coordinate of D as follows:
	D.x=C.x+Xa = 151+36 = 187;
	D.y=C.y+Ya = 127-BLK = 63;
	Convert this into grid coordinate by
	dividing each component with BLK.
	The result is
	D.x = 187/BLK = 2 (grid coordinate),
	D.y = 63/BLK = 0 (grid coordinate)
	So the grid coordinate of D is (2, 0).

	6. Grid (2,0) is checked.
	There is a wall there, so the process stop.

*/

void	hinter(t_able *table) // step1 and 2 and 3
{
	t_cords	step;
	t_cords	inter;

	step.y = 0;
	inter.y = 0;
	if (table->a > 0 && table->a < PIw) // facing up
	{
		inter.y = (table->cords->y / BLK) * BLK - 1;
		step.y = -BLK; // Y step
	}
	else if (talbe->a < PIe && table->a > PIw) // facing down
	{
		inter.y = (table->cords->y / BLK) * BLK + BLK;
		step.y = BLK; // Y step
	}
	// else chk if the ray is facing straight at the sides!
	// tan(a) = BLK / Xa
	inter.x = table->cords.x + (table->cords.y - inter.y) / tan(table->a);
	step.x = BLK / tan(table->a); // X step

	while (inc_and_chk_wall(table, &inter, step))
		;
}

void	vinter(t_able *table) // step1 and 2 and 3
{
	t_cords	step;
	t_cords	inter;

	step.y = 0;
	inter.y = 0;
	if (table->a > PIs && table->a < PIn) // facing right
	{
		inter.x = (table->cords->x / BLK) * BLK + BLK;
		step.y = -BLK; // Y step
	}
	else if (talbe->a < PIs || table->a > PIn) // facing left
	{
		inter.x = (table->cords->x / BLK) * BLK - 1;
		step.y = BLK; // Y step
	}
	// else chk if the ray is facing straight at the sides!
	// tan(a) = BLK / Xa
	inter.x = table->cords.x + (table->cords.y - inter.y) / tan(table->a);
	step.x = BLK / tan(table->a); // X step

	while (inc_and_chk_wall(table, &inter, step))
		;
}


bool	inc_and_chk_wall(t_able *table, t_cords *inter, t_cords step)
{
	t_cords	chk;

	chk.y = inter->y / BLK;
	chk.x = inter->x / BLK;
	if (table->map[(chk.y * table->map_xy) + chk.x]) //this area is not protected and can seg
		return (false);
	inter->x += step.x;
	inter->y += step.y;
	return (true);
}

