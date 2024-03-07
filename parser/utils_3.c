/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:45 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:40:47 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_exp(t_expression **exps, t_expression *todel)
{
	t_expression	*tmp;

	tmp = *exps;
	if (tmp == todel)
	{
		*exps = todel->next;
		todel->next = 0;
		free_exps(todel);
		return ;
	}
	while (tmp)
	{
		if (tmp == todel)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			todel->next = 0;
			free_exps(todel);
			break ;
		}
		tmp = tmp->next;
	}
}

int	delete_and_pop(t_expression **exps, t_expression *cmd,
		t_expression **valid_io, int io[2])
{
	int	i;

	i = -1;
	while (++i < 2)
		if (valid_io[i])
			delete_exp(exps, valid_io[i]);
	if (io[0] == ERROR_HEREDOC_CLOSED)
		return (ERROR_HEREDOC_CLOSED);
	if (cmd)
	{
		cmd->fd_in = io[0];
		cmd->fd_out = io[1];
	}
	return (OK);
}

int	handle_useless_redirs(char redir, t_all *all, t_expression **tmp)
{
	t_expression	*to_del;

	if (redir == OUTPUT_REDIR)
		open((*tmp)->args->value, get_perms(*tmp), 0644);
	else if (*((*tmp)->value) + 1 != 0)
		if (open_heredoc(all, (*tmp)->args->value, 1) == ERROR_HEREDOC_CLOSED)
			return (ERROR_HEREDOC_CLOSED);
	to_del = *tmp;
	*tmp = (*tmp)->prev;
	delete_exp(&all->tree, to_del);
	return (OK);
}

int	clear_redir(t_all *all, t_expression *valid_redir, char redir)
{
	t_expression	*tmp;

	if (!valid_redir)
		return (OK);
	tmp = valid_redir->prev;
	while (tmp)
	{
		if (tmp->type == OPERATOR)
			break ;
		if (tmp->type == REDIRECTION && *(tmp->value) == redir)
		{
			if (handle_useless_redirs(redir, all, &tmp) != OK)
				return (ERROR_HEREDOC_CLOSED);
		}
		else
			tmp = tmp->prev;
	}
	return (OK);
}
