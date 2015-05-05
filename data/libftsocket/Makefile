# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgundlac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/11 02:34:50 by fgundlac          #+#    #+#              #
#    Updated: 2015/04/03 16:08:58 by fgundlac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Werror -Wextra -g
NAME = libftsocket.a
PATH_INC = includes
PATH_OBJ = obj
PATH_SRC = srcs

SRC +=	\
		io_socket.c \

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all : $(NAME)

$(NAME) : namemes $(OBJ)
	@ ar -rc $@ $(OBJ)
	@ ranlib $(NAME)
	@ echo " \033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.c)
	@ echo -n .
	@ mkdir -p $(PATH_OBJ)
	@ $(CC) $(CFLAGS) -o $@ -c $^ -I $(PATH_INC)

clean :
	@ rm -rf $(PATH_OBJ)
	@ echo "Cleaning $(NAME) \
		\033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

fclean : clean
	@ rm -f $(NAME)
	@ echo "Fcleaning $(NAME) \
		\033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

re : fclean all

namemes :
	@ echo -n Compiling $(NAME)

.PHONY: clean fclean re
