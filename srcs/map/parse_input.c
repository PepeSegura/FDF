/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:40:15 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/24 16:40:39 by psegura-         ###   ########.fr       */
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
	printf("fd: %d\n", fd);
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
	printf("SWIDE:   %f / %d = %f\n", (double)SCREEN_WIDTH, fdf->map.min_wide,
		ratio_width);
	printf("SHEIGHT: %f / %d = %f\n", (double)SCREEN_HEIGHT,
		fdf->map.actual_size, ratio_height);
	if (ratio_width < ratio_height)
		fdf->cam.scale = ratio_width;
	else
		fdf->cam.scale = ratio_height;
	fdf->cam.initial_scale = fdf->cam.scale;
	printf("SCREEN_RATIO: %f\n", fdf->cam.scale);
}

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

void	parse_input(int argc, char **argv, t_fdf *fdf)
{
	if (argc != 2)
		ft_error("Invalid number of arguments.");
	printf("filename: %s\n", argv[1]);
	fdf->map.str = argv[1];
	check_filename(fdf->map.str);
	create_map(&fdf->map);
	if (fdf->map.min_wide == INT32_MAX)
		ft_error("Empty map");
	calc_screen_ratio(fdf);
}
