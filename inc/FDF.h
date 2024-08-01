/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:42:44 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/01 22:02:10 by psegura-         ###   ########.fr       */
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

# define ROTATE_ANGLE (M_PI / 4)
// # define ROTATE_ANGLE 0.2

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
const double (*get_projection_array(void))[3];
const double (*get_rotate_x_array(void))[3];
const double (*get_rotate_y_array(void))[3];
const double (*get_rotate_z_array(void))[3];
t_point    mult_matrix(const double matrix[3][3], t_point point);

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