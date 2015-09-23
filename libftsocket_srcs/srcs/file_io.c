#include <libftsocket.h>
#include <fcntl.h>

#include <errno.h>
#include <stdio.h>

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