/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:40:15 by psegura-          #+#    #+#             */
/*   Updated: 2024/07/31 19:40:57 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void    create_point(int nbr, long color)
{
	t_point point;

	ft_bzero(&point, sizeof(point));
	point.color = color;
	point.z = nbr;

	// printf("Point: x[%d] y[%d] z[%d] c[%ld]\n", point.x, point.y, point.z, point.color);
}

void    parse_line(char *str, int line_count)
{
	int		i;
	int 	start;
	int 	space_last;
	int		num;
	long	color;

	i = 0;
	space_last = -1;
	color = 0;
	printf("line %.2d: ", line_count);
	while (str[i])
	{
		if (ft_isspace(str[i]) || str[i] == ',') // Handle spaces and commas
		{
			if (i > space_last + 1) // Ensure there is a number between separators
			{
				start = space_last + 1;
				num = ft_atoi(&str[start]);
				if (str[i] == ',') // Handle the content after the comma
				{
					color = ft_atol_16(&str[i + 3]);
					printf("%d,%ld", num, color);
					while (str[i] && !ft_isspace(str[i]))
						i++;
				}
				else
				// 	printf("%d", num);
				// printf(" ");
				create_point(num, color);
			}
			space_last = i;
		}
		i++;
	}
	// printf("\n");
}

void	create_map(t_map *map)
{
	int		fd;
	char	*line;
	
	fd = open(map->str, O_RDONLY);
	if (fd == -1)
		ft_perror(map->str);

    int line_count = 0;
	init_map(map);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        // ft_dprintf(2, "line %d: %s", line_count, line);
		add_line(map, line);
        // parse_line(line, line_count);
        free(line);
        line_count++;
    }
	close(fd);
}


void	parse_input(int argc, char **argv, t_fdf *fdf)
{
	if (argc != 2)
		ft_error("Invalid number of arguments.");
	fdf->map.str = argv[1];
	create_map(&fdf->map);
}