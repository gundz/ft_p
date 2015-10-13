/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/13 11:55:08 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/13 11:55:09 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsocket.h>
#include <server.h>
#include <libft.h>

int						command_cd(int sockfd, t_data *data)
{
	char				old_path[PATH_MAX];
	char				*tmp;
	char				*new_path;
	int					ret;

	tmp = get_char_string(sockfd);
	getcwd(old_path, PATH_MAX);
	new_path = ft_strijoin(3, old_path, "/", tmp);
	free(tmp);
	if (chdir(new_path) == -1)
	{
		free(new_path);
		return (error_handling(-1, sockfd, MSG_NO_SUCH_FILE));
	}
	tmp = getcwd(NULL, PATH_MAX);
	if (ft_strncmp(data->root_path, tmp, ft_strlen(data->root_path)) != 0)
	{
		chdir(old_path);
		ret = error_handling(-1, sockfd, MSG_CD_ACCESS_DENIED);
	}
	else
		ret = error_handling(0, sockfd, MSG_CD_OK);
	free(tmp);
	free(new_path);
	return (ret);
}
