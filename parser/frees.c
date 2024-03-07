/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:13 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:40:14 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_envs(t_env *envs)
{
	t_env	*tmp;

	while (envs)
	{
		tmp = envs;
		envs = envs->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_args(t_arg *args)
{
	t_arg	*tmp;

	while (args)
	{
		tmp = args;
		args = args->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_exps(t_expression *exps)
{
	t_expression	*tmp;

	while (exps)
	{
		tmp = exps;
		exps = exps->next;
		if (tmp->value)
			free(tmp->value);
		if (tmp->args)
			free_args(tmp->args);
		free(tmp);
	}
}
