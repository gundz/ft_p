/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:36:05 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:36:06 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsocket.h>

int						error_handling(int ret, int sockfd, int msg)
{
	if (sockfd != -1)
		send_int32(sockfd, msg);
	return (ret);
}
