/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/03 00:59:26 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

// void	draw_map(t_map *map, t_camera *cam, mlx_image_t *img)
// {
// 	t_point	**points;
// 	int		i;
// 	int		j;
// 	int		x;
// 	int		y;

// 	points = map->points;
// 	memset(img->pixels, 0, img->width * img->height * BPP);
// 	i = 0;
// 	while (i < map->actual_size)
// 	{
// 		j = 0;
// 		while (j < map->min_wide)
// 		{
//             x = points[i][j].x * cam->grid_space;
//             y = points[i][j].y * cam->grid_space;
//             if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
//                 mlx_put_pixel(img, x, y, points[i][j].color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	draw_map(t_fdf *fdf, mlx_image_t *img)
{
	t_point	**points;
	double	scale;
	int		min_x = INT_MAX, max_x;
	int		min_y = INT_MAX, max_y;
	int		center_x;
	int		center_y;
	int		offset_x;
	int		offset_y;

	points = fdf->map.points;
	int i, j;
	scale = fdf->cam.grid_space;
	int x, y;
	// Calculate the bounding box of the transformed points
	min_x = INT_MAX, max_x = INT_MIN;
	min_y = INT_MAX, max_y = INT_MIN;
	for (i = 0; i < fdf->map.actual_size; i++)
	{
		for (j = 0; j < fdf->map.min_wide; j++)
		{
			x = points[i][j].x * scale;
			y = points[i][j].y * scale;
			if (x < min_x)
				min_x = x;
			if (x > max_x)
				max_x = x;
			if (y < min_y)
				min_y = y;
			if (y > max_y)
				max_y = y;
		}
	}
	// Calculate the center of the bounding box
	center_x = (min_x + max_x) / 2;
	center_y = (min_y + max_y) / 2;
	// Calculate the offset to center the image in the window
	offset_x = (SCREEN_WIDTH / 2) - center_x;
	offset_y = (SCREEN_HEIGHT / 2) - center_y;
	// Clear the image
	memset(img->pixels, 0, img->width * img->height * BPP);
	// Draw the points with the offset applied
	for (i = 0; i < fdf->map.actual_size; i++)
	{
		for (j = 0; j < fdf->map.min_wide; j++)
		{
			x = points[i][j].x * scale + offset_x;
			y = points[i][j].y * scale + offset_y;
			if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
			{
				mlx_put_pixel(img, x, y, points[i][j].color);
			}
		}
	}
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	(void)xdelta, (void)ydelta, (void)param;
	fdf = (t_fdf *)param;
	// Simple up or down detection
	if (ydelta > 0) // Scroll Up (Zoom In)
	{
		puts("Zooming In!");
		fdf->cam.grid_space *= 1.2; // Increase grid space by 20%
	}
	else if (ydelta < 0) // Scroll Down (Zoom Out)
	{
		puts("Zooming Out!");
		fdf->cam.grid_space /= 1.2; // Decrease grid space by 20%
	}
	// Redraw the map with the updated grid_space
	draw_map(fdf, fdf->img);
}

void	mlx_stuff(t_fdf *fdf)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	// mlx_set_setting(MLX_DECORATED, false);
	// mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, fdf->map.str, false);
	if (mlx == NULL)
		ft_error("Can't load mlx");
	img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error("Can't load img");
	draw_map(fdf, img);
	fdf->img = img;
	mlx_scroll_hook(mlx, &my_scrollhook, fdf);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

void	print_point(t_point point)
{
	printf("x: [%d]\n", point.x);
	printf("y: [%d]\n", point.y);
	printf("z: [%d]\n", point.z);
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	(void)argc, (void)argv;
	ft_bzero(&fdf, sizeof(fdf));
	parse_input(argc, argv, &fdf);
	printf("INPUT %s\n", fdf.map.str);
	printf("WIDE_MAP: [%d]\n", fdf.map.min_wide);
	printf("HEIGHT_MAP: [%d]\n", fdf.map.actual_size);
	// print_map(&fdf.map);
	// rotate_map(&fdf.map);
	// print_map(&fdf.map);
	mlx_stuff(&fdf);
	// t_point p1 = {.x = 10, .y = 10, .z = 30};
	// print_point(p1);
	// t_point p2 = mul_mat(get_rot_y(ANGLE), p1);
	// print_point(p2);
	exit(EXIT_SUCCESS);
}
