all: libft server client

libft:
	@ make -C libft/

server:
	@ make -C data/server

client:
	@ make -C data/client

clean:
	@ make clean -C libft
	@ make clean -C data/client
	@ make clean -C data/server

fclean:
	@ make fclean -C libft
	@ make fclean -C data/client
	@ make fclean -C data/server

re: fclean all

.PHONY: clean fclean re libft server client
