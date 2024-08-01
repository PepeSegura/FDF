/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:59:08 by psegura-          #+#    #+#             */
/*   Updated: 2024/08/01 17:30:38 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	ft_perror(char *msg)
{
	ft_dprintf(2, "Error:\n\t");
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_error(char *str)
{
	ft_dprintf(2, "Error:\n\t%s\n", str);
	exit(EXIT_FAILURE);
}
