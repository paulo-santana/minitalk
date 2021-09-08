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

int	ft_printf(const char *format, ...);

void	clear_connection(t_connection *connection)
{
	ft_printf("cleaning connection\n");
	connection->client_pid = 0;
	free(connection->text);
	connection->current_stage = SENDING_MESSAGE_LENGTH;
	connection->length = 0;
	connection->is_connected = 0;
}

static void	handle_for_current_stage(t_connection *connection, int signal)
{
	if (connection->current_stage == SENDING_MESSAGE_LENGTH)
		get_message_len(connection, signal);
	else if (connection->current_stage == CLEANING_CONNECTION)
		clear_connection(connection);
	else
	{
		ft_printf("unknown stage\n");
		return ;
	}
	kill(connection->client_pid, SIGUSR1);
}

void	signal_handler(int signal, siginfo_t *info, void *param)
{
	static t_connection	connection;
	static int			is_connected;

	(void)param;
	if (!connection.is_connected)
	{
		ft_printf("client pid: %d\n", info->si_pid);
		connection.client_pid = info->si_pid;
		handle_for_current_stage(&connection, signal);
		is_connected = 1;
	}
	else
	{
		if (connection.client_pid == info->si_pid)
			handle_for_current_stage(&connection, signal);
		else
			ft_printf("message from a different client\n");
	}
	usleep(1000);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
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
