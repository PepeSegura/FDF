/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_limits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:24:21 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 23:51:11 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static t_map_limits	init_map_limits(void)
{
	t_map_limits	limits;

	limits.min[X] = INT_MAX;
	limits.min[Y] = INT_MAX;
	limits.min[Z] = INT_MAX;
	limits.max[X] = INT_MIN;
	limits.max[Y] = INT_MIN;
	limits.max[Z] = INT_MIN;
	return (limits);
}

void	get_bounding_box(t_map *map, double scale)
{
	int				i;
	int				j;
	t_map_limits	limits;

	limits = init_map_limits();
	i = 0;
	while (i < map->actual_size)
	{
		j = 0;
		while (j < map->min_wide)
		{
			if (map->points[i][j].x * scale < limits.min[X])
				limits.min[X] = map->points[i][j].x * scale;
			if (map->points[i][j].x * scale > limits.max[X])
				limits.max[X] = map->points[i][j].x * scale;
			if (map->points[i][j].y * scale < limits.min[Y])
				limits.min[Y] = map->points[i][j].y * scale;
			if (map->points[i][j].y * scale > limits.max[Y])
				limits.max[Y] = map->points[i][j].y * scale;
			j++;
		}
		i++;
	}
	map->limits = limits;
}

void	set_offsets(t_fdf *fdf)
{
	int	mid[2];

	get_bounding_box(&fdf->map, fdf->cam.scale);
	mid[X] = (fdf->map.limits.min[X] + fdf->map.limits.max[X]) / 2;
	mid[Y] = (fdf->map.limits.min[Y] + fdf->map.limits.max[Y]) / 2;
	fdf->cam.offsets[X] = ((SCREEN_WIDTH / 2) - mid[X])
		+ fdf->cam.key_offset[X];
	fdf->cam.offsets[Y] = ((SCREEN_HEIGHT / 2) - mid[Y])
		+ fdf->cam.key_offset[Y];
}
