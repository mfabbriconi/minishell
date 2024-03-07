/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:41:24 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:41:25 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_prompt(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(0);
	}
}

static void	sig_silent(int sig)
{
	g_signal = sig;
}

void	ft_set_signals(int mode)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (mode == PROMPT || mode == HEREDOC)
	{
		sa.sa_handler = &sig_prompt;
		if (mode == HEREDOC)
			sa.sa_handler = &sig_heredoc;
		sigaction(SIGINT, &sa, 0);
		sa.sa_handler = SIG_IGN;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGQUIT, &sa, 0);
		return ;
	}
	else if (mode == FORK)
		sa.sa_handler = SIG_DFL;
	else if (mode == SILENT)
	{
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = sig_silent;
	}
	sigaction(SIGQUIT, &sa, 0);
	sigaction(SIGINT, &sa, 0);
}
