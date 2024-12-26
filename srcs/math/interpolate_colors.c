/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:30:53 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/25 13:42:08 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

static inline int	interpolate_channel(int start, int end, float t)
{
	return (start + (int)((end - start) * t));
}

uint32_t	inter(uint32_t color1, uint32_t color2, float t)
{
	const uint8_t	*c1 = (uint8_t *)&color1;
	const uint8_t	*c2 = (uint8_t *)&color2;
	const t_color	new_color = {
		.channels[R] = interpolate_channel(c1[R], c2[R], t),
		.channels[G] = interpolate_channel(c1[G], c2[G], t),
		.channels[B] = interpolate_channel(c1[B], c2[B], t),
		.channels[A] = interpolate_channel(c1[A], c2[A], t),
	};

	if (t != t || t == 1.0f || color1 == color2)
		return (color1);
	return (new_color.color);
}
