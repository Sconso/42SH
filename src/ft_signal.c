/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 17:05:43 by sconso            #+#    #+#             */
/*   Updated: 2014/03/26 18:18:46 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_print.h>
#include <signal.h>

void	handle_signal(int signo)
{
	if (signo >= 0)
	{
		ft_putstr("\r\n");
		ft_putstr(INVIT);
	}
}

void	ft_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGSEGV, handle_signal);
	signal(SIGFPE, handle_signal);
	signal(SIGBUS, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGHUP, handle_signal);
	signal(SIGILL, handle_signal);
	signal(SIGABRT, handle_signal);
	signal(SIGSYS, handle_signal);
	signal(SIGALRM, handle_signal);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	signal(SIGINFO, handle_signal);
	signal(SIGTSTP, handle_signal);
}
