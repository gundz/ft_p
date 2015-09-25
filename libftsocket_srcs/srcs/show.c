#include <libftsocket.h>
#include <stdio.h>

double					get_percent(const long int i, const long int size)
{
	return((long double)i * 100 / size);
}

void					show_percent(const long int i, const long int size)
{
	static double		tmp = 0;
	double				percent;

	percent = get_percent(i, size);
	if (tmp != percent || tmp == 0)
	{
		printf("\t%ld/%ld | %2.f%%\r", i, size, percent);		
		fflush(stdout);
		tmp = percent;
	}
}