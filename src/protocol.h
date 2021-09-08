/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:26:14 by psergio-          #+#    #+#             */
/*   Updated: 2021/09/02 20:26:14 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This file specify the common structures that can be used by both the server
 * and the client
 * */

#ifndef PROTOCOL_H
# define PROTOCOL_H

# include <signal.h>

typedef struct s_message	t_connection;
typedef enum e_stages		t_stages;

enum e_stages {
	SENDING_MESSAGE_LENGTH = 0,
	SENDING_MESSAGE_BODY,
	CLEANING_CONNECTION,
};

struct s_message {
	pid_t			client_pid;
	int				client_pid_bit;
	pid_t			server_pid;
	unsigned int	length;
	char			*text;
	t_stages		current_stage;
	int				is_connected;
};

#endif
