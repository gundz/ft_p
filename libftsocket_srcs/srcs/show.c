/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:37:49 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:37:50 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsocket.h>
#include <stdio.h>

static double			get_percent(const off_t i, const off_t size)
{
	return ((long double)i * 100 / size);
}

void					show_percent(const off_t i, const off_t size)
{
	static double		tmp = 0;
	double				percent;

	percent = get_percent(i, size);
	if (tmp != percent || tmp == 0)
	{
		printf("\t%lld/%lld | %2.f%%\r", (long long unsigned int)i, \
			(long long unsigned int)size, percent);
		fflush(stdout);
		tmp = percent;
	}
	if (percent == 100)
		printf("\n");
}
