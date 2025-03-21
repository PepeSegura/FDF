MAKEFLAGS	= --no-print-directory #--silent

NAME	 = fdf

CFLAGS	 =	-Wextra -Wall -Werror #-Wunreachable-code
CFLAGS	 += -I inc
CFLAGS	 += -I libft
CFLAGS	 += -O3

DEBUG	 =	#-g3 -fsanitize=address

CPPFLAGS =	-MMD

LIBMLX	= ./libs/MLX42
LIBFT	= ./libs/libft

HEADERS = -I ./inc -I $(LIBMLX)/include -I $(LIBFT)/inc

LIBS	=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBS	+=	$(LIBFT)/libft.a


SRCS =									\
		srcs/main.c						\
										\
		srcs/map/parse_input.c			\
		srcs/map/t_map.c				\
		srcs/map/t_map_aux.c			\
		srcs/map/map_limits.c			\
										\
		srcs/math/matrix.c				\
		srcs/math/interpolate_colors.c	\
		srcs/math/bresenham.c			\
		srcs/math/isometric.c			\
										\
		srcs/mlx/draw.c					\
		srcs/mlx/hooks.c				\
		srcs/mlx/hooks_tools.c			\
										\
		srcs/other/errors.c				\


OBJS = $(patsubst srcs/%.c, objs/srcs/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

MLX_LIB = $(LIBMLX)/build/libmlx42.a

$(MLX_LIB):
	@cmake -DDEBUG=0 $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

LIBFT_LIB = $(LIBFT)/libft.a

$(LIBFT_LIB):
	@make -C $(LIBFT)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	@$(CC) $(DEBUG) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && printf "Linking: $(NAME)\n"

objs/srcs/%.o: ./srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf objs
	@rm -rf $(LIBMLX)/build
	@make fclean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME) objs

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re libmlx libft
