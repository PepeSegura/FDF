/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:04:39 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/17 22:26:14 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

t_point scale_point(t_point p, double scale)
{
    return ((t_point){
        p.x * scale,
        p.y * scale,
        p.z * scale,
        p.color
    });
}

t_point offset_point(t_point p, t_fdf *fdf)
{
    t_point new_p;

    new_p = isometric(p, fdf);
    return ((t_point){
        new_p.x + fdf->cam.offset_x,
        new_p.y + fdf->cam.offset_y,
        new_p.z,
        new_p.color
    });
}

t_point scale_and_offset(t_point p, t_fdf *fdf)
{
    return (offset_point(scale_point(p, fdf->cam.scale), fdf));
}
