/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:30:53 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/25 13:40:23 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

// printf("(%d, %d) %u\n", x, y, color);
static void	plot_point(t_fdf *fdf, int x, int y, uint32_t color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(fdf->img, x, y, (uint32_t)color);
	}
}

static inline int	get_step(double a, double b)
{
	if (a < b)
		return (1);
	return (-1);
}

static inline int	check_points(t_point a, t_point b)
{
	if ((b.x < 0.0 && a.x < 0.0) || (b.y < 0.0 && a.y < 0.0))
		return (1);
	if (b.x > SCREEN_WIDTH && a.x > SCREEN_WIDTH)
		return (1);
	if (b.y > SCREEN_HEIGHT && a.y > SCREEN_HEIGHT)
		return (1);
	return (0);
}

static inline t_bresenham	init_struct(t_point a, t_point b)
{
	t_bresenham	bresenham;

	ft_memset(&bresenham, 0, sizeof(t_bresenham));
	bresenham.dx = fabs(b.x - a.x);
	bresenham.dy = fabs(b.y - a.y);
	bresenham.sx = get_step(a.x, b.x);
	bresenham.sy = get_step(a.y, b.y);
	bresenham.err = bresenham.dx - bresenham.dy;
	bresenham.current_step = 0;
	if (bresenham.dx > bresenham.dy)
		bresenham.total_steps = bresenham.dx;
	else
		bresenham.total_steps = bresenham.dy;
	return (bresenham);
}

// Bresenham's Line Algorithm with Color Gradient
void	bresenham_line(t_fdf *fdf, t_point a, t_point b)
{
	t_bresenham	bre;
	float		t;

	if (check_points(a, b) == 1)
		return ;
	bre = init_struct(a, b);
	while (1)
	{
		t = (float)bre.current_step / bre.total_steps;
		plot_point(fdf, (int)a.x, (int)a.y, inter(a.c.color, b.c.color, t));
		if (abs((int)a.x - (int)b.x) <= 1 && abs((int)a.y - (int)b.y) <= 1)
			break ;
		bre.err2 = bre.err * 2;
		if (bre.err2 > -bre.dy)
		{
			bre.err -= bre.dy;
			a.x += bre.sx;
		}
		if (bre.err2 < bre.dx)
		{
			bre.err += bre.dx;
			a.y += bre.sy;
		}
		bre.current_step++;
	}
}
