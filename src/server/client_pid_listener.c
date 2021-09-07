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

void	get_message_len(t_message *message, int signal)
{
	static int	current_bit;

	ft_printf("getting message length: %d\n", message->client_pid);
	if (message->current_stage != SENDING_MESSAGE_LENGTH)
	{
		ft_printf("the message length was already fetched\n");
		return ;
	}
	if (current_bit >= 32)
	{
		ft_printf("current bit is bigger than 31\n");
		return ;
	}
	message->client_pid <<= 1 ;
	if (signal == SIGUSR2)
		message->client_pid++;
	current_bit++;
	kill(message->client_pid, SIGUSR1);
}
