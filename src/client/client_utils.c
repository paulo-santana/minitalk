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

int	ft_printf(const char *format, ...);

void	handle_response(int signal)
{
	ft_printf("the server just responded :flushed:\n");
}

void	register_listener(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_response;
	sigaction(SIGUSR1, &sa, NULL);
}
