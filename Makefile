all: libft server client

libft:
	@ make -C libft/

server:
	@ make -C makefiles/server

client:
	@ make -C makefiles/client

clean:
	@ make clean -C libft
	@ make clean -C makefiles/client
	@ make clean -C makefiles/server

fclean:
	@ make fclean -C libft
	@ make fclean -C makefiles/client
	@ make clean -C makefiles/server

re: fclean all

.PHONY: clean fclean re libft server client