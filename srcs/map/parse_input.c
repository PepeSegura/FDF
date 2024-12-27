/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:40:15 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/27 01:05:15 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	check_filename(char *str)
{
	char	*pos_x;
	int		len;

	pos_x = ft_strrchr(str, '.');
	if (pos_x)
		len = ft_strlen(pos_x);
	if (pos_x == str || !pos_x || len != 4 || !ft_strnstr(pos_x, ".fdf", 10))
		ft_error(WRONG_EXT);
}

void	init_map(t_map *map)
{
	map->max_size = 128;
	map->actual_size = 0;
	map->min_wide = INT32_MAX;
	map->points = ft_calloc(map->max_size, sizeof(t_point *));
	if (map->points == NULL)
		ft_error("Malloc failed");
}

void	create_map(t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map->str, O_RDONLY);
	if (fd == -1)
		ft_perror(map->str);
	init_map(map);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		add_line(map, line);
		free(line);
	}
	close(fd);
}

void	calc_screen_ratio(t_fdf *fdf)
{
	double	ratio_width;
	double	ratio_height;

	ratio_width = (double)SCREEN_WIDTH / fdf->map.min_wide;
	ratio_height = (double)SCREEN_HEIGHT / fdf->map.actual_size;
	if (ratio_width < ratio_height)
		fdf->cam.scale = ratio_width;
	else
		fdf->cam.scale = ratio_height;
	fdf->cam.initial_scale = fdf->cam.scale;
}

void	parse_input(int argc, char **argv, t_fdf *fdf)
{
	if (argc != 2)
		ft_error("Invalid number of arguments.");
	fdf->map.str = argv[1];
	check_filename(fdf->map.str);
	create_map(&fdf->map);
	if (fdf->map.min_wide == INT32_MAX)
		ft_error("Empty map");
	calc_screen_ratio(fdf);
}
