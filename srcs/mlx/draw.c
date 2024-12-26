/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:34:16 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 02:33:27 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	draw_cross(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < SCREEN_WIDTH)
	{
		mlx_put_pixel(fdf->img, i, SCREEN_HEIGHT / 2, 0xFF00FF);
		i++;
	}
	while (j < SCREEN_HEIGHT)
	{
		mlx_put_pixel(fdf->img, SCREEN_WIDTH / 2, j, 0xFF00FF);
		j++;
	}
}

t_point	set_point(t_point s, t_camera cam)
{
	t_point	d;

	d.x = s.x * cam.scale + cam.offsets[X];
	d.y = s.y * cam.scale + cam.offsets[Y];
	d.z = s.z;
	d.c.color = s.c.color;
	return (d);
}

void	set_offsets_and_clear_img(t_fdf *fdf)
{
	set_offsets(fdf);
	ft_memset(fdf->img->pixels, 0, fdf->img->width * fdf->img->height * 4UL);
}

void	draw_map(t_fdf *fdf)
{
	int		i;
	int		j;

	set_offsets_and_clear_img(fdf);
	i = -1;
	while (++i < fdf->map.actual_size)
	{
		j = -1;
		while (++j < fdf->map.min_wide)
		{
			if (j < fdf->map.min_wide - 1)
			{
				bresenham_line(fdf, set_point(fdf->map.points[i][j], fdf->cam),
					set_point(fdf->map.points[i][j + 1], fdf->cam)
					);
			}
			if (i < fdf->map.actual_size - 1)
			{
				bresenham_line(fdf, set_point(fdf->map.points[i][j], fdf->cam),
					set_point(fdf->map.points[i + 1][j], fdf->cam)
					);
			}
		}
	}
}
