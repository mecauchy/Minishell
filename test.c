#include "libft/includes/libft.h"
#include <bits/types/siginfo_t.h>
#include <signal.h>
#include <sys/wait.h>

int	signa;

void	handle_usr2(int sig, siginfo_t *info, void *p)
{
	kill(info->si_pid, SIGUSR1);
	sig = 0;
	p++;
}

void	handle_usr1(int sig, siginfo_t *info, void *p)
{
	while (signa != 2)
		sig = 0;
	kill(info->si_pid, SIGKILL);
	p ++;
}
void	handle_ctrc_c(int sig)
{
	signa = sig;
}

int	execlol(void)
{
	int pid = fork();
	if (pid < 0)
		return(-1);
	if (pid > 0)
	{
		kill(pid, SIGUSR2);
	}
	else
	{
		while(1)
			write(1, "1", 1);
		return (0);
	}
	waitpid(pid, 0, 0);
	return (0);
}


int	main(void)
{
	struct sigaction sa1;
	int	err;

	sa1.sa_sigaction = &handle_usr2;
	sigemptyset(&sa1.sa_mask);
	sa1.sa_flags = SA_SIGINFO;
	err = sigaction(SIGUSR2, &sa1, NULL);
	if (err < 0)
		return (err);
	struct sigaction sa2;
	int	err2;

	sa2.sa_sigaction = &handle_usr1;
	sigemptyset(&sa2.sa_mask);
	sa2.sa_flags = SA_SIGINFO;
	err2 = sigaction(SIGUSR1, &sa2, NULL);
	if (err2 < 0)
		return (err2);

	struct sigaction sa3;
	int	err3;

	sa3.sa_handler= &handle_ctrc_c;
	sigemptyset(&sa3.sa_mask);
	sa3.sa_flags = SA_SIGINFO;
	err3 = sigaction(SIGINT, &sa3, NULL);
	if (err3 < 0)
		return (err3);
	execlol();
	signa = 0;
	sleep(10);
	execlol();
}
