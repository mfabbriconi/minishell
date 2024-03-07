/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:37:50 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:37:53 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_found_or_no_such(char *str, int fd[2], int has_pipe, char *path)
{
	if (has_pipe)
	{
		close(fd[0]);
		close(fd[1]);
	}
	write(1, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(1, str, ft_strlen(str));
	if (!path)
		write(1, " : No such file or directory\n", 29);
	else
		write(1, " : command not found\n", 21);
	exit(127);
	return (OK);
}

char	*get_path_loop(char **buff, char *arg)
{
	int		i;
	char	*path;
	char	*basepath;

	i = -1;
	path = 0;
	basepath = 0;
	while (buff[++i])
	{
		basepath = ft_strjoin(buff[i], "/");
		path = ft_strjoin(basepath, arg);
		if (!access(path, 0))
		{
			free(basepath);
			return (path);
		}
		free(basepath);
		free(path);
	}
	return (arg);
}

char	*get_path(char *arg, t_env *envs)
{
	char	*path;
	char	**buff;

	if (!arg)
		return (0);
	path = get_env(envs, "PATH");
	if (!path)
		return (0);
	buff = ft_split(path, ':');
	if (!buff)
		return (0);
	path = get_path_loop(buff, arg);
	free_mtx(buff);
	return (path);
}

int	check_pipe(t_expression *exp)
{
	exp = exp->next;
	while (exp)
	{
		if (exp->type == OPERATOR)
			return (1);
		exp = exp->next;
	}
	return (0);
}

void	set_next_pipe(t_expression *exp, int fd)
{
	exp = exp->next;
	while (exp)
	{
		if (exp->type == COMMAND)
		{
			if (exp->fd_in == DEFAULT)
				exp->fd_in = fd;
			return ;
		}
		exp = exp->next;
	}
}
