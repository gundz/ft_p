#include <libftsocket.h>

int					error_handling(int ret, int msg, char *more)
{
	show_msg(msg, more);
	return (ret);
}