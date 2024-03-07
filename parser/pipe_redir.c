/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:22 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:42:12 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_redir(t_expression *exp, t_all *all, char *input, int i[2])
{
	char	*tmp;
	int		res;

	tmp = 0;
	exp->value = ft_substr(input, i[0], i[1]);
	i[0] += i[1];
	if (is_operator(input + (i[0])) || is_redirection(input + i[0]))
		return (ERROR_INVALID_REDIR);
	skip_space(input, &i[0]);
	res = take_str(input, &(i[0]), &tmp);
	if (res != OK)
		return (ERROR_UNCLOSED_QUOTES);
	if (!tmp)
		return (ERROR_NO_REDIR_ARG);
	add_arg(&exp->args, solve_value_body(all, tmp, 0));
	free(tmp);
	return (OK);
}

int	add_redir(t_all *all, char *input, int i[2])
{
	int				res;
	t_expression	*new;

	new = (t_expression *)malloc(sizeof(t_expression));
	if (!new)
		return (MALLOC_ERROR);
	new->next = 0;
	new->prev = 0;
	new->args = 0;
	new->type = REDIRECTION;
	new->pid = DEFAULT;
	new->status = DEFAULT;
	res = parse_redir(new, all, input, i);
	if (res != OK)
	{
		free_exps(new);
		return (res);
	}
	if (!all->tree)
	{
		all->tree = new;
		return (OK);
	}
	add_next(&(all->tree), new);
	return (OK);
}

int	add_pipe(t_expression **exps, int i[2])
{
	t_expression	*new;

	new = (t_expression *)malloc(sizeof(t_expression));
	if (!new)
		return (MALLOC_ERROR);
	new->next = 0;
	new->prev = 0;
	new->args = 0;
	new->type = OPERATOR;
	new->pid = DEFAULT;
	new->status = DEFAULT;
	new->value = ft_strdup("|");
	i[0] += 1;
	if (!*exps)
	{
		*exps = new;
		return (OK);
	}
	add_next(exps, new);
	return (OK);
}
