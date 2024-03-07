/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:39:57 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:39:58 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	stop_parse_cmd(char *s)
{
	if (!*s)
		return (1);
	if (is_operator(s))
		return (1);
	if (is_redirection(s))
		return (1);
	return (0);
}

int	add_arg(t_arg **args, char *str)
{
	t_arg	*new;
	t_arg	*tmp;

	new = (t_arg *)malloc(sizeof(t_arg));
	if (!new)
		return (MALLOC_ERROR);
	new->next = 0;
	new->value = str;
	if (!*args)
	{
		*args = new;
		return (OK);
	}
	tmp = *args;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (OK);
}

int	parse_command(t_expression **exp, t_all *all, char *input, int *i)
{
	int		c;
	int		res;
	char	*tmp;

	c = 0;
	if ((*exp)->value)
		c = 1;
	res = OK;
	tmp = 0;
	while (input[*i])
	{
		if (stop_parse_cmd(input + (*i)))
			return (OK);
		res = take_str(input, i, &tmp);
		if (res != OK)
			return (res);
		res = add_value(exp, all, tmp, &c);
		if (res != OK)
			return (res);
		if (input[*i] && !stop_parse_cmd(input + (*i)))
			(*i)++;
	}
	return (res);
}

int	alloc_cmd(t_expression **ret)
{
	*ret = (t_expression *)malloc(sizeof(t_expression));
	if (!*ret)
		return (MALLOC_ERROR);
	(*ret)->next = 0;
	(*ret)->prev = 0;
	(*ret)->args = 0;
	(*ret)->type = COMMAND;
	(*ret)->value = 0;
	(*ret)->status = DEFAULT;
	(*ret)->fd_in = DEFAULT;
	(*ret)->fd_out = DEFAULT;
	(*ret)->pid = DEFAULT;
	return (OK);
}

int	add_command(t_all *all, char *input, int *i, t_expression **last_cmd)
{
	int	res;
	int	is_new;

	is_new = 0;
	if (!*last_cmd)
	{
		if (alloc_cmd(last_cmd) != OK)
			return (MALLOC_ERROR);
		is_new = 1;
	}
	res = parse_command(last_cmd, all, input, i);
	if (res != OK)
	{
		free_exps(*last_cmd);
		return (res);
	}
	if (!(all->tree))
	{
		all->tree = *last_cmd;
		return (OK);
	}
	if (is_new)
		add_next(&(all->tree), *last_cmd);
	return (OK);
}
