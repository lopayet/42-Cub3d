NAME		=	cub3D
CFLAGS		=	-Wall -Wextra -Werror
CC			=	cc
MAKE		=	make

HEADERS		=	include/cub3d.h
INCLUDE		=	-I ./include -I $(MLX_DIR) -I $(LIBFT_DIR)
OBJS		=	$(patsubst %.c,%.o,$(SRCS))
SRCS		=	./src/cub3d.c ./src/common_utils.c ./src/events.c \
				./src/parsing/parse.c ./src/parsing/get_data.c \
				./src/parsing/get_data_utils.c ./src/parsing/parse_utils.c \
				./src/parsing/get_map.c ./src/parsing/get_map_size.c \
				./src/parsing/format_check.c ./src/parsing/map_check.c \
				./src/render/render_utils.c ./src/render/draw_line.c ./src/render/minimap.c \
				./src/draw_ray/calc_ray.c ./src/draw_ray/check_horizontal.c ./src/draw_ray/check_vertical.c \
				./src/draw_ray/init_player.c ./src/draw_ray/draw3d.c \
				./src/controls.c ./src/render/texture.c ./src/render/background.c
MLX_DIR		=	./minilibx
MLX			=	$(MLX_DIR)/libmlx_Linux.a

LIBFT_DIR		=	./libft
LIBFT			=	$(LIBFT_DIR)/libft.a

LIBS_DIR	=	-L $(MLX_DIR) -L $(LIBFT_DIR)
LIBS		=	-lft -lmlx -lX11 -lXext -lm

all :
	make -C $(LIBFT_DIR)
	make $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS_DIR) $(LIBS)

%.o : %.c $(HEADERS) Makefile $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean :
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
