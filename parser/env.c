/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:08 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 19:50:07 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(t_env *env, char *key)
{
	int		i;
	size_t	l;
	t_env	*buff;

	buff = env;
	i = ft_strlen(key);
	l = (size_t)i;
	while (buff)
	{
		if (ft_strlen(buff->key) == l && !ft_strncmp(buff->key, key, i))
			return (ft_strdup(buff->value));
		buff = buff->next;
	}
	return (0);
}

void	*new_env(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = key;
	new->value = value;
	new->next = 0;
	if (!*env)
	{
		*env = new;
		return (0);
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

t_env	*parse_envp(char *envp[])
{
	t_env	*env;
	int		i;
	int		c;

	i = -1;
	env = 0;
	while (envp[++i])
	{
		c = -1;
		while (envp[i][++c] && envp[i][c] != '=')
			continue ;
		new_env(&env, ft_substr(envp[i], 0, c), ft_substr(envp[i], c + 1,
				ft_strlen(envp[i]) - c - 1));
	}
	return (env);
}

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("key: %s\nvalue: %s\n-----------\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
