/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mtx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:35:10 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:35:15 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_env **e, t_arg *arg, int a)
{
	int		i;
	t_arg	*tmp;
	t_env	*env;

	i = 0;
	if (a)
	{
		tmp = arg;
		while (tmp)
		{
			i++;
			tmp = tmp->next;
		}
	}
	else
	{
		env = *e;
		while (env)
		{
			i++;
			env = env->next;
		}
	}
	return (i);
}

char	**ft_env_list_to_matrix(t_env **env)
{
	int		i;
	t_env	*tmp;
	char	*t;
	char	**new_env;

	tmp = *env;
	i = ft_lstsize(env, 0, 0);
	new_env = malloc(sizeof(char *) * i + 1);
	new_env[i] = 0;
	i = 0;
	while (tmp)
	{
		t = ft_strjoin(tmp->key, "=");
		new_env[i++] = ft_strjoin(t, tmp->value);
		free(t);
		tmp = tmp->next;
	}
	return (new_env);
}

void	free_mtx(char **mtx)
{
	int	i;

	if (!mtx || !*mtx)
		return ;
	i = -1;
	while (mtx[++i])
		free(mtx[i]);
	free(mtx);
}

char	**get_mtx_args(t_arg *args, char *path)
{
	char	**array;
	t_arg	*buff;
	int		i;

	i = ft_lstsize(0, args, 1);
	buff = args;
	array = (char **)malloc(sizeof(char *) * (i + 2));
	array[i + 1] = 0;
	array[0] = path;
	i = 1;
	while (buff)
	{
		array[i] = ft_strdup(buff->value);
		buff = buff->next;
		i++;
	}
	return (array);
}

void	print_mtx(char **mtx)
{
	int	i;

	i = -1;
	if (!mtx)
		return ;
	while (mtx[++i])
		printf("%s\n", mtx[i]);
}
