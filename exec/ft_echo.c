/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:35:53 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:35:55 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

int	ft_echo(t_expression *cmd)
{
	t_arg	*buff;
	int		n;
	int		fd;

	n = 0;
	buff = cmd->args;
	fd = 1;
	if (!buff)
		ft_putstr_fd("\n", fd);
	while (ft_strlen(buff->value) == 2 && ft_strcmp("-n", buff->value))
	{
		buff = buff->next;
		n = 1;
	}
	while (buff)
	{
		ft_putstr_fd(buff->value, fd);
		if (buff->next)
			write(fd, " ", 1);
		buff = buff->next;
	}
	if (n != 1)
		ft_putstr_fd("\n", fd);
	return (0);
}
