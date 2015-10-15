/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:33:15 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:33:17 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <libftsocket.h>
# define NB_COMMANDS 8

typedef struct	s_command
{
	char		*command;
	int			(*f)();
}				t_command;

typedef struct	s_data
{
	t_socket	serv;
	char		*addr;
	int			portno;
	t_command	commands[NB_COMMANDS];
}				t_data;

int				init_client(t_data *data);

void			init_commands(t_command *commands);
int				command_get_function_id(t_command *commands, char *cinput, \
	const int nb_commands);

int				command_put_file(int sockfd, char *command);
int				command_get_file(int sockfd, char *command);
int				command_ls(int sockfd, char *command);
int				command_pwd(int sockfd, char *command);
int				command_cd(int sockfd, char *command);
int				command_lls(int sockfd, char *command);
int				command_lpwd(int socfd, char *command);
int				command_lcd(int sockfd, char *command);

int				error_handling(int ret, int msg, char *more);

#endif
