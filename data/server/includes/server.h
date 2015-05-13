#ifndef SERVER_H
# define SERVER_H

t_socket	*new_server_socket(void);

int			bind_and_listen(t_socket *ssock);

t_socket	*wait_for_client(t_socket *ssock);


#endif