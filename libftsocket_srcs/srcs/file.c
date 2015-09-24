#include <libft.h>
#include <libftsocket.h>

#include <errno.h>
#include <stdio.h>

#include <sys/stat.h>

int						get_file_stats(const int fd, struct stat *buf)
{
	if ((fstat(fd, buf)) == -1)
	{
		perror("Error getting file stat");
		return (-1);
	}
	return (0);
}

int						send_file(const int sockfd, char *path)
{
	int					fd;
	struct stat			buf_stat;
	char				buf[DATA_BUF_SIZE];
	int					n;

	if ((fd = open_file_read(path)) == -1)
		return (-1);
	if (send_char_string(sockfd, path) == -1)
		return (-1);
	if (get_file_stats(fd, &buf_stat) == -1)
		return (-1);
	if (send_data(sockfd, &buf_stat, sizeof(buf)))
		return (-1);
	while ((n = read(fd, &buf, DATA_BUF_SIZE)) > 0)
		send_data(sockfd, &buf, n);
	close(fd);
	return (0);
}



int						write_file(const int fd, const int sockfd, void (*f)(long int, long int))
{
	struct stat			*buf_stat;
	void				*data;
	long int			i;
	long int			j;

	if (get_data(sockfd, (void **)&buf_stat) == -1)
		return (-1);
	i = 0;
	while (i < buf_stat->st_size)
	{
		j = get_data(sockfd, &data);
		write(fd, data, sizeof(char) * j);
		free(data);
		i += j;
		f(i, buf_stat->st_size);
	}
	f(i, buf_stat->st_size);
	printf("\n");
	free(buf_stat);
	return (0);
}

int						get_file(const int sockfd, void (*f)(long int, long int))
{
	int					fd;
	char				*path;

	if ((path = ft_basename(get_char_string(sockfd))) == NULL)
		return (-1);
	printf("\tfile: %s\n", path);
	if ((fd = open_file_write(path)) == -1)
		return (-1);
	write_file(fd, sockfd, f);
	close(fd);
	return (0);
}