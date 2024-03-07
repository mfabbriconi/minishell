/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:50 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 19:49:49 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_last(t_env *env, t_env *next)
{
	t_env	*buff;

	buff = env;
	while (buff->next)
		buff = buff->next;
	buff->next = next;
}

void	add_next(t_expression **exps, t_expression *new)
{
	t_expression	*tmp;

	tmp = *exps;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
