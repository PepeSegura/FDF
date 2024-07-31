/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:26:02 by psegura-          #+#    #+#             */
/*   Updated: 2024/07/31 19:54:47 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	init_map(t_map *map)
{
	map->max_size = 128;
	map->actual_size = 0;
	map->points = ft_calloc(map->max_size, sizeof(t_point *));
	if (map->points == NULL)
		ft_error("Malloc failed");
}

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
		while (str[i] && ft_isspace(str[i]))
		{
			i++;
		}
		if (str[i] && (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '+'))
		{
			count++;
			while (str[i] && !ft_isspace(str[i]))
			{
				i++;
			}
		}
	}
	printf("SIZE_LINE: %d\n", count);
	return (count);
}

void	init_points_line(char *line, t_point *points_line, int size_line)
{
	int	i;

	i = 0;
	/* TODO: function*/
}


void	add_line(t_map *map, char *line)
{
	int		size_line;
	t_point	*points_line;

	if (map->actual_size == map->max_size)
		resize_map(map);

	size_line = count_points(line);
	points_line = ft_calloc(size_line, sizeof(t_point));
	if (points_line == NULL)
		ft_error("Malloc failed");
	points_line = init_points_line(line, points_line, size_line);
	map->points[map->actual_size] = points_line;
	(void)line;
	map->actual_size++;
}
