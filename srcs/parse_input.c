/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:40:15 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/03 01:04:59 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

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
	printf("SWIDE:   %f / %d = %f\n", (double)SCREEN_WIDTH, fdf->map.min_wide, ratio_width);
	printf("SHEIGHT: %f / %d = %f\n", (double)SCREEN_HEIGHT, fdf->map.actual_size, ratio_height);
	if (ratio_width < ratio_height)
		fdf->cam.grid_space = ratio_width;
	else
		fdf->cam.grid_space = ratio_height;
	printf("SCREEN_RATIO: %f\n", fdf->cam.grid_space);
}

void	parse_input(int argc, char **argv, t_fdf *fdf)
{
	if (argc != 2)
		ft_error("Invalid number of arguments.");
	fdf->map.str = argv[1];
	create_map(&fdf->map);
	if (fdf->map.min_wide == INT32_MAX)
		ft_error("Empty map");
	calc_screen_ratio(fdf);
}
