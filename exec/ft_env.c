/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:35:45 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 19:50:26 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env **env, t_expression *cmd)
{
	t_env	*buff;
	int		fd;

	(void)cmd;
	fd = 1;
	if (!env)
		return (0);
	buff = *env;
	while (buff)
	{
		ft_putstr_fd(buff->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(buff->value, fd);
		ft_putstr_fd("\n", fd);
		buff = buff->next;
	}
	return (1);
}
