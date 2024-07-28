#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42/MLX42.h"

typedef struct s_point
{
    float x;
    float y;
    float z;
    long color;
}   t_point;


/* mlx_tools.c */
int get_rgba(int r, int g, int b, int a);
int get_r(int rgba);
int get_g(int rgba);
int get_b(int rgba);
int get_a(int rgba);

#endif