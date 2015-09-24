#include <libftsocket.h>
#include <stdio.h>

int						get_percent(const long int i, const long int size)
{
	return((long double)i * 100 / size);
}

void					show_percent(const long int i, const long int size)
{
	static int			tmp = 0;
	int					percent;

	percent = get_percent(i, size);
	if (tmp != percent || tmp == 0)
	{
		printf("\t%ld/%ld | %d%%\r", i, size, percent);		
		fflush(stdout);
		tmp = percent;
	}
}