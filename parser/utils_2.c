/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:40 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:40:42 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_error_near(char *str)
{
	printf("syntax error near: unexpected token `%s'\n", str);
	return (ERROR_PARSE);
}

int	parser_checks(t_expression *tmp, t_expression **exps)
{
	if (tmp->type == OPERATOR && !tmp->next)
		return (parse_error_near(tmp->value));
	if (tmp->type == OPERATOR && tmp->next->type == OPERATOR)
		return (parse_error_near(tmp->value));
	if (tmp == *exps && tmp->type == OPERATOR)
		return (parse_error_near(tmp->value));
	return (OK);
}

int	take_str(char *input, int *i, char **str)
{
	int	tmp;

	if (!input[*i])
		return (0);
	tmp = *i;
	while (input[*i] && !is_space(input[*i]) && !stop_parse_cmd(&input[*i]))
	{
		if (input[*i] == QUOTE_D || input[*i] == QUOTE_S)
		{
			if (skip_quote(input, i) == ERROR_UNCLOSED_QUOTES)
				return (ERROR_UNCLOSED_QUOTES);
			continue ;
		}
		(*i)++;
	}
	*str = ft_substr(input, tmp, (*i) - tmp);
	return (OK);
}

int	count_till_quote(char *str, char quote)
{
	int	i;

	if (quote != QUOTE_S && quote != QUOTE_D)
		return (ft_strlen(str));
	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i - 1);
}

void	solve_quote(t_all *all, char *value, int i[2], char *dst)
{
	int		t;
	char	quote;
	char	*tmp;

	tmp = 0;
	quote = value[i[0]];
	t = count_till_quote(value + i[0], value[i[0]]);
	tmp = ft_substr(value + i[0], 1, t);
	if (quote == QUOTE_D)
		tmp = solve_dollar(all, tmp);
	if (dst)
		ft_strcpy(dst + (i[1]), tmp);
	i[1] += ft_strlen(tmp);
	i[0] += t + 1;
	free(tmp);
}
