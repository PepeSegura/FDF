/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/12 00:04:14 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void draw_map(t_fdf *fdf, mlx_image_t *img)
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
    scale = fdf->cam.grid_space;

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
    memset(img->pixels, 0, img->width * img->height * BPP);

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
                bresenham_line(fdf, (t_point){.x = x1, .y = y1, .color = points[i][j].color},
                               (t_point){.x = x2, .y = y2, .color = points[i][j + 1].color});
            }

            // Draw vertical line to the bottom
            if (i < fdf->map.actual_size - 1)
            {
                x3 = points[i + 1][j].x * scale + offset_x;
                y3 = points[i + 1][j].y * scale + offset_y;
                bresenham_line(fdf, (t_point){.x = x1, .y = y1, .color = points[i][j].color},
                               (t_point){.x = x3, .y = y3, .color = points[i + 1][j].color});
            }
        }
    }

    printf("img %p\n", img);
}

// void	calc_camera_offsets(t_fdf *fdf)
// {
// 	int			i;
// 	int			j;
// 	t_offset	ost;
// 	t_point		**points;
// 	t_camera	cam;

// 	ost = fdf->cam.offset;
// 	points = fdf->map.points;
// 	cam = fdf->cam;

// 	for (i = 0; i < fdf->map.actual_size; i++)
// 	{
// 		for (j = 0; j < fdf->map.min_wide; j++)
// 		{
// 			ost.x = points[i][j].x * fdf->cam.grid_space;
// 			ost.y = points[i][j].y * fdf->cam.grid_space;
// 			if (ost.x < ost.min_x)
// 				ost.min_x = ost.x;
// 			if (ost.x > ost.max_x)
// 				ost.max_x = ost.x;
// 			if (ost.y < ost.min_y)
// 				ost.min_y = ost.y;
// 			if (ost.y > ost.max_y)
// 				ost.max_y = ost.y;
// 		}
// 	}
// 	// Calculate the center of the bounding box
// 	ost.center_x = (ost.min_x + ost.max_x) / 2;
// 	ost.center_y = (ost.min_y + ost.max_y) / 2;
// 	// Calculate the offset to center the image in the window
// 	cam.offset_x = (SCREEN_WIDTH / 2) - ost.center_x;
// 	cam.offset_y = (SCREEN_HEIGHT / 2) - ost.center_y;
// }


// void draw_map(t_fdf *fdf, mlx_image_t *img)
// {
//     t_point **points;
//     double scale;
//     int min_x = INT_MAX, max_x = INT_MIN;
//     int min_y = INT_MAX, max_y = INT_MIN;
//     int center_x;
//     int center_y;
//     int offset_x;
//     int offset_y;
//     int i, j;
//     int x1, y1, x2, y2, x3, y3;

//     points = fdf->map.points;
//     scale = fdf->cam.grid_space;

//     // Calculate the bounding box of the transformed points
//     for (i = 0; i < fdf->map.actual_size; i++)
//     {
//         for (j = 0; j < fdf->map.min_wide; j++)
//         {
//             int x = points[i][j].x * scale;
//             int y = points[i][j].y * scale;

//             if (x < min_x)
//                 min_x = x;
//             if (x > max_x)
//                 max_x = x;
//             if (y < min_y)
//                 min_y = y;
//             if (y > max_y)
//                 max_y = y;
//         }
//     }

//     // Calculate the center of the bounding box
//     center_x = (min_x + max_x) / 2;
//     center_y = (min_y + max_y) / 2;

//     // Calculate the offset to center the image in the window
//     offset_x = (SCREEN_WIDTH / 2) - center_x;
//     offset_y = (SCREEN_HEIGHT / 2) - center_y;

//     // Clear the image
//     memset(img->pixels, 0, img->width * img->height * BPP);

//     // Draw horizontal and vertical lines
//     for (i = 0; i < fdf->map.actual_size; i++)
//     {
//         for (j = 0; j < fdf->map.min_wide; j++)
//         {
//             x1 = points[i][j].x * scale + offset_x;
//             y1 = points[i][j].y * scale + offset_y;

//             // Draw horizontal line to the right
//             if (j < fdf->map.min_wide - 1)
//             {
//                 x2 = points[i][j + 1].x * scale + offset_x;
//                 y2 = points[i][j + 1].y * scale + offset_y;
//                 bresenham_line(fdf, (t_point){.x = x1, .y = y1, .color = points[i][j].color},
//                                (t_point){.x = x2, .y = y2, .color = points[i][j + 1].color});
//             }

//             // Draw vertical line to the bottom
//             if (i < fdf->map.actual_size - 1)
//             {
//                 x3 = points[i + 1][j].x * scale + offset_x;
//                 y3 = points[i + 1][j].y * scale + offset_y;
//                 bresenham_line(fdf, (t_point){.x = x1, .y = y1, .color = points[i][j].color},
//                                (t_point){.x = x3, .y = y3, .color = points[i + 1][j].color});
//             }
//         }
//     }
// }


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
	fdf->img = img;
	draw_map(fdf, img);
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
	rotate_map(&fdf.map);
	// print_map(&fdf.map);
	mlx_stuff(&fdf);
	// t_point p1 = {.x = 10, .y = 10, .z = 30};
	// print_point(p1);
	// t_point p2 = mul_mat(get_rot_y(ANGLE), p1);
	// print_point(p2);
	exit(EXIT_SUCCESS);
}

// int main(void)
// {
// 	t_point a = {.x=0, .y=0, .color = 0xFF0000FF};
// 	t_point b = {.x=1920, .y=10, .color = 0xFFFF};

// 	bresenham_line(a, b);
// }

/* TODO: follow this repo */
// https://github.dev/m4nnb3ll/fdf/tree/main/fdf