/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:37:19 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:37:23 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_expression *cmd)
{
	int		fd;
	char	cwd[256];

	(void)cmd;
	fd = 1;
	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, fd);
	write(fd, "\n", 1);
	return (1);
}
