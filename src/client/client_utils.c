/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 21:34:50 by psergio-          #+#    #+#             */
/*   Updated: 2021/09/02 21:34:50 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../../libft/libft.h"
#include "../protocol.h"

int	ft_printf(const char *format, ...);

extern t_connection	*g_connection;

void	send_length_next_bit(void)
{
	static int	current_bit = 31;
	int			signal;
	int			signals[2];

	signals[0] = SIGUSR1;
	signals[1] = SIGUSR2;
	if (current_bit == 0)
	{
		g_connection->current_stage = SENDING_MESSAGE_BODY;
	}
	signal = (g_connection->length >> current_bit--) & 1;
	ft_printf("%d", signal);
	kill(g_connection->server_pid, signals[signal]);
}

void	send_body_next_bit(void)
{
	static int			current_bit = 7;
	static unsigned int	current_byte = 0;
	int					signal;
	int					signals[2];

	if (current_byte >= g_connection->length)
	{
		ft_printf("the last byte was already sent");
		return ;
	}
	signals[0] = SIGUSR1;
	signals[1] = SIGUSR2;
	if (current_bit < 0)
	{
		current_bit = 7;
		current_byte++;
	}
	if (current_byte >= g_connection->length)
	{
		ft_printf("the last byte was already sent");
		g_connection->current_stage = CLEANING_CONNECTION;
	}
	signal = (g_connection->text[current_byte] >> current_bit--) & 1;
	kill(g_connection->server_pid, signals[signal]);
}

void	handle_response(int signal)
{
	g_connection->is_connected = 1;
	if (g_connection->current_stage == SENDING_MESSAGE_LENGTH)
		send_length_next_bit();
	else if (g_connection->current_stage == SENDING_MESSAGE_BODY)
		send_body_next_bit();
	else
	{
		ft_printf("received a confirmation, but there's nothing else");
		g_connection->is_connected = 0;
		return ;
	}
	(void)signal;
}

void	register_listener(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_response;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}
