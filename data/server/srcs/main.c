#include <libftsocket.h>
#include <libft.h>
#include <server.h>

int
main(void)
{
	t_socket		*ssock;
	t_socket		*csock;
	int				run;

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
		csock = wait_for_client(ssock);
		while (1)
		{
			char	*msg;

			if ((msg = rec_msg(csock->sock)) != NULL)
			{
				ft_putstr("receive command : \"");
				ft_putstr(msg);
				ft_putstr("\"\n");
				/*		commands		*/
				if (ft_strcmp("exit", msg) == 0)
				{
					free(msg);
					break ;
				}
				if (ft_strcmp("shutdown", msg) == 0)
				{
					free(msg);
					run = 0;
					break ;
				}
				free(msg);
			}
		}
		close_socket(csock);
		printf("client socket closed\n\n");
	}

	close_socket(ssock);
	printf("server closed\n");
	return (0);
}