/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:34:57 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/26 00:50:46 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
    t_fdf	*fdf;

	(void)xdelta, (void)ydelta, (void)param;
	fdf = (t_fdf *)param;
	// Simple up or down detection
	if (ydelta > 0) // Scroll Up (Zoom In)
	{
		puts("Zooming In!");
		fdf->cam.scale *= 1.2; // Increase grid space by 20%
	}
	else if (ydelta < 0) // Scroll Down (Zoom Out)
	{
		puts("Zooming Out!");
		fdf->cam.scale /= 1.2; // Decrease grid space by 20%
	}
	// Redraw the map with the updated scale
	draw_map(fdf);
}

int key_is_allowed(int keynum)
{
    const int allowed_keys[8] = {
        MLX_KEY_ESCAPE, MLX_KEY_SLASH, MLX_KEY_RIGHT_BRACKET,
        MLX_KEY_R, MLX_KEY_RIGHT, MLX_KEY_LEFT,
        MLX_KEY_UP, MLX_KEY_DOWN
    };

    int i = 0;
    while (i < 8)
    {
        if (keynum == allowed_keys[i])
            return (1);
        i++;
    }
    printf("Invalid key %d\n", keynum);
    return (0);
}

void    my_key_hook(mlx_key_data_t keydata, void* param)
{
    (void)param;
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        printf("Escape!\n");
        mlx_terminate(fdf->mlx);
        exit(1);
    }
    else if (keydata.key == MLX_KEY_SLASH && keydata.action == MLX_PRESS)
        printf("Scale UP!\n");
    else if (keydata.key == MLX_KEY_RIGHT_BRACKET && keydata.action == MLX_PRESS)
        printf("Scale DOWN!\n");
    else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
    {
        printf("RESET!\n");
        memset(&fdf->cam.key_offset, 0, sizeof(int[2]));
        fdf->cam.scale = fdf->cam.initial_scale;
    }
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
    {
        printf("Moving right!\n");
        fdf->cam.key_offset[X] += SCREEN_WIDTH / 10;
    }
    else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
    {
        printf("Moving left!\n");
        fdf->cam.key_offset[X] -= SCREEN_WIDTH / 10;
    }
    else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
    {
        printf("Moving up!\n");
        fdf->cam.key_offset[Y] -= SCREEN_HEIGHT / 10;
    }
    else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
    {
        printf("Moving down!\n");
        fdf->cam.key_offset[Y] += SCREEN_HEIGHT / 10;
    }
    // Redraw the map with the updated scale
    if (key_is_allowed(keydata.key))
	    draw_map(fdf);
}
