/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:03 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:40:04 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	stop_parse_dollar(char *s)
{
	if (stop_parse_cmd(s))
		return (1);
	if (is_space(*s))
		return (1);
	if (*s == QUOTE_S || *s == QUOTE_D || *s == DOLLAR)
		return (1);
	return (0);
}

char	*take_env_key(char *str, int *i)
{
	int	t;

	(*i)++;
	t = *i;
	while (!stop_parse_dollar(str + (*i)))
		(*i)++;
	return (ft_substr(str, t, (*i) - t));
}

void	expand_dollar(t_all *all, char *str, int i[2], char *dst)
{
	char	*tmp;
	char	*envval;

	tmp = take_env_key(str, &i[0]);
	if (ft_strlen(tmp) == 1 && *tmp == QUESTION)
	{
		if (all->g_status == 0 && g_signal == SIGINT)
			envval = ft_strdup("130");
		else
			envval = ft_itoa(all->g_status);
	}
	else
		envval = get_env(all->envs, tmp);
	if (dst)
		ft_strcpy(dst + i[1], envval);
	i[1] += ft_strlen(envval);
	free(tmp);
	free(envval);
}

// add check
char	*alloc_dollar(t_all *all, char *str)
{
	int		i[2];
	char	*res;

	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		i[1] += skip_space(str, &i[0]);
		if (str[i[0]] == DOLLAR && !stop_parse_dollar(str + (i[0] + 1)))
			expand_dollar(all, str, i, 0);
		else if (i[0]++ >= 0 && i[1]++ >= 0)
			continue ;
	}
	res = (char *)malloc(sizeof(char) * i[1] + 1);
	res[i[1]] = 0;
	return (res);
}

char	*solve_dollar(t_all *all, char *str)
{
	int		i[2];
	char	*res;

	i[0] = 0;
	i[1] = 0;
	res = alloc_dollar(all, str);
	while (str[i[0]])
	{
		if (str[i[0]] == DOLLAR && !stop_parse_dollar(str + (i[0] + 1)))
			expand_dollar(all, str, i, res);
		else
			res[i[1]++] = str[i[0]++];
	}
	free(str);
	return (res);
}
