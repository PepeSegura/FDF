/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:34:16 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/25 23:33:03 by psegura-         ###   ########.fr       */
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

t_point set_point(t_point s, t_camera cam)
{
    t_point d;

    d.x = s.x * cam.scale + cam.offsets[X];
    d.y = s.y * cam.scale + cam.offsets[Y];
    d.z = s.z;
    d.color = s.color;
    return (d);
}

void draw_map(t_fdf *fdf)
{
    t_point **points;
    int i;
    int j;

    points = fdf->map.points;

    set_offsets(fdf);

    // Clear the image
    memset(fdf->img->pixels, 0, fdf->img->width * fdf->img->height * BPP);

    // Draw horizontal and vertical lines with offset applied
    i = -1;
    while (++i < fdf->map.actual_size)
    {
        j = -1;
        while (++j < fdf->map.min_wide)
        {
            // Draw horizontal line to the right
            if (j < fdf->map.min_wide - 1)
            {
                bresenham_line(
                    fdf,
                    set_point(points[i][j],  fdf->cam),
                    set_point(points[i][j + 1],  fdf->cam)
                );
            }
            // Draw vertical line to the bottom
            if (i < fdf->map.actual_size - 1)
            {
                bresenham_line(
                    fdf,
                    set_point(points[i][j],  fdf->cam),
                    set_point(points[i + 1][j],  fdf->cam)
                );
            }
        }
    }
}
