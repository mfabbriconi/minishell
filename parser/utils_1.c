/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:33 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:40:34 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_perms(t_expression *valid_o)
{
	if (*(valid_o->value + 1) == 0)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (*(valid_o->value + 1) != 0)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (0);
}

int	is_operator(char *s)
{
	if (*s == PIPE)
		return (1);
	return (0);
}

int	is_redirection(char *s)
{
	if (*s != INPUT_REDIR && *s != OUTPUT_REDIR)
		return (0);
	if (!ft_strncmp(s, INPUT_REDIR_A, 2) || !ft_strncmp(s, OUTPUT_REDIR_A, 2))
		return (2);
	return (1);
}

int	skip_space(char *input, int *i)
{
	int	l;

	l = *i;
	while (input[*i] && is_space(input[*i]))
		(*i)++;
	return (*i - l);
}

int	skip_quote(char *input, int *i)
{
	char	quote;
	int		l;

	l = *i;
	quote = 0;
	if (input[*i] == QUOTE_D)
		quote = QUOTE_D;
	if (input[*i] == QUOTE_S)
		quote = QUOTE_S;
	if (quote == QUOTE_S || quote == QUOTE_D)
	{
		(*i)++;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i])
			(*i)++;
		else
			return (ERROR_UNCLOSED_QUOTES);
	}
	return (*i - l);
}
