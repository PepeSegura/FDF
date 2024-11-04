/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_limits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:24:21 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/26 00:36:57 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static t_map_limits set_map_limits(void)
{
    t_map_limits    limits;

    limits.max_x = INT_MIN;
    limits.max_y = INT_MIN;
    limits.min_x = INT_MAX;
    limits.min_y = INT_MAX;
    return (limits);
}

void get_bounding_box(t_map *map, double scale)
{
    int             i;
    int             j;
    t_map_limits    limits;

    limits = set_map_limits();
    i = 0;
    while (i < map->actual_size)
    {
        j = 0;
        while (j < map->min_wide)
        {
            if (map->points[i][j].x * scale < limits.min_x)
                limits.min_x = map->points[i][j].x * scale;
            if (map->points[i][j].x * scale > limits.max_x)
                limits.max_x = map->points[i][j].x * scale;
            if (map->points[i][j].y * scale < limits.min_y)
                limits.min_y = map->points[i][j].y * scale;
            if (map->points[i][j].y * scale > limits.max_y)
                limits.max_y = map->points[i][j].y * scale;
            j++;
        }
        i++;
    }
    map->limits = limits;
}

void set_offsets(t_fdf *fdf)
{
    // Calculate the bounding box of the scaled points
    get_bounding_box(&fdf->map, fdf->cam.scale);
    printf("getbounding: min X: %d Y: %d - max X: %d Y: %d\n", fdf->map.limits.min_x, fdf->map.limits.min_y, fdf->map.limits.max_x, fdf->map.limits.max_y);
    int center[2];

    // Calculate the center of the bounding box
    center[X] = (fdf->map.limits.min_x + fdf->map.limits.max_x) / 2;
    center[Y] = (fdf->map.limits.min_y + fdf->map.limits.max_y) / 2;
    printf("center: X: %d Y: %d\n", center[X], center[Y]);

    // Calculate the offset to center the image in the window
    fdf->cam.offsets[X] = ((SCREEN_WIDTH / 2) - center[X]) + fdf->cam.key_offset[X];
    fdf->cam.offsets[Y] = ((SCREEN_HEIGHT / 2) - center[Y]) + fdf->cam.key_offset[Y];

    printf("setofsets() X: %d Y: %d\n", fdf->cam.offsets[X], fdf->cam.offsets[Y]);
}

