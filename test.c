#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int	main()
{

	double	ray_x;
	double	texture_x;
	int		x;
	int		texture_width;

	texture_width = 64;
	ray_x = 4.127;
	texture_x = (ray_x - round(ray_x));
	x = (int)(texture_x * texture_width);
	// printf("X CALCULUS\n");
	// printf("(double)abs(ray_x) is %f\n", (double)abs(ray_x));
	// printf("texture_x is %f\n", texture_x);
	// printf("x is %d\n", x);

	double	texture_y;
	int		y;
	int		wall_height;
	int		texture_height;
	int		i;

	texture_height = 64;
	wall_height = 100;
	y = 0;
	texture_y = 0;
	i = 0;

	while (i < wall_height)
	{
		printf("texture px %d is in {%d, %d}\n", i, x, y);
		y = i * texture_height / wall_height;
		i++;
	}

	return (0);
}