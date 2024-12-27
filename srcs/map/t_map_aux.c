/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:26:02 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/27 01:09:37 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	init_point(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
	point->c.color = DEFAULT_COLOR;
}

inline void	update_map_height(t_map *map, int point_height)
{
	if (point_height < map->limits.min[Z])
		map->limits.min[Z] = point_height;
	else if (point_height > map->limits.max[Z])
		map->limits.max[Z] = point_height;
}

void	skip_digits_and_set_color(t_point *point, char *line, int *i)
{
	while (line[*i] && ft_strchr(DIGITS_SYMBOLS, line[*i]))
		(*i)++;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] == ',')
	{
		point->c.color = ((ft_atol_16(&line[*i + 3])) << 8) | 0xFF;
		while (line[*i] && line[*i] != ' ')
			(*i)++;
	}
}

void	init_pline(char *line, t_point *points_line, int map_size, t_map *map)
{
	int	i;
	int	point;

	i = 0;
	point = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i] && ft_strchr(DIGITS_SYMBOLS, line[i]))
		{
			init_point(&points_line[point], point, map_size);
			points_line[point].z = ft_atoi(&line[i]);
			update_map_height(map, points_line[point].z);
			skip_digits_and_set_color(&points_line[point], line, &i);
			point++;
		}
		else
		{
			while (line[i] && !ft_isspace(line[i]))
				i++;
		}
	}
}
