#include <libftsocket.h>
#include <stdio.h>

static double			get_percent(const off_t i, const off_t size)
{
	return((long double)i * 100 / size);
}

void					show_percent(const off_t i, const off_t size)
{
	static double		tmp = 0;
	double				percent;

	percent = get_percent(i, size);
	if (tmp != percent || tmp == 0)
	{
		printf("\t%lld/%lld | %2.f%%\r", i, size, percent);		
		fflush(stdout);
		tmp = percent;
	}
	if (percent == 100)
		printf("\n");
}