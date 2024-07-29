/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/07/29 17:48:05 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

int	main(int argc, char **argv)
{
    t_fdf   fdf;
	// int		fd;
	// char	*line;
    ft_bzero(&fdf, sizeof(fdf));
    parse_input(argc, argv, &fdf);
    printf("INPUT %s\n", fdf.map.str);
// 	fd = open(argv[1], O_RDONLY);
//     int line_count = 0;
//     while (1)
//     {
//         line = get_next_line(fd);
//         if (!line)
//             break;
//         // ft_dprintf(1, "%s", line);
//         parse_line(line, line_count);
//         free(line);
//         line_count++;
//     }
// 	close(fd);
}
