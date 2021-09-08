/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:58:33 by psergio-          #+#    #+#             */
/*   Updated: 2021/09/02 17:58:33 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "../../libft/libft.h"
#include "../protocol.h"
#include <signal.h>
#include <unistd.h>

int	ft_printf(const char *format, ...);

t_connection	*g_connection;

int	parse_server_pid(const char *str)
{
	int	pid;

	pid = ft_atoi(str);
	if (pid <= 0)
	{
		ft_printf("Error: invalid server pid: %d\n", pid);
		return (1);
	}
	return (pid);
}

static t_connection	*make_message(int server_pid, char *text)
{
	t_connection	*message;

	message = ft_calloc(1, sizeof(t_connection));
	if (message == NULL)
	{
		ft_putstr_fd("Failed to allocate memory for a message\n", 1);
	}
	message->client_pid = getpid();
	message->text = text;
	message->length = ft_strlen(text);
	message->server_pid = server_pid;
	return (message);
}

static void	connect(int server_pid)
{
	register_listener();
	kill(server_pid, SIGUSR1);
}

int	main(int argc, char *argv[])
{
	int	server_pid;

	if (argc != 3)
	{
		ft_printf("Usage: %s PID MESSAGE\n\n", argv[0]);
		ft_printf("Where\n" "PID is the process ID of the server, and\n"
			"MESSAGE is a quoted string that will be sent to the server\n");
		return (1);
	}
	server_pid = parse_server_pid(argv[1]);
	g_connection = make_message(server_pid, argv[2]);
	connect(server_pid);
	while (1)
	{
		pause();
		if (!g_connection->is_connected)
			break ;
	}
	ft_printf("Message sent successfully!\n");
	free(g_connection);
	return (0);
}
