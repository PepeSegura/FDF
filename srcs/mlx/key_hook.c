/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:34:57 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 02:33:40 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	apply_translation(t_fdf *fdf, int dir)
{
	if (dir == UP)
		fdf->cam.key_offset[Y] -= SCREEN_HEIGHT / 10;
	else if (dir == DOWN)
		fdf->cam.key_offset[Y] += SCREEN_HEIGHT / 10;
	else if (dir == LEFT)
		fdf->cam.key_offset[X] -= SCREEN_WIDTH / 10;
	else if (dir == RIGHT)
		fdf->cam.key_offset[X] += SCREEN_WIDTH / 10;
}

void	reset_view(t_fdf *fdf)
{
	ft_printf("RESET!\n");
	ft_memset(&fdf->cam.key_offset, 0, sizeof(int [2]));
	fdf->cam.scale = fdf->cam.initial_scale;
}

void	apply_scale(t_fdf *fdf, int scale)
{
	(void)fdf;
	if (scale == PLUS)
	{
		ft_printf("Scale UP!\n");
	}
	else if (scale == MINUS)
	{
		ft_printf("Scale DOWN!\n");
	}
}

void	exit_fdf(t_fdf *fdf)
{
	ft_printf("Escape!\n");
	mlx_terminate(fdf->mlx);
	exit(0);
}

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	const int	keys[8] = {ESC, RESET, MINUS, PLUS, RIGHT, LEFT, UP, DOWN};
	t_fdf		*fdf;

	fdf = (t_fdf *)param;
	if (!number_in_array(8, keys, keydata.key))
		return ;
	if (!number_in_array(2, (int []){MLX_PRESS, MLX_REPEAT}, keydata.action))
		return ;
	if (keydata.key == ESC)
		exit_fdf(fdf);
	else if (keydata.key == RESET)
		reset_view(fdf);
	else if (number_in_array(2, (int []){MINUS, PLUS}, keydata.key))
		apply_scale(fdf, keydata.key);
	else if (number_in_array(4, (int []){RIGHT, LEFT, UP, DOWN}, keydata.key))
		apply_translation(fdf, keydata.key);
	draw_map(fdf);
}
