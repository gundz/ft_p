#include <sys/stat.h>
#include <stdio.h>

#include <libftsocket.h>

static int			get_file_core(int sockfd, int fd, void (*f)(off_t, off_t))
{
	struct stat		s;
	char			buf[BUFSIZ];
	off_t			i;
	off_t			j;

	recv(sockfd, &s, sizeof(struct stat), 0);
	i = 0;
	while (i < s.st_size)
	{
		j = recv(sockfd, &buf, BUFSIZ, 0);
		write(fd, buf, j);
		if (f)
			f(i, s.st_size);
		i += j;
	}
	if (f)
		f(i, s.st_size);
	return (0);
}

int					get_file(int sockfd, char *path, void (*f)(off_t, off_t))
{
	int				fd;

	if ((fd = open_file_write(path)) == -1)
		return (-1);
	get_file_core(sockfd, fd, f);
	close(fd);
	return (0);
}