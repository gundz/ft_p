NAME = ../../server

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

LIBFT_PATH = ../../libft/
LIBFT_INC = -I $(LIBFT_PATH)includes
LIBFT_NAME = $(LIBFT_PATH)libft.a

LIBSOCKET_PATH = ../libftsocket/
LIBSOCKET_INC = -I $(LIBSOCKET_PATH)includes
LIBSOCKET_NAME = $(LIBSOCKET_PATH)libftsocket.a

PATH_INC = -I includes/
PATH_OBJ = obj
PATH_SRC = srcs

SRC =	main.c

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all: $(NAME)

$(NAME): namemes $(OBJ)
	@ $(CC) $(OBJ) $(CFLAGS) $(LFLAGS) $(PATH_INC) $(LIBFT_INC) $(LIBFT_NAME) $(LIBSOCKET_INC) $(LIBSOCKET_NAME) -o $(NAME)
	@ echo " \033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/, %.c)
	@ echo -n .
	@ mkdir -p $(PATH_OBJ)
	@ $(CC) -c $^ $(PATH_INC) $(LIBFT_INC) $(LIBSOCKET_INC) $(CFLAGS) $(LFGLAGS) -o $@

clean:
	@ rm -rf $(PATH_OBJ)
	@ echo "Cleaning $(NAME) \
		\033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

fclean: clean
	@ rm -rf $(NAME)
	@ echo "Fcleaning $(NAME) \
		\033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

namemes :
	@ echo -n Compiling $(NAME)

re: fclean all

.PHONY: clean fclean re
