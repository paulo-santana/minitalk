/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_pid_listener.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 20:39:43 by psergio-          #+#    #+#             */
/*   Updated: 2021/09/06 20:39:43 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "server.h"
#include "../protocol.h"

int	ft_printf(const char *format, ...);

void	get_message_body(t_connection *connection, int signal)
{
	static unsigned int	current_bit;
	static unsigned int	current_byte;

	connection->text[current_byte] <<= 1;
	if (signal == SIGUSR2)
		connection->text[current_byte]++;
	current_bit++;
	if (current_bit >= 8)
	{
		current_bit = 0;
		current_byte++;
		if (current_byte == connection->length)
		{
			ft_printf("[SERVER] > message: %.*s\n",
				connection->length, connection->text);
			connection->current_stage = CLEANING_CONNECTION;
			current_byte = 0;
		}
	}
}

void	get_message_len(t_connection *connection, int signal)
{
	if (connection->current_stage != SENDING_MESSAGE_LENGTH)
	{
		ft_printf("the message length was already fetched\n");
		return ;
	}
	if (connection->client_pid_bit > 32)
	{
		ft_printf("current bit is bigger than 31\n");
		return ;
	}
	connection->length <<= 1 ;
	if (signal == SIGUSR2)
		connection->length++;
	connection->client_pid_bit++;
	if (connection->client_pid_bit > 32 && connection->text == NULL)
	{
		if (connection->length == 0)
		{
			connection->current_stage = CLEANING_CONNECTION;
			return ;
		}
		connection->text = ft_calloc(connection->length + 1, 1);
		connection->current_stage = SENDING_MESSAGE_BODY;
	}
}
