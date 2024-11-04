/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/11/04 12:35:30 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

mlx_t    *init_and_customize_mlx(t_fdf *fdf)
{
    mlx_t           *mlx;
    mlx_win_cursor_t *cursor; 

    mlx_set_setting(MLX_DECORATED, false);
    mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, fdf->map.str, false);
	if (mlx == NULL)
		ft_error("Can't load mlx");
    cursor = mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR);
    mlx_set_cursor(mlx, cursor);
    return (mlx);
}

void	mlx_stuff(t_fdf *fdf)
{
	mlx_t           *mlx;
	mlx_image_t     *img;

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

int	main(int argc, char **argv)
{
	(void)argc, (void)argv;
	t_fdf	fdf;

	ft_bzero(&fdf, sizeof(fdf));
	parse_input(argc, argv, &fdf);
	printf("INPUT %s\n", fdf.map.str);
	printf("WIDE_MAP: [%d]\n", fdf.map.min_wide);
	printf("HEIGHT_MAP: [%d]\n", fdf.map.actual_size);
	// print_map(&fdf.map);
	rotate_map(&fdf.map);
	// print_map(&fdf.map);
	mlx_stuff(&fdf);
	exit(EXIT_SUCCESS);
}
