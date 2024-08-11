/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:53:57 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/11 22:40:53 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	rotate_map(t_map *map)
{
	const double (*rot_z)[3] = get_rot_z(45);
    const double (*rot_x)[3] = get_rot_x(atan(sqrt(2)));
    // const double (*proj)[3] = get_projection();      // Projection matrix
	int	i;
	int	j;

	i = 0;
	while (i < map->actual_size)
	{
		j = 0;
		while (j < map->min_wide)
		{
			map->points[i][j] = mul_mat(rot_z, map->points[i][j]);
			map->points[i][j] = mul_mat(rot_x, map->points[i][j]);
			// map->points[i][j] = mul_mat(proj, map->points[i][j]);
			j++;
		}
		i++;
	}
}
