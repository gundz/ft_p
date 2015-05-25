#include <libftsocket.h>
#include <libft.h>
#include <server.h>

void
talk(t_socket *csock, int *run, int *connected)
{
	char	*msg;

	if ((msg = rec_msg(csock->sock)) != NULL)
	{
		printf("receive command : \"%s\"\n", msg);

		if (check_get_file(msg) == 1)
			send_file(csock, msg + 4);

		if (ft_strcmp("ls", msg) == 0)
		{
			send_ls(csock, "./");
		}

		if (ft_strcmp("exit", msg) == 0)
		{
			*connected = 0;
			free(msg);
			return ;
		}
		if (ft_strcmp("shutdown", msg) == 0)
		{
			free(msg);
			*connected = 0;
			*run = 0;
			return ;
		}

		// if (check_command(msg) == 0)
		// {
		// 	send_msg(csock, "200- OK");
		// }
		free(msg);
	}
}

int
main(void)
{
	t_socket		*ssock;
	t_socket		*csock;
	int				run;
	int				connected;

	ssock = new_server_socket();
	if (ssock == NULL)
		return (-1);

	if (bind_and_listen(ssock) == -1)
	{
		close(ssock->sock);
		return (-1);
	}

	run = 1;
	while (run == 1)
	{
		connected = 1;
		csock = wait_for_client(ssock);
		while (connected == 1)
		{
			talk(csock, &run, &connected);
		}
		close_socket(csock);
		printf("client socket closed\n\n");
	}

	close_socket(ssock);
	printf("server closed\n");
	return (0);
}