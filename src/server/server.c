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

t_message	*g_message;

static void	handle_for_current_stage(t_message *message, int signal)
{
	if (message->current_stage == SENDING_MESSAGE_LENGTH)
		get_message_len(message, signal);
	else
		ft_printf("getting the message\n");
}

void	signal_handler(int signal, siginfo_t *info, void *param)
{
	static t_message	message;
	static int			is_connected;

	if (!is_connected)
	{
		ft_printf("client pid: %d\n", info->si_pid);
		message.client_pid = info->si_pid;
		handle_for_current_stage(&message, signal);
		is_connected = 1;
	}
	else
	{
		if (message.client_pid == info->si_pid)
		{
			handle_for_current_stage(&message, signal);
		}
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	g_message = ft_calloc(sizeof(t_message), 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_printf("[SERVER] > listening on pid %u\n", pid);
	while (1)
	{
		pause();
		if (g_message->client_pid)
			return (0);
	}
}
