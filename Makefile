# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/22 06:44:10 by Cutku             #+#    #+#              #
#    Updated: 2023/05/13 01:49:24 by Cutku            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_COLOR = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;32m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

.SILENT:

SO_LNG_SRCS	=	main.c init_map.c error_check.c clean_up.c queue.c bfs.c images.c objects.c player.c
SO_LNG_OBJS	=	$(SO_LNG_SRCS:.c=.o)

SO_LNG_BNUS_SRCS = so_long_bonus/main.c so_long_bonus/init_map.c so_long_bonus/error_check.c \
				so_long_bonus/clean_up.c so_long_bonus/queue.c so_long_bonus/bfs.c \
				so_long_bonus/images.c so_long_bonus/objects.c so_long_bonus/player.c so_long_bonus/enemy.c
SO_LNG_BNUS_OBJS = $(SO_LNG_BNUS_SRCS:.c=.o)

LIBFT		= ./libft/
LIBFT_LIB	= ./libft/libft.a

MLX42		= MLX42/build
MLX42_LIB	= MLX42/build/libmlx42.a

CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra

NAME		= so_long

all: $(NAME)

$(LIBFT_LIB):
	make bonus -C $(LIBFT) && make clean -C $(LIBFT)
	echo "$(GREEN)Libft compiled successfully!$(DEF_COLOR)"

$(NAME): $(SO_LNG_OBJS) $(LIBFT_LIB) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(SO_LNG_OBJS) $(LIBFT_LIB) $(MLX42_LIB) -o $(NAME) -I MLX42/include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
	echo "$(GREEN)So_long compiled successfully!$(DEF_COLOR)"

$(MLX42_LIB):
	(cd MLX42 && cmake -B build)
	make -C $(MLX42)

clean:
	$(RM) $(SO_LNG_OBJS)
	$(RM) $(SO_LNG_BNUS_OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)

re:	fclean all

bonus: $(SO_LNG_BNUS_OBJS) $(LIBFT_LIB) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(SO_LNG_BNUS_OBJS) $(LIBFT_LIB) $(MLX42_LIB) -o $(NAME) -I MLX42/include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
	echo "$(GREEN)So_long_bonus compiled successfully!$(DEF_COLOR)"

.PHONY:	all clean fclean re bonus