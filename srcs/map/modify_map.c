/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:53:57 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 01:46:57 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

# define SCALE 5

inline void normalize_height(t_point *point, t_map *map)
{
	double segment_size = (map->limits.max[Z] - map->limits.min[Z]) / SCALE;
	point->z = (point->z - map->limits.min[Z]) / segment_size;
}

void	rotate_map(t_map *map)
{
	const	double	(*rot_z)[3] = get_rot_z(45);
	const	double	(*rot_x)[3] = get_rot_x(atan(sqrt(2)));
	const	double	(*proj)[3] = get_projection();
	int				i;
	int				j;

	i = 0;
	while (i < map->actual_size)
	{
		j = 0;
		while (j < map->min_wide)
		{
			normalize_height(&map->points[i][j], map);
			// map->points[i][j].z = map->points[i][j].z /50;
			map->points[i][j] = mul_mat(rot_z, map->points[i][j]);
			map->points[i][j] = mul_mat(rot_x, map->points[i][j]);
			map->points[i][j] = mul_mat(proj, map->points[i][j]);
			// printf("Point[%d][%d]: x=%.2f, y=%.2f, z=%.2f\n", 
			//        i, j, 
			//        map->points[i][j].x, 
			//        map->points[i][j].y, 
			//        map->points[i][j].z);
			j++;
		}
		i++;
	}
}
