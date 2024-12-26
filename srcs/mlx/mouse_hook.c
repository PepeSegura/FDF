/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:02:50 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 02:33:46 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	(void)xdelta;
	if (ydelta > 0)
	{
		ft_printf("Scroll Up (Zoom In)\n");
		((t_fdf *)param)->cam.scale *= 1.2;
	}
	else if (ydelta < 0)
	{
		ft_printf("Scroll Down (Zoom Out)\n");
		((t_fdf *)param)->cam.scale *= 0.8;
	}
	draw_map((t_fdf *)param);
}
