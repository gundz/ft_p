#include <libftsocket.h>

int					send_uint32(const int fd, const uint32_t var)
{
	if (send(fd, &var, sizeof(uint32_t), 0) == -1)
	{
		perror("Error sending uint32_t");
		return (-1);
	}
	return  (0);
}

int					get_uint32(const int fd)
{
	uint32_t		var;

	recv(fd, &var, sizeof(uint32_t), 0);
	return (var);
}