/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 01:48:56 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

mlx_t	*init_and_customize_mlx(t_fdf *fdf)
{
	mlx_t				*mlx;
	mlx_win_cursor_t	*cursor;

	// mlx_set_setting(MLX_DECORATED, false);
	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, fdf->map.str, false);
	if (mlx == NULL)
		ft_error("Can't load mlx");
	cursor = mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR);
	mlx_set_cursor(mlx, cursor);
	return (mlx);
}

void	mlx_stuff(t_fdf *fdf)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = init_and_customize_mlx(fdf);
	img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error("Can't load img");
	fdf->img = img;
	fdf->mlx = mlx;
	draw_map(fdf);
	mlx_key_hook(mlx, my_key_hook, fdf);
	mlx_scroll_hook(mlx, &my_scrollhook, fdf);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

# define SCALE 10

inline void normalize_height2(t_point *point, t_map *map)
{
	double segment_size = (map->limits.max[Z] - map->limits.min[Z]) / SCALE;
	point->z = (point->z - map->limits.min[Z]) / segment_size;
}

void	rotate_map2(t_map *map, t_fdf *fdf)
{
	int				i;
	int				j;

	i = 0;
	while (i < map->actual_size)
	{
		j = 0;
		while (j < map->min_wide)
		{
			normalize_height2(&map->points[i][j], map);
			map->points[i][j] = isometric(map->points[i][j], fdf);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	(void)argc, (void)argv;
	ft_bzero(&fdf, sizeof(fdf));
	parse_input(argc, argv, &fdf);
	printf("HEIGHT:\nMIN:%d MAX: %d\n", fdf.map.limits.min[Z], fdf.map.limits.max[Z]);
	printf("INPUT %s\n", fdf.map.str);
	printf("WIDE_MAP: [%d]\n", fdf.map.min_wide);
	printf("HEIGHT_MAP: [%d]\n", fdf.map.actual_size);
	// rotate_map(&fdf.map);
	rotate_map2(&fdf.map, &fdf);
	
	mlx_stuff(&fdf);
	exit(EXIT_SUCCESS);
}
