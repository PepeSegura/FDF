/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:34:16 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 15:08:31 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

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
