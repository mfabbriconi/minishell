/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:59 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:41:01 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_cmd_status(t_expression *cmds)
{
	t_expression	*buff;

	buff = cmds;
	while (buff)
	{
		if (buff->status != DEFAULT)
			return (buff->status);
		buff = buff->prev;
	}
	return (-1);
}

void	wait_procs(t_expression *exp, t_all *all)
{
	int				status;
	t_expression	*tmp;

	tmp = exp;
	while (tmp)
	{
		if (tmp->pid != DEFAULT)
		{
			if (tmp->status != DEFAULT)
				return ;
			waitpid(tmp->pid, &status, 0);
			tmp->status = WEXITSTATUS(status);
			logic_handle_signals(tmp);
			all->g_status = tmp->status;
			g_signal = 0;
		}
		tmp = tmp->prev;
	}
}

int	executor(t_all *all)
{
	int				res;
	t_expression	*tmp;

	res = 0;
	g_signal = 0;
	tmp = all->tree;
	ft_set_signals(SILENT);
	while (tmp)
	{
		if (tmp->type == COMMAND)
			res = setup_exec(tmp, &all->envs);
		tmp = tmp->next;
	}
	tmp = get_last_exp(all->tree);
	wait_procs(tmp, all);
	delete_heredocs();
	return (res);
}
