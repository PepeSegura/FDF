/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/17 22:50:19 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void draw_map2(t_fdf *fdf)
{
    t_point **points;
    double scale;
    int min_x = INT_MAX, max_x = INT_MIN;
    int min_y = INT_MAX, max_y = INT_MIN;
    int center_x;
    int center_y;
    int offset_x;
    int offset_y;
    int i, j;
    int x1, y1, x2, y2, x3, y3;

    points = fdf->map.points;
    scale = fdf->cam.scale;

    // Calculate the bounding box of the transformed points
    for (i = 0; i < fdf->map.actual_size; i++)
    {
        for (j = 0; j < fdf->map.min_wide; j++)
        {
            int x = points[i][j].x * scale;
            int y = points[i][j].y * scale;

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
    memset(fdf->img->pixels, 0, fdf->img->width * fdf->img->height * BPP);

    // Draw horizontal and vertical lines with offset applied
    for (i = 0; i < fdf->map.actual_size; i++)
    {
        for (j = 0; j < fdf->map.min_wide; j++)
        {
            x1 = points[i][j].x * scale + offset_x;
            y1 = points[i][j].y * scale + offset_y;

            // Draw horizontal line to the right
            if (j < fdf->map.min_wide - 1)
            {
                x2 = points[i][j + 1].x * scale + offset_x;
                y2 = points[i][j + 1].y * scale + offset_y;
                bresenham_line(
                    fdf,
                    (t_point){.x = x1, .y = y1, .color = points[i][j].color},
                    (t_point){.x = x2, .y = y2, .color = points[i][j + 1].color}
                    );
            }

            // Draw vertical line to the bottom
            if (i < fdf->map.actual_size - 1)
            {
                x3 = points[i + 1][j].x * scale + offset_x;
                y3 = points[i + 1][j].y * scale + offset_y;
                bresenham_line(
                    fdf, 
                    (t_point){.x = x1, .y = y1, .color = points[i][j].color},
                    (t_point){.x = x3, .y = y3, .color = points[i + 1][j].color}
                );
            }
        }
    }

    printf("img %p\n", fdf->img);
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
	fdf->img = img;
    rotate_map(&fdf->map);
	draw_map2(fdf);
    mlx_key_hook(mlx, my_key_hook, fdf);
	mlx_scroll_hook(mlx, &my_scrollhook, fdf);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

void	print_point(t_point point)
{
	printf("x: [%f]\n", point.x);
	printf("y: [%f]\n", point.y);
	printf("z: [%f]\n", point.z);
	printf("\n");
}



int	main(int argc, char **argv)
{
	(void)argc, (void)argv;
	t_fdf	fdf;

	ft_bzero(&fdf, sizeof(fdf));
	parse_input(argc, argv, &fdf);
	// printf("INPUT %s\n", fdf.map.str);
	// printf("WIDE_MAP: [%d]\n", fdf.map.min_wide);
	// printf("HEIGHT_MAP: [%d]\n", fdf.map.actual_size);
	// // print_map(&fdf.map);
    // set_map_limits(&fdf.map, 1, &fdf);
    // printf("LIMITS:\n");
    // printf("MIN: X: [%d] Y: [%d]\n", fdf.map.limits.min_x,  fdf.map.limits.min_y);
    // printf("MAX: X: [%d] Y: [%d]\n", fdf.map.limits.max_x,  fdf.map.limits.max_y);
    // set_map_offsets(&fdf);
    // printf("SCALE: [%f]\n", fdf.cam.scale);
    // printf("OFFSETS:\nX: [%d] Y: [%d]\n", fdf.cam.offset_x, fdf.cam.offset_y);
	// rotate_map(&fdf.map);
	// print_map(&fdf.map);
	mlx_stuff(&fdf);
	exit(EXIT_SUCCESS);
}
