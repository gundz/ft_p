#ifndef LIBFTSOCKET_H
# define LIBFTSOCKET_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>

# include <unistd.h>
# include <stdlib.h>

typedef int SOCKET;
typedef int SOCKET_ERR;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

# define PORT 80

#include <errno.h>
#include <stdio.h>

SOCKET			open_socket(void);

#endif