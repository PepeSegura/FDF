/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:34:16 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/17 22:08:04 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void    draw_cross(t_fdf *fdf)
{
    printf("DRAW CROSS\n");
    int i;
    int j;

    i = -1;
    j = -1;
    while(++i < SCREEN_WIDTH)
        mlx_put_pixel(fdf->img, i, SCREEN_HEIGHT / 2, 0xFF00FF);
    while(++j < SCREEN_HEIGHT)
        mlx_put_pixel(fdf->img, SCREEN_WIDTH / 2, j, 0xFF00FF);
}

void    draw_map(t_fdf *fdf)
{
    printf("draw_map()\n");
    int     i;
    int     j;
    t_point p1;
    t_map   map;

    map = fdf->map;
    memset(fdf->img->pixels, 0, fdf->img->width * fdf->img->height * BPP);
    draw_cross(fdf);
    printf("MAP: size: %d wide: %d\n", map.actual_size, map.min_wide);
    i = 0;
    while (i < map.actual_size)
    {
        j = 0;
        while (j < map.min_wide)
        {
            p1 = scale_and_offset(map.points[i][j], fdf);
            if (j < map.min_wide - 1)
                bresenham_line(fdf, p1, scale_and_offset(map.points[i][j + 1], fdf));
            if (i < map.actual_size - 1)
                bresenham_line(fdf, p1, scale_and_offset(map.points[i + 1][j], fdf));
            j++;
        }
        i++;
    }
}
