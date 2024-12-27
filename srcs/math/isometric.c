/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:01:05 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 23:55:31 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

#define ATANSQR_2 0.955316618
#define SCALE 10

inline void	normalize_z(t_point *point, t_map *map)
{
	const double	range = (double)map->limits.max[Z]
		- (double)map->limits.min[Z];
	const double	tile_size = range / SCALE;

	point->z = (point->z - (double)map->limits.min[Z]) / tile_size;
}

t_point	isometric(t_point p, t_fdf *fdf)
{
	double	x_deg;
	double	z_deg;

	normalize_z(&p, &fdf->map);
	z_deg = 45;
	x_deg = ATANSQR_2;
	p = mul_mat(g_get_rot_z(z_deg), p);
	p = mul_mat(g_get_rot_x(x_deg), p);
	fdf->cam.z_deg = z_deg;
	fdf->cam.x_deg = x_deg;
	fdf->cam.y_deg = 0;
	return (p);
}

void	apply_isometric(t_map *map, t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->actual_size)
	{
		j = 0;
		while (j < map->min_wide)
		{
			map->points[i][j] = isometric(map->points[i][j], fdf);
			j++;
		}
		i++;
	}
}
