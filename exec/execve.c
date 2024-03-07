/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:36:30 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:36:36 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cmd(t_expression *exp, t_env **envs)
{
	if (ft_strcmp(exp->value, "echo"))
		ft_echo(exp);
	else if (ft_strcmp(exp->value, "env"))
		ft_env(envs, exp);
	else if (ft_strcmp(exp->value, "pwd"))
		ft_pwd(exp);
	else
		return (1);
	return (0);
}

int	setup_stdio(t_expression *exp)
{
	if (exp->fd_in != DEFAULT && (dup2(exp->fd_in, STDIN_FILENO) == -1
			|| close(exp->fd_in) == -1))
		return (ERROR_PIPE);
	if (exp->fd_out != DEFAULT && (dup2(exp->fd_out, STDOUT_FILENO) == -1
			|| close(exp->fd_out) == -1))
		return (ERROR_PIPE);
	return (OK);
}

int	child_proc(t_expression *exp, t_env **envs, int fd[2], int has_pipe)
{
	char	*path;
	char	**args;
	char	**mtx;

	if (has_pipe)
		close(fd[0]);
	if (setup_stdio(exp) != OK)
		return (ERROR_PIPE);
	if (!check_cmd(exp, envs))
		exit(0);
	path = get_path(exp->value, *envs);
	if (!path || (path == exp->value && access(path, 0)))
		return (not_found_or_no_such(exp->value, fd, has_pipe, path));
	args = get_mtx_args(exp->args, path);
	mtx = ft_env_list_to_matrix(envs);
	execve(path, args, mtx);
	if (has_pipe)
		close(fd[1]);
	free_mtx(args);
	free_mtx(mtx);
	if (path && *path)
		free(path);
	exit(1);
	return (OK);
}

int	ft_execve(t_expression *exp, t_env **envs)
{
	int	has_pipe;
	int	fd[2];
	int	res;

	res = OK;
	has_pipe = check_pipe(exp);
	if (has_pipe && pipe(fd) == -1)
		return (ERROR_PIPE);
	if (has_pipe)
	{
		if (exp->fd_out == DEFAULT)
			exp->fd_out = fd[1];
		set_next_pipe(exp, fd[0]);
	}
	exp->pid = fork();
	if (exp->pid == 0)
	{
		ft_set_signals(FORK);
		child_proc(exp, envs, fd, has_pipe);
	}
	if (exp->fd_in != DEFAULT)
		close(exp->fd_in);
	if (has_pipe)
		close(fd[1]);
	return (res);
}

int	setup_exec(t_expression *exp, t_env **envs)
{
	int	res;

	if (ft_strcmp(exp->value, "exit"))
		return (ft_exit(exp->args));
	if (ft_strcmp(exp->value, "export"))
		return (ft_export(exp, envs) * 0);
	else if (ft_strcmp(exp->value, "unset"))
		return (ft_unset(exp, envs) * 0);
	else if (ft_strcmp(exp->value, "cd"))
		return (ft_cd(exp, envs) * 0);
	res = ft_execve(exp, envs);
	return (res);
}
