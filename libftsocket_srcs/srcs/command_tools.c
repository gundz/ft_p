/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:37:43 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:37:43 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char					*check_command_usage(char *command, unsigned int nb_arg)
{
	char				**tmp;
	unsigned int		len;

	tmp = ft_strsplit(command, ' ');
	if (ft_ctablen(tmp) != (nb_arg + 1))
	{
		ft_freectab(tmp);
		return (NULL);
	}
	len = ft_strlen(tmp[0]) + 1;
	ft_freectab(tmp);
	return (command + len);
}
