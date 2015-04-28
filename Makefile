all: server client

server:
	@ make -C makefiles/server

client:
	@ make -C makefiles/client

clean:
	@ make clean -C makefiles/server
	@ make clean -C makefiles/client

fclean:
	@ make fclean -C makefiles/server
	@ make fclean -C makefiles/client

re: fclean all

.PHONY: clean fclean re server client