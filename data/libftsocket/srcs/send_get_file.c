#include <libftsocket.h>
#include <libft.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>

int
check_get_file(char *msg)
{
	char			**tab;
	unsigned int	tab_len;

	tab = ft_strsplit(msg, ' ');
	tab_len = ft_ctablen(tab);
	if (tab_len < 2)
	{
		//send error;
		return (-1);
	}
	if (ft_strcmp("get", tab[0]) == 0)
	{
		//send success
		return (1);
	}
	ft_freectab(tab);
	return (0);
}

void
get_file_data(const int fd, char *filename, t_file_data *file_data)
{
	struct stat		buf;
	int				i;

	fstat(fd, &buf);
	//check fstat output
	i = 0;
	while (filename[i] != '\0')
	{
		file_data->filename[i] = filename[i];
		i++;
	}
	file_data->filename[i] = '\0';
	file_data->filesize = (int)buf.st_size;
	file_data->block_size = BUF_SIZE;
	if (buf.st_size < BUF_SIZE)
		file_data->nb_block = 1;
	else
		file_data->nb_block = (int)ceil(buf.st_size / BUF_SIZE);
}

void
send_file(t_socket *sock, char *path)
{
	int				fd;
	t_file_data		file_data;
	int				n;
	char			buf[BUF_SIZE + 1];

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		perror("");
		return ;
	}
	get_file_data(fd, path, &file_data);
	send_struct(sock, &file_data, sizeof(t_file_data));
	printf("sending file : %s\n", path);
	printf("size = %d | block_size = %d | nb_block = %d\n", file_data.filesize, file_data.block_size, file_data.nb_block);
	while ((n = read(fd, &buf, BUF_SIZE)) != 0)
		send_data(sock, buf, n);
	printf("file sending ended !\n");
	close(fd);
}


int
save_file(t_socket *sock, t_file_data *file_data, int fd)
{
	char			*buf;
	double			size;
	unsigned int	final_size;
	int				tmp;
	int				percent;

	if (!(buf = (char *)malloc(sizeof(char) * (BUF_SIZE + 1))))
		return (-1);
	tmp = 0;
	final_size = 0;
	while (final_size != file_data->filesize)
	{
		size = rec_data(sock, buf);
		final_size += size;
		percent = (int)((double)final_size * 100 / file_data->filesize);
		if (percent != tmp)
		{
			tmp = percent;
			printf("%d%%\n", percent);
		}
		write(fd, buf, size);
	}
	free(buf);
	return (0);
}

void
rec_file(t_socket *sock)
{
	t_file_data		file_data;
	int				fd;

	recv(sock->sock, &file_data, sizeof(t_file_data), 0);
	fd = open(file_data.filename, O_WRONLY | O_CREAT);
	if (fd != -1)
	{
		save_file(sock, &file_data, fd);
		printf("saving \"%s\"\n", file_data.filename);
	}
	else
		perror("");
	close(fd);
}