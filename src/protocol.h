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

typedef struct s_message	t_message;
typedef enum e_stages		t_stages;

enum e_stages {
	SENDING_CLIENT_PID,
	SENDING_MESSAGE_LENGTH,
	SENDING_MESSAGE_BODY,
};

struct s_message {
	unsigned int	client_pid;
	unsigned int	length;
	char			*text;
	t_stages		current_stage;
};

#endif
