/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:37:24 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:37:25 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H
# define MSG_H

typedef enum		e_msg
{
	MSG_CO_CONFIRM, MSG_CO_WAIT, MSG_CO_DISCO,
	MSG_COMMAND_ERROR,
	MSG_NO_SUCH_FILE,
	MSG_FILE_GET, MSG_FILE_GET_CONFIRM, MSG_FILE_GET_USAGE, MSG_FILE_GET_ERR,
	MSG_FILE_PUT, MSG_FILE_PUT_CONFIRM, MSG_FILE_PUT_USAGE, MSG_FILE_PUT_ERR,
	MSG_LS, MSG_LS_ERR,
	MSG_PWD, MSG_PWD_ERR,
	MSG_CD, MSG_CD_OK, MSG_CD_ACCESS_DENIED, MSG_CD_USAGE
}					t_msg;

#endif
