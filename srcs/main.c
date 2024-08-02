/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/02 18:14:02 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	draw_map(t_map *map, mlx_image_t *img)
{
	t_point	**points;
	int		i;
	int		j;

	points = map->points;
	memset(img->pixels, 0, img->width * img->height * BPP);
	i = 0;
	while (i < map->actual_size)
	{
		j = 0;
		while (j < map->min_wide)
		{
			mlx_put_pixel(img, points[i][j].x, points[i][j].y,
				points[i][j].color);
			j++;
		}
		i++;
	}
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
	draw_map(&fdf->map, img);
	mlx_loop(mlx);
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
	print_map(&fdf.map);
	mlx_stuff(&fdf);
	rotate_map(&fdf.map);
	print_map(&fdf.map);
	t_point p1 = {.x = 10, .y = 10, .z = 30};
	print_point(p1);
	t_point p2 = mul_mat(get_rot_y(ANGLE), p1);
	print_point(p2);
	exit(EXIT_SUCCESS);
}
