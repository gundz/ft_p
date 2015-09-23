#include <libftsocket.h>
#include <stdio.h>

void					show_percent(const long int i, const long int size)
{
	static int			tmp = 0;
	int					percent;

	percent = (int)((long double)i * 100 / size);
	if (tmp != percent)
	{
		printf("%ld/%ld | %d%%\n", i, size, percent);
		tmp = percent;
	}
}