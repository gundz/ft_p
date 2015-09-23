#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <stdio.h>

#include <libft.h>
#include <libftsocket.h>

int						get_file_stats(const int fd, struct stat *buf)
{
	if ((fstat(fd, buf)) == -1)
	{
		perror("Error getting file stat");
		return (-1);
	}
	return (0);
}

int						open_file_read(char *path)
{
	int					fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		perror("Error while opening file");
		return (-1);
	}
	return (fd);
}

int						open_file_write(char *path)
{
	int					fd;

	if ((fd = open(path, O_WRONLY | O_CREAT, 0644)) == -1)
	{
		perror("Error while opening file");
		return (-1);
	}
	return (fd);
}

int						send_file(const int sockfd, char *path)
{
	int					fd;
	struct stat			buf_stat;
	char				buf[DATA_BUF_SIZE];
	int					n;

	if ((fd = open_file_read(path)) == -1)
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

void					show_percent(const int i, const int size)
{
	static int			tmp = 0;
	int					percent;

	percent = (int)((double)i * 100 / size);
	if (tmp != percent)
	{
		printf("%d/%d | %d%%\n", i, size, percent);
		tmp = percent;
	}
}

int						write_file(const int fd, const int sockfd)
{
	struct stat			*buf_stat;
	void				*data;
	int					i;
	int					j;

	if (get_data(sockfd, (void **)&buf_stat) == -1)
		return (-1);
	i = 0;
	while (i < buf_stat->st_size)
	{
		j = get_data(sockfd, &data);
		write(fd, data, sizeof(char) * j);
		free(data);
		i += j;
		show_percent(i, buf_stat->st_size);
	}
	free(buf_stat);
	return (0);
}

int						get_file(const int sockfd)
{
	int					fd;

	fd = open_file_write("/mnt/FCB83109B830C3C4/tmp/copy");
	write_file(fd, sockfd);
	close(fd);
	return (0);
}