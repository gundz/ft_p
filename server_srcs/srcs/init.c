#include <errno.h>
#include <stdio.h>

#include <limits.h>
#include <libftsocket.h>
#include <server.h>

int						init_server(t_data *data)
{
	static int			yes = 1;

	if (new_socket(&data->serv, AF_INET, INADDR_ANY, htons(data->portno)) == -1)
		return (-1);
	if(setsockopt(data->serv.fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
		return (-1);
	if (bind(data->serv.fd, (struct sockaddr *)&data->serv.addr, data->serv.socklen) == -1)
		perror("Error on binding");
	listen(data->serv.fd, 5);
	init_commands(data->commands);
	getcwd(data->root_path, PATH_MAX);
	return (0);	
}