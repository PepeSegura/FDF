/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:53:57 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/02 17:56:52 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	rotate_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->actual_size)
	{
		j = 0;
		while (j < map->min_wide)
		{
			map->points[i][j] = mul_mat(get_projection(), map->points[i][j]);
			map->points[i][j] = mul_mat(get_rot_x(ANGLE), map->points[i][j]);
			map->points[i][j] = mul_mat(get_rot_y(ANGLE), map->points[i][j]);
			map->points[i][j] = mul_mat(get_rot_z(ANGLE), map->points[i][j]);
			j++;
		}
		i++;
	}
}
