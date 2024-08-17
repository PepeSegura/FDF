/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_limits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:24:21 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/17 22:22:08 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void set_map_limits(t_map *map, double scale, t_fdf *fdf) {
    t_point p;
    int i, j;

    // Initialize map limits
    map->limits.min_x = INT32_MAX;
    map->limits.max_x = -INT32_MAX;
    map->limits.min_y = INT32_MAX;
    map->limits.max_y = -INT32_MAX;

    for (i = 0; i < map->actual_size; i++) {
        for (j = 0; j < map->min_wide; j++) {
            p = isometric(scale_point(map->points[i][j], scale), fdf);
            // Update map limits
            if (p.x < map->limits.min_x)
                map->limits.min_x = p.x;
            if (p.x > map->limits.max_x)
                map->limits.max_x = p.x;
            if (p.y < map->limits.min_y)
                map->limits.min_y = p.y;
            if (p.y > map->limits.max_y)
                map->limits.max_y = p.y;
        }
    }
}

void set_map_offsets(t_fdf *fdf) {
    // Calculate map center
    double map_center_x = (fdf->map.limits.min_x + fdf->map.limits.max_x) / 2.0;
    double map_center_y = (fdf->map.limits.min_y + fdf->map.limits.max_y) / 2.0;

    // Calculate screen center
    double screen_center_x = SCREEN_WIDTH / 2.0;
    double screen_center_y = SCREEN_HEIGHT / 2.0;

    // Calculate offsets needed to center the map on the screen
    fdf->cam.offset_x = round(screen_center_x - map_center_x);
    fdf->cam.offset_y = round(screen_center_y - map_center_y);
}
