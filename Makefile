LIBFT_SRCS = ./libft_srcs/
LIBFTSOCKET_SRCS = ./libftsocket_srcs/
SERVER_SRCS = ./server_srcs/
CLIENT_SRCS = ./client_srcs/

all: re libft libftsocket server client

libft:
	@ make -sC $(LIBFT_SRCS)

libftsocket:
	@ make -sC $(LIBFTSOCKET_SRCS)

server:
	@ make -sC $(SERVER_SRCS)

client:
	@ make -sC $(CLIENT_SRCS)

clean:
	@ make clean -sC $(LIBFT_SRCS)
	@ make clean -sC $(LIBFTSOCKET_SRCS)
	@ make clean -sC $(SERVER_SRCS)
	@ make clean -sC $(CLIENT_SRCS)

fclean:
	@ make fclean -sC $(LIBFT_SRCS)
	@ make fclean -sC $(LIBFTSOCKET_SRCS)
	@ make fclean -sC $(SERVER_SRCS)
	@ make fclean -sC $(CLIENT_SRCS)

re: fclean all

.PHONY: libft libftsocket server client
