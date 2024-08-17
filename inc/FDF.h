/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:42:44 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/17 22:37:07 by psegura-         ###   ########.fr       */
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

# define FILE_EXT ".fdf"

# define DEFAULT_COLOR 0xFF0000FF

# define BPP sizeof(int32_t)

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800

# define ANGLE (M_PI / 4)
# define PI		3.14
# define PI2	6.18
# define PI05	1.57
# define PI025	0.78

typedef struct s_point
{
	double	x;
	double 	y;
	double 	z;
	long	color;
}   t_point;

typedef struct s_map_limits
{
	int	min_x;
	int	min_y;
	int	max_x;
	int	max_y;
}	t_map_limits;

typedef struct s_map
{
	t_point 		**points;
	int				min_wide;
	int				max_size;
	int				actual_size;
	char			*str;
	t_map_limits	limits;
}   t_map;

typedef struct s_offset
{
	int	center_x;
	int	center_y;
	int	min_x;
	int	min_y;
	int	max_x;
	int	max_y;
	int	x;
	int	y;
}	t_offset;


typedef struct s_camera
{
	t_offset	offset;
	
	int			offset_x;
	int			offset_y;

	double		scale;

	// TEST
	double		x_deg;
	double		y_deg;
	double		z_deg;
	double		depth_change;
	// TEST
}	t_camera;

typedef struct s_fdf
{
	t_map   	map;
	t_camera	cam;
	mlx_image_t	*img;
}   t_fdf;


/* DELETEEE */
void draw_map2(t_fdf *fdf);

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

/* point_tools.c */
t_point scale_point(t_point p, double scale);
t_point offset_point(t_point p, t_fdf *fdf);
t_point scale_and_offset(t_point p, t_fdf *fdf);

/* projection.c */
t_point isometric(t_point p, t_fdf *fdf);

/* map_limits.c */
void    set_map_limits(t_map *map, double scale, t_fdf *fdf);
void    set_map_offsets(t_fdf *fdf);

/* draw.c */
void    draw_map(t_fdf *fdf);

/* hooks.c */
void    my_key_hook(mlx_key_data_t keydata, void* param);
void	my_scrollhook(double xdelta, double ydelta, void *param);
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
} t_bresenham;

void bresenham_line(t_fdf *fdf, t_point a, t_point b);

/* errors.c */
void	ft_perror(char *msg);
void	ft_error(char *str);

#endif