#include <stdio.h>
#include <libft.h>
#include <libftsocket.h>

int						command_get_file(int sockfd, char *command)
{
	char				*path;
	char				*filename;

	if ((path = get_char_string(sockfd)) == NULL)
		return (-1);
	filename = ft_basename(path);
	if (get_file(sockfd, filename, &show_percent) == -1)
	{
		perror("Error get_file");
		return (-1);
	}
	return (0);
	(void)command;
}

int						command_put_file(int sockfd, char *command)
{
	int					fd;
	char				*path;
	char				**tmp;
	int					ret;

	tmp = ft_strsplit(command, ' ');
	if (ft_ctablen(tmp) != 2)
	{
		ft_freectab(tmp);
		return (-1);
	}
	path = tmp[1];
	if ((fd = open_file_read(path)) == -1)
	{
		ft_freectab(tmp);
		return (-1);
	}
	send_char_string(sockfd, path);
	ret = send_file(sockfd, path, &show_percent);
	ft_freectab(tmp);
	if (ret == -1)
		perror("Error: send_file");
	return (ret);
}

int						command_ls(const int sockfd, char *command)
{
	int					n;
	char				buf[DATA_BUF_SIZE + 1];
	char				*tmp;

	while ((n = recv(sockfd, &buf, DATA_BUF_SIZE, 0)) > 0)
	{
		buf[n] = '\0';
		if ((tmp = ft_strchr(buf, EOF)) != NULL)
		{
			*tmp = '\0';
			printf("%s", buf);
			break ;
		}
		else
			printf("%s", buf);

	}
	(void)command;
	return (0);
}