/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:42:44 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 01:44:05 by psegura-         ###   ########.fr       */
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
# include "keys.h"

# define FILE_EXT ".fdf"

# define DEFAULT_COLOR 0x6a5de2FF

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800

# define PI		3.14
# define PI2	6.18
# define PI05	1.57
# define PI025	0.78

# define WRONG_EXT "Map extension is not \".fdf\""

# define R 3
# define G 2
# define B 1
# define A 0
# define ABGR 4

typedef union u_color
{
	uint32_t	color;
	uint8_t		channels[ABGR];
}	t_color;

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
	t_color		c;
}	t_point;

# define X 0
# define Y 1
# define Z 2
# define XYZ 3

typedef struct s_map_limits
{
	int min[XYZ];
	int max[XYZ];
}	t_map_limits;

typedef struct s_map
{
	t_point			**points;
	int				min_wide;
	int				max_size;
	int				actual_size;
	char			*str;
	t_map_limits	limits;
}	t_map;

typedef struct s_camera
{
	int			offsets[2];
	int			key_offset[2];
	double		scale;
	double		initial_scale;

	// TEST
	double		x_deg;
	double		y_deg;
	double		z_deg;
	double		depth_change;
	// TEST
}	t_camera;

typedef struct s_fdf
{
	t_map		map;
	t_camera	cam;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_fdf;

/* parse_input.c */
void	parse_input(int argc, char **argv, t_fdf *fdf);

/* t_map.c */
void	print_map(t_map *map);
void	init_map(t_map *map);
void	add_line(t_map *map, char *line);

/* matrix.c */
const double	(*get_projection(void))[3];
const double	(*get_rot_x(double angle))[3];
const double	(*get_rot_y(double angle))[3];
const double	(*get_rot_z(double angle))[3];
t_point	mul_mat(const double matrix[3][3], t_point point);

/* modify_map.c */
void	rotate_map(t_map *map);

/* projection.c */
t_point	isometric(t_point p, t_fdf *fdf);

/* map_limits.c */
void	set_offsets(t_fdf *fdf);

/* draw.c */
void	draw_map(t_fdf *fdf);

/* hooks.c */
void	my_key_hook(mlx_key_data_t keydata, void *param);
void	my_scrollhook(double xdelta, double ydelta, void *param);

/* hook_tools.c*/
bool	number_in_array(int len, const int array[len], int to_find);

/* interpolate_color.c */
uint32_t	inter(uint32_t color1, uint32_t color2, float t);

/* bresenham.c */
typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
	int	total_steps;
	int	current_step;
}	t_bresenham;

void	bresenham_line(t_fdf *fdf, t_point a, t_point b);

/* errors.c */
void	ft_perror(char *msg);
void	ft_error(char *str);

#endif
