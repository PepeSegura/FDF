/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:14:53 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/26 23:57:24 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

inline double	rad(double deg)
{
	return (deg * M_PI / 180);
}

// const double	(*get_projection(void))[3]
// {
// 	static const double	projection_array[3][3] = {
// 	{1, 0, 0},
// 	{0, 1, 0},
// 	{0, 0, 1}
// 	};

// 	return (projection_array);
// }

const double	(*g_get_rot_x(double angle))[3]
{
	static double	rotate_x_array[3][3];

	rotate_x_array[0][0] = 1;
	rotate_x_array[0][1] = 0;
	rotate_x_array[0][2] = 0;
	rotate_x_array[1][0] = 0;
	rotate_x_array[1][1] = cos(angle);
	rotate_x_array[1][2] = -sin(angle);
	rotate_x_array[2][0] = 0;
	rotate_x_array[2][1] = sin(angle);
	rotate_x_array[2][2] = cos(angle);
	return ((const double (*)[3])rotate_x_array);
}

const double	(*g_get_rot_y(double angle))[3]
{
	static double	rotate_y_array[3][3];

	rotate_y_array[0][0] = cos(angle);
	rotate_y_array[0][1] = 0;
	rotate_y_array[0][2] = -sin(angle);
	rotate_y_array[1][0] = 0;
	rotate_y_array[1][1] = 1;
	rotate_y_array[1][2] = 0;
	rotate_y_array[2][0] = sin(angle);
	rotate_y_array[2][1] = 0;
	rotate_y_array[2][2] = cos(angle);
	return ((const double (*)[3])rotate_y_array);
}

const double	(*g_get_rot_z(double angle))[3]
{
	static double	rotate_z_array[3][3];

	rotate_z_array[0][0] = cos(rad(angle));
	rotate_z_array[0][1] = -sin(rad(angle));
	rotate_z_array[0][2] = 0;
	rotate_z_array[1][0] = sin(rad(angle));
	rotate_z_array[1][1] = cos(rad(angle));
	rotate_z_array[1][2] = 0;
	rotate_z_array[2][0] = 0;
	rotate_z_array[2][1] = 0;
	rotate_z_array[2][2] = 1;
	return ((const double (*)[3])rotate_z_array);
}

t_point	mul_mat(const double m[3][3], t_point p)
{
	t_point	result;

	ft_bzero(&result, sizeof(t_point));
	result.x = (m[0][0] * p.x) + (m[0][1] * p.y) + (m[0][2] * p.z);
	result.y = (m[1][0] * p.x) + (m[1][1] * p.y) + (m[1][2] * p.z);
	result.z = (m[2][0] * p.x) + (m[2][1] * p.y) + (m[2][2] * p.z);
	result.c.color = p.c.color;
	return (result);
}
