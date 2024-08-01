/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:14:53 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/01 20:54:00 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

const double (*get_projection_array(void))[3]
{
    static const double projection_array[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 0},
    };

    return (projection_array);
}

const double (*get_rotate_x_array(void))[3]
{
    static const double rotate_x_array[3][3] = {
        {1, 0, 0},
        {0, cos(ROTATE_ANGLE), -sin(ROTATE_ANGLE)},
        {0, sin(ROTATE_ANGLE), cos(ROTATE_ANGLE)}
    };

    return (rotate_x_array);
}

const double (*get_rotate_y_array(void))[3]
{
    static const double rotate_y_array[3][3] = {
        {cos(ROTATE_ANGLE), 0, sin(ROTATE_ANGLE)},
        {0, 1, 0},
        {-sin(ROTATE_ANGLE), 0, cos(ROTATE_ANGLE)}
    };

    return (rotate_y_array);
}

const double (*get_rotate_z_array(void))[3]
{
    static const double rotate_z_array[3][3] = {
        {cos(ROTATE_ANGLE), -sin(ROTATE_ANGLE), 0},
        {sin(ROTATE_ANGLE), cos(ROTATE_ANGLE), 0},
        {0, 0, 1}
    };

    return (rotate_z_array);
}

t_point    mult_matrix(const double matrix[3][3], t_point point)
{
    t_point result;

    ft_bzero(&result, sizeof(t_point));
    result.x = (matrix[0][0] * point.x) + (matrix[0][1] * point.y) + (matrix[0][2] * point.z);
    result.y = (matrix[1][0] * point.x) + (matrix[1][1] * point.y) + (matrix[1][2] * point.z);
    result.z = (matrix[2][0] * point.x) + (matrix[2][1] * point.y) + (matrix[1][2] * point.z);
    return (result);
}
