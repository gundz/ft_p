#include <libftsocket.h>
#include <sys/wait.h>
#include <stdio.h>

int						command_ls(const int sockfd)
{
	pid_t				pid;
	const int			eof = EOF;

	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		send(sockfd, &eof, sizeof(eof), 0);
	}
	else
	{
		dup2(sockfd, STDOUT_FILENO);
		if (execl("/bin/ls", "ls", "-la", NULL) == -1)
		{
			printf("Error: ls\n");
			send(sockfd, &eof, sizeof(eof), 0);
		}
	}
	return (0);
}