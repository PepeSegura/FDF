/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:42:44 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/02 17:57:21 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "MLX42/MLX42.h"

# define DEFAULT_COLOR 0xFF0000FF

#define BPP sizeof(int32_t)

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

# define ANGLE (M_PI / 4)

typedef struct s_point
{
	int		x;
	int 	y;
	int 	z;
	long	color;
}   t_point;

typedef struct s_map
{
	t_point **points;
	int		min_wide;
	int		max_size;
	int		actual_size;
	char	*str;
}   t_map;

typedef struct s_fdf
{
	t_map   map;
}   t_fdf;

/* parse_input.c */
void	parse_input(int argc, char **argv, t_fdf *fdf);
void	parse_line(char *str, int line_count);

/* t_map.c */
void	print_map(t_map *map);
void	init_map(t_map *map);
void	add_line(t_map *map, char *line);

/* matrix.c */
const double	(*get_projection(void))[3];
const double	(*get_rot_x(double angle))[3];
const double	(*get_rot_y(double angle))[3];
const double	(*get_rot_z(double angle))[3];
t_point			mul_mat(const double matrix[3][3], t_point point);

/* modify_map.c */
void	rotate_map(t_map *map);

/* mlx_tools.c */
int get_rgba(int r, int g, int b, int a);
int get_r(int rgba);
int get_g(int rgba);
int get_b(int rgba);
int get_a(int rgba);

/* errors.c */
void	ft_perror(char *msg);
void	ft_error(char *str);

#endif