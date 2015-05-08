DATA_PATH =	data/

all: libft libftsocket server client

libft:
	@ make -sC $(DATA_PATH)libft/

libftsocket:
	@ make -sC $(DATA_PATH)libftsocket

server:
	@ make -sC $(DATA_PATH)/server

client:
	@ make -sC $(DATA_PATH)/client

clean:
	@ make clean -sC libft
	@ make clean -sC $(DATA_PATH)libftsocket
	@ make clean -sC $(DATA_PATH)client
	@ make clean -sC $(DATA_PATH)server

fclean:
	@ make fclean -sC $(DATA_PATH)libft
	@ make fclean -sC $(DATA_PATH)libftsocket
	@ make fclean -sC $(DATA_PATH)client
	@ make fclean -sC $(DATA_PATH)server

re: fclean all

.PHONY: clean fclean re libft server client
