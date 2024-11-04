/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:01:05 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/17 13:20:05 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

// atan(sqrt(2))
#define ATANSQR_2 0.955316618

t_point isometric(t_point p, t_fdf *fdf)
{
    double		x_deg;
	double		z_deg;

    fdf->cam.depth_change = 1;
	p.z = p.z * fdf->cam.depth_change;
    z_deg = 45;
	x_deg = ATANSQR_2;
    p = mul_mat(get_rot_z(z_deg), p);
    p = mul_mat(get_rot_x(x_deg), p);
    fdf->cam.z_deg = z_deg;
	fdf->cam.x_deg = x_deg;
	fdf->cam.y_deg = 0;
    return (p);
}
