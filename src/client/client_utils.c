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
	if (current_bit < 0)
	{
		ft_printf("the current bit is lesser than 0");
		g_connection->current_stage = SENDING_MESSAGE_BODY;
		return ;
	}
	signal = (g_connection->client_pid >> current_bit--) & 1;
	ft_printf("%d", signal);
	kill(g_connection->server_pid, signals[signal]);
}

void	handle_response(int signal)
{
	send_length_next_bit();
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
