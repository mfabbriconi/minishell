/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:36:59 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 19:48:55 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_arg *arg)
{
	write(1, "brexit\n", 7);
	if (arg && arg->value)
	{
		if (!is_number(arg->value))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				arg->value);
			arg->value = "255";
		}
		exit(ft_atoi(arg->value));
	}
	else
		exit(0);
}
