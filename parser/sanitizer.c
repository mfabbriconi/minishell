/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:27 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:40:30 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	solve_valid_redir(t_all *all, t_expression *cmd, t_expression **valid_io)
{
	int	io[2];

	io[0] = DEFAULT;
	io[1] = DEFAULT;
	if (valid_io[0] && *(valid_io[0]->value + 1) == 0)
		io[0] = open(valid_io[0]->args->value, O_RDONLY, 0644);
	else if (valid_io[0] && *(valid_io[0]->value + 1) != 0)
		io[0] = open_heredoc(all, valid_io[0]->args->value, 0);
	if (valid_io[1])
		io[1] = open(valid_io[1]->args->value, get_perms(valid_io[1]), 0644);
	return (delete_and_pop(&all->tree, cmd, valid_io, io));
}

int	get_valid_io(t_expression *exp, t_expression ***valid_io, int i[2])
{
	t_expression	*tmp;

	(*valid_io) = (t_expression **)malloc(sizeof(t_expression *) * 2);
	(*valid_io)[0] = 0;
	(*valid_io)[1] = 0;
	tmp = exp;
	if (exp->type == OPERATOR)
		tmp = exp->prev;
	while (tmp)
	{
		if (tmp->type == OPERATOR)
			break ;
		if (tmp->type == REDIRECTION)
		{
			if (*(tmp->value) == INPUT_REDIR && i[0]++ >= 0 && !(*valid_io)[0])
				(*valid_io)[0] = tmp;
			if (*(tmp->value) == OUTPUT_REDIR && i[1]++ >= 0 && !(*valid_io)[1])
				(*valid_io)[1] = tmp;
			if (*(tmp->value + 1) == 0 && *(tmp->value) == INPUT_REDIR
				&& access(tmp->args->value, F_OK))
				return (ERROR_FILE_NOT_FOUND);
		}
		tmp = tmp->prev;
	}
	return (OK);
}

int	check_redir_tree(t_all *all, t_expression *exp, t_expression **cmd)
{
	int				i[2];
	int				res;
	t_expression	**valid_io;

	i[0] = 0;
	i[1] = 0;
	ft_set_signals(SILENT);
	res = get_valid_io(exp, &valid_io, i);
	if (res != OK)
		return (res);
	if (i[0] > 1)
		res = clear_redir(all, valid_io[0], INPUT_REDIR);
	if (res == ERROR_HEREDOC_CLOSED)
		return (res);
	if (i[1] > 1)
		res = clear_redir(all, valid_io[1], OUTPUT_REDIR);
	if (res == ERROR_HEREDOC_CLOSED)
		return (res);
	res = solve_valid_redir(all, *cmd, valid_io);
	if (res == ERROR_HEREDOC_CLOSED)
		return (res);
	*cmd = 0;
	free(valid_io);
	return (OK);
}

int	sanitizer(t_all *all)
{
	int				res;
	t_expression	*tmp;
	t_expression	*cmd;

	res = OK;
	tmp = all->tree;
	cmd = 0;
	while (tmp)
	{
		res = parser_checks(tmp, &all->tree);
		if (res != OK)
			return (res);
		if (tmp->type == COMMAND)
			cmd = tmp;
		if (tmp->type == OPERATOR || !tmp->next)
		{
			res = check_redir_tree(all, tmp, &cmd);
			ft_set_signals(PROMPT);
			if (res != OK)
				return (res);
		}
		tmp = tmp->next;
	}
	return (res);
}
