/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:26:02 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/27 01:09:55 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	resize_map(t_map *map)
{
	t_point	**new_points;
	int		i;

	map->max_size = map->max_size << 1;
	new_points = ft_calloc(map->max_size, sizeof(t_point *));
	if (new_points == NULL)
		ft_error("Malloc failed");
	i = 0;
	while (i < map->actual_size)
	{
		new_points[i] = map->points[i];
		i++;
	}
	free(map->points);
	map->points = new_points;
}

int	count_points(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '\n')
	{
		if (ft_strchr(VALID_CHARS, str[i]) == NULL)
			ft_error("Invalid CHAR");
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] && ft_strchr(DIGITS_SYMBOLS, str[i]))
		{
			count++;
			while (str[i] && !ft_isspace(str[i]))
				i++;
		}
		else if (str[i] == '\0' || str[i] == '\n')
			break ;
		else
			ft_error("Invalid CHAR");
	}
	return (count);
}

void	add_line(t_map *map, char *line)
{
	int		size_line;
	t_point	*points_line;

	if (map->actual_size == map->max_size)
		resize_map(map);
	size_line = count_points(line);
	if (size_line == 0)
		ft_error("There is an empty line");
	if (size_line < map->min_wide)
		map->min_wide = size_line;
	points_line = ft_calloc(size_line, sizeof(t_point));
	if (points_line == NULL)
		ft_error("Malloc failed");
	init_pline(line, points_line, map->actual_size, map);
	map->points[map->actual_size] = points_line;
	map->actual_size++;
}
