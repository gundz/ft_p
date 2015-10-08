#include <libftsocket.h>

int						error_handling(int ret, int sockfd, int msg)
{
	if (sockfd != -1)
		send_int32(sockfd, msg);
	return (ret);
}