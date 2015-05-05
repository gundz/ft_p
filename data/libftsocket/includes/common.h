#ifndef COMMON_H
# define COMMON_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>

typedef int SOCKET;
typedef int SOCKET_ERR;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define PORT 80
# define BUF_SIZE 32

#endif