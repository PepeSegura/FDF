/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:53:57 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/10 14:28:31 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	rotate_map(t_map *map)
{
	// const double (*rot_x)[3] = get_rot_x(M_PI / 6); // Rotate around X by -35.264 degrees
    const double (*rot_y)[3] = get_rot_y(M_PI / 4);  // Rotate around Y by 45 degrees
    // const double (*proj)[3] = get_projection();      // Projection matrix
	int	i;
	int	j;

	i = 0;
	while (i < map->actual_size)
	{
		j = 0;
		while (j < map->min_wide)
		{
			// map->points[i][j] = mul_mat(rot_x, map->points[i][j]);
			map->points[i][j] = mul_mat(rot_y, map->points[i][j]);
			// map->points[i][j] = mul_mat(proj, map->points[i][j]);
			j++;
		}
		i++;
	}
}
