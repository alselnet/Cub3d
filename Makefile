# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 16:55:17 by aselnet           #+#    #+#              #
#    Updated: 2023/09/03 16:32:10 by aselnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d

LIB_DIR		=	./libft

MLX_DIR		=	./mlx

MLX 		=  ./mlx/libmlx.a

DEPS		=	${OBJS:.o=.d}

LIBFT		=	./libft/libft.a

MAIN		=	./srcs/cub3d.c

CORE		=	./srcs/display.c\
				./srcs/minimap.c\
				./srcs/textures.c\
				./srcs/init.c\
				./srcs/utils.c\
				./srcs/movement.c\
				./srcs/movement2.c\
				./srcs/raycasting.c\
				./srcs/close.c\

PARSING		=	

SRCS		=	${MAIN} ${PARSING} ${CORE}

OBJS		=	${SRCS:.c=.o}

RM			=	rm -f

CC			=	gcc

FLAGS		=	-MMD -Wall -Wextra -Werror -I include/

FLAGS_LIB	= -lXext -lX11

all			: ${NAME}

%.o: %.c
		@${CC} ${FLAGS}  -c $< -o ${<:.c=.o}

${LIBFT}	:
		@echo "\033[35m----Building libft----"
		@make -sC ${LIB_DIR}
		@echo "OK\033[0m"

${MLX}		:
		  @echo "\033[35m----Building MLX----"
		  @make -sC ${MLX_DIR}
		  @echo "OK\033[0m"

${NAME}		: ${OBJS} ${LIBFT} ${MLX}
		@echo "\033[34m----Compiling----"
		@${CC} ${FLAGS} ${OBJS} -L ${MLX_DIR} -lmlx -lm ${FLAGS_LIB} -o ${NAME} ${LIBFT}
		@echo "OK\033[0m"

clean		:
		@echo "\033[31m----Cleaning libft----"
		@make clean -sC ${LIB_DIR}
		@echo "OK"
		@echo "\033[31m----Cleaning MLX----"
		@make clean -sC ${MLX_DIR}
		@echo "OK"
		@echo "\033[31m----Cleaning objects----"
		@${RM} ${OBJS} ${DEPS}
		@echo "OK\033[0m"

fclean		: clean
		@echo "\033[33m----Cleaning all----"
		@${RM} ${NAME}
		@${RM} ${LIBFT}
		@${RM} ${MLX}
		@echo "OK\033[0m"

re			: fclean all

.PHONY		: all clean fclean re

-include $(DEPS)