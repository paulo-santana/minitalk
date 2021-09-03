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

#include <signal.h>
#include <unistd.h>
#include "../protocol.h"
#include "../../libft/libft.h"
#include "client.h"

int	ft_printf(const char *format, ...);

int	parse_server_pid(const char *str)
{
	int	pid;

	pid = ft_atoi(str);
	if (pid < 0)
	{
		ft_printf("Error: invalid server pid: %d\n", pid);
		return (1);
	}
	return (pid);
}

static t_message	*make_message(char *text)
{
	t_message	*message;

	message = ft_calloc(1, sizeof(t_message));
	if (message == NULL)
	{
		ft_putstr_fd("Failed to allocate memory for a message\n", 1);
	}
	message->client_pid = getpid();
	message->text = text;
	message->length = ft_strlen(text);
	return (message);
}

static int	send_message(t_message *message)
{
	register_listener();
	return (1);
}

int	main(int argc, char *argv[])
{
	int					i;
	int					server_pid;
	t_message			*message;
	unsigned int		msg_len;

	if (argc != 3)
	{
		ft_printf("Usage: %s PID MESSAGE\n\n", argv[0]);
		ft_printf("Where\n" "PID is the process ID of the server, and\n"
			"MESSAGE is a quoted string that will be sent to the server\n");
		return (1);
	}
	server_pid = parse_server_pid(argv[1]);
	message = make_message(argv[2]);
	if (!send_message(message))
	{
		ft_printf("Failed to send the message\n");
		free(message);
		return (1);
	}
	ft_printf("Message sent successfully!\n");
	free(message);
	return (0);
}
