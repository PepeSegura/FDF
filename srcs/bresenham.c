/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:30:53 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/25 23:41:00 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static void plot_point(t_fdf *fdf, int x, int y, long color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		// printf("(%d, %d) %ld\n", x, y, color);
		mlx_put_pixel(fdf->img, x, y, color);
	}
	// else
	// {
	// 	printf("Out of screen: (%d, %d) %ld\n", x, y, color);
	// }
}

static inline int	get_step(double a, double b)
{
	if (a < b)
		return (1);
	return (-1);
}

static inline t_bresenham init_struct(t_point a, t_point b)
{
	t_bresenham bresenham = {
		.dx = fabs(b.x - a.x),
		.dy = fabs(b.y - a.y),
		.sx = get_step(a.x, b.x),
		.sy = get_step(a.y, b.y),
		};

	bresenham.err = bresenham.dx - bresenham.dy;
	bresenham.err2 = bresenham.err * 2;
	if (bresenham.dx > bresenham.dy)
		bresenham.total_steps = bresenham.dx;
	else
		bresenham.total_steps = bresenham.dy;
	bresenham.current_step = 0;
	return (bresenham);
}

static inline int check_points(t_point a, t_point b)
{
	if ((b.x < 0.0 && a.x < 0.0) || (b.y < 0.0 && a.y < 0.0))
		return (1);
	if (b.x > SCREEN_WIDTH && a.x > SCREEN_WIDTH)
		return (1);
	if (b.y > SCREEN_HEIGHT && a.y > SCREEN_HEIGHT)
		return (1);
	return (0);
}

typedef struct s_channel{
	const int r;
	const int g;
	const int b;
} t_channel;

inline t_channel init_channel(long color)
{
	const t_channel channel = {
		.r = ((color >> 16) & 0xFF),
		.g = ((color >> 8) & 0xFF),
		.b = (color & 0xFF)
		};

	return (channel);
}

// Function to interpolate between two colors
static long interpolate_color(long color1, long color2, float t)
{
	const t_channel c1 = init_channel(color1);
	const t_channel c2 = init_channel(color2);
	const int r = c1.r + (int)((c2.r - c1.r) * t);
	const int g = c1.g + (int)((c2.g - c1.g) * t);
	const int b = c1.b + (int)((c2.b - c1.b) * t);

	return (r << 16) | (g << 8) | b;
}

// Bresenham's Line Algorithm with Color Gradient
void bresenham_line(t_fdf *fdf, t_point a, t_point b)
{
    t_bresenham	bre;
    float		t;
    if (check_points(a, b) == 1)
        return;
    bre = init_struct(a, b);
    while (1)
    {
        t = (float)bre.current_step / bre.total_steps;
        plot_point(fdf, (int)a.x, (int)a.y, interpolate_color(a.color, b.color, t));
		if (abs((int)a.x - (int)b.x) <= 1 && abs((int)a.y - (int)b.y) <= 1)
            break;
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
