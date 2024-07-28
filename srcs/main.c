/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/07/28 21:01:27 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void	ft_error(char *str)
{
	ft_dprintf(2, "Error:\n\t%s\n", str);
	exit(EXIT_FAILURE);
}

void parse_line(char *str, int line_count)
{
    (void)line_count;
    int i;
    int start;
    int space_last = -1;

    i = 0;
    while (str[i])
    {
        if (ft_isspace(str[i]) || str[i] == ',') // Handle spaces and commas
        {
            if (i > space_last + 1) // Ensure there is a number between separators
            {
                start = space_last + 1;
                int num = ft_atoi(&str[start]);
                (void)num;

                if (str[i] == ',') // Handle the content after the comma
                {
                    long color = ft_atol_16(&str[i + 3]);
                    (void)color;
                    printf("%d,%ld", num, color);
                    while (str[i] && !ft_isspace(str[i]))
                    {
                        i++;
                    }
                }
                else
                    printf("%d", num);
                printf(" ");
            }
            space_last = i;
        }
        i++;
    }
    printf("\n");
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
		ft_error("Invalid number of arguments.");
	fd = open(argv[1], O_RDONLY);
    int line_count = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        // ft_dprintf(1, "%s", line);
        parse_line(line, line_count);
        free(line);
        line_count++;
    }
	close(fd);
}
