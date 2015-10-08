#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <libftsocket.h>

int					safe_send(int sockfd, void *data, int size)
{
	int				i;
	int				j;

	i = 0;
	while (i < size)
	{
		j = send(sockfd, data + i, size, 0);
		if (j < 0)
		{
			perror("send_error");
			return (-1);
		}
		i += j;
	}
	return (i);
}

int					send_file(int sockfd, int fd, void (*f)(off_t, off_t))
{
	struct stat		s;
	void			*addr;
	off_t			i;
	off_t			j;

	if (fstat(fd, &s) == -1)
		return (-1);
	safe_send(sockfd, &s, sizeof(struct stat));
	addr = mmap(NULL, s.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
		return (-1);
	i = 0;
	while (i < s.st_size)
	{
		j = BUFSIZ;
		if (i + j > s.st_size)
			j = s.st_size - i;
		safe_send(sockfd, addr + i, j);
		if (f)
			f(i, s.st_size);
		i += j;
	}
	if (f)
		f(i, s.st_size);
	return (0);
}

