/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:11:45 by psergio-          #+#    #+#             */
/*   Updated: 2021/09/06 13:11:45 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/types/siginfo_t.h>
#include <signal.h>
#include <unistd.h>
#include "../protocol.h"
#include "../../libft/libft.h"
#include "server.h"
#include <errno.h>
#include <string.h>

int		ft_printf(const char *format, ...);

#define SIG_CLEAR 0

void	clear_connection(t_connection *connection)
{
	free(connection->text);
	ft_bzero(connection, sizeof(t_connection));
}

static void	handle_for_current_stage(t_connection *connection, int signal)
{
	pid_t	client_pid;

	if (connection->current_stage == SENDING_MESSAGE_LENGTH)
		get_message_len(connection, signal);
	else if (connection->current_stage == SENDING_MESSAGE_BODY)
		get_message_body(connection, signal);
	if (connection->current_stage == CLEANING_CONNECTION)
	{
		client_pid = connection->client_pid;
		clear_connection(connection);
		if (kill(client_pid, SIGUSR1))
			ft_printf("error sending last bit\n");
		return ;
	}
	kill(connection->client_pid, SIGUSR1);
}

void	signal_handler(int signal, siginfo_t *info, void *param)
{
	static t_connection	connection;

	if (!connection.is_connected)
	{
		connection.client_pid = info->si_pid;
		connection.is_connected = 1;
		handle_for_current_stage(&connection, signal);
	}
	else
	{
		if (connection.client_pid == info->si_pid)
			handle_for_current_stage(&connection, signal);
		else
		{
			ft_printf("[SERVER] > message from a different client\n");
			clear_connection(&connection);
		}
	}
	(void)param;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_printf("[SERVER] > listening on pid %u\n", pid);
	while (1)
	{
		pause();
	}
}
