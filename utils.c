/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:41:28 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:41:30 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	logic_handle_signals(t_expression *exp)
{
	if (g_signal == SIGINT)
	{
		printf("\n");
		exp->status = 130;
	}
	else if (g_signal == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		exp->status = 131;
	}
}

t_expression	*get_last_exp(t_expression *exps)
{
	if (!exps)
		return (exps);
	while (exps->next)
		exps = exps->next;
	return (exps);
}
