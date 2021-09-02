int ft_printf(const char *, ...);

#include <signal.h>
#include <unistd.h>
#include "../../libft/libft.h"

void signal_handler(int signal)
{
	static int	signals;

	if (signal == SIGUSR1)
		ft_printf("0");
	else if (signal == SIGUSR2)
		ft_printf("1");
	else
		ft_printf("I don't know this signal: %d\n", signal);
}

int main(void)
{
	pid_t				pid;
	struct sigaction 	sa;

	ft_bzero(&sa, sizeof(sa));
	pid = getpid();
	sa.sa_handler = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("[SERVER] > listening on pid %u\n", pid);
	while (1)
		pause();
}
