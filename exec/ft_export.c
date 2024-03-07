/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:37:08 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:37:12 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pop_env(t_env **new, char *key, char *value)
{
	int	f;

	f = 0;
	if (!*key && f++ >= 0)
		free(key);
	if (!*value && f++ >= 0)
		free(value);
	if (f > 0)
	{
		free(*new);
		return (1);
	}
	(*new)->key = key;
	(*new)->value = value;
	(*new)->next = 0;
	return (0);
}

static int	ft_new_env(t_env **env, char *new_env, int i)
{
	t_env	*new;
	t_env	*buff;
	size_t	bl;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	if (pop_env(&new, ft_strdup(new_env), ft_strdup(&new_env[i + 1])))
		return (0);
	buff = *env;
	while (buff)
	{
		bl = ft_strlen(buff->key);
		if (bl == ft_strlen(new->key) && !ft_strncmp(buff->key, new->key, bl))
		{
			free(buff->value);
			buff->value = new->value;
			free(new->key);
			free(new);
			return (1);
		}
		buff = buff->next;
	}
	ft_add_last(*env, new);
	return (1);
}

char	**sort_mtx(char **mtx)
{
	int		i;
	int		x;
	char	*buff;

	i = 0;
	while (mtx[i])
	{
		x = i + 1;
		while (mtx[x])
		{
			if (ft_strcmp2(mtx[i], mtx[x]) > 0)
			{
				buff = mtx[i];
				mtx[i] = mtx[x];
				mtx[x] = buff;
			}
			x++;
		}
		i++;
	}
	return (mtx);
}

int	export_no_args(t_env **env)
{
	int		i[2];
	char	**mtx;

	mtx = ft_env_list_to_matrix(env);
	mtx = sort_mtx(mtx);
	i[0] = 0;
	while (mtx[i[0]])
	{
		i[1] = 0;
		while (mtx[i[0]][i[1]] && mtx[i[0]][i[1]] != '=')
			(i[1])++;
		mtx[i[0]][i[1]] = 0;
		printf("declare -x %s=\"%s\"\n", mtx[i[0]], &(mtx[i[0]][i[1] + 1]));
		i[0]++;
	}
	free_mtx(mtx);
	return (0);
}

int	ft_export(t_expression *cmd, t_env **env)
{
	int		i;
	char	*value;
	t_arg	*args;

	cmd->status = 0;
	if (!cmd->args)
		return (export_no_args(env));
	args = cmd->args;
	while (args)
	{
		value = args->value;
		i = 0;
		while (value[i] && value[i] != '=')
			i++;
		value[i] = 0;
		ft_new_env(env, value, i);
		args = args->next;
	}
	return (0);
}
