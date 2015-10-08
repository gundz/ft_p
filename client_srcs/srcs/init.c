#include <stdio.h>

#include <client.h>
#include <libftsocket.h>

int					init_client(t_data *data)
{
	if (new_socket(&data->serv, AF_INET, inet_addr(data->addr), htons(data->portno)) == -1)
		return (-1);
	if (connect(data->serv.fd, (struct sockaddr *)&data->serv.addr, data->serv.socklen) < 0)
	{
		printf("Error: invalid host or port\n");
		return (-1);
	}
	init_commands(data->commands);
	return (0);
}