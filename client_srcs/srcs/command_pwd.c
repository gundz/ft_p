#include <stdio.h>
#include <libft.h>
#include <libftsocket.h>

int						command_pwd(int sockfd)
{
	int					n;
	char				buf[BUFSIZ + 1];
	char				*tmp;

	send_int32(sockfd, MSG_PWD);
	while ((n = recv(sockfd, &buf, BUFSIZ, 0)) > 0)
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
	return (0);
}