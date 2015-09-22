all: clean
	gcc -Wall -Werror -Wextra -I ./ server.c -o server
	gcc -Wall -Werror -Wextra -I ./ client.c -o client

clean:
	rm -rf *.o

fclean: clean
	rm -rf server client

re: fclean all

.PHONY: all re clean fclean