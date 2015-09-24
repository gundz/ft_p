#include <errno.h>
#include <stdio.h>

#include <libft.h>
#include <libftsocket.h>
#include <client.h>

void					client_commands(t_socket *serv)
{
	char				*command;
	int					msg;

	while (1)
	{
		ft_putstr(inet_ntoa(serv->addr.sin_addr));
		ft_putstr(" $>: ");
		get_next_line(0, &command);
		send_char_string(serv->fd, command);
		msg = get_int32(serv->fd);
		if (msg == MSG_CO_DISCO)
			break ;
		else
			show_msg(msg, NULL);
	}
}

int						main_client(char *addr, const int portno)
{
	t_socket			serv;
	int					msg;

	if (init_client(addr, portno, &serv) == -1)
		return (EXIT_FAILURE);

	show_msg(MSG_CO_WAIT, inet_ntoa(serv.addr.sin_addr));
	msg = get_int32(serv.fd);
	show_msg(msg, inet_ntoa(serv.addr.sin_addr));
	client_commands(&serv);
	close(serv.fd);
	show_msg(MSG_CO_DISCO, inet_ntoa(serv.addr.sin_addr));
	return (EXIT_SUCCESS);
}

int						main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: ./client addr port\n");
		return (EXIT_FAILURE);
	}
	return (main_client(argv[1], ft_atoi(argv[2])));
}
