#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcourrie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 16:16:15 by gcourrie          #+#    #+#              #
#    Updated: 2016/03/22 10:58:38 by gcourrie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=		fdf

SRC_PATH=		./sources/

OBJ_PATH=		./objects/

LIB_PATH=		./minilibx_macos/

INC_PATH=		./includes/

SRC_NAME=		main.c

OBJ_NAME=		$(SRC_NAME:.c=.o)

LIB_NAME=		libmlx.a

LIBFT	=		libft/libft.a

GCC		=		gcc

CFLAGS	=		-Wall -Wextra -Werror

SRC		=		$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ		=		$(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB		=		$(addprefix $(LIB_PATH),$(LIB_NAME))

INC		=		$(addprefix -I,$(INC_PATH))

FLAGS	=		-framework OpenGL -framework AppKit

all:			$(NAME)

$(NAME):		$(OBJ)
				cd $(LIB_PATH); $(MAKE) -f Makefile
				cd libft; $(MAKE) -f Makefile
				$(GCC) $(CFLAGS) -o $(NAME) $(LIB) $(FLAGS) $(OBJ)

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
				$(GCC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
				rm -vf $(OBJ)
				@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
				rm -rvf libft/objects

fclean:			clean
				rm -vf $(NAME)
				rm -vf $(LIB)
				rm -vf $(LIBFT)

re:				fclean all

.PHONY:			all clean fclean re
