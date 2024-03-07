/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:37:40 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 18:37:42 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*tmp_heredoc_file(int reset)
{
	static int	i = 0;
	char		*tmp;
	char		*res;

	if (reset)
	{
		i = 0;
		return (0);
	}
	tmp = ft_itoa(i++);
	res = ft_strjoin(HEREDOC_TMP_FILE, tmp);
	free(tmp);
	return (res);
}

void	delete_heredocs(void)
{
	int		i;
	char	*tmp;
	char	*f_name;

	i = -1;
	while (++i < HEREDOC_MAX)
	{
		tmp = ft_itoa(i);
		f_name = ft_strjoin(HEREDOC_TMP_FILE, tmp);
		if (!access(f_name, 0))
			unlink(f_name);
		free(tmp);
		free(f_name);
	}
	tmp_heredoc_file(1);
}

void	write_on_heredoc(t_all *all, char *input, int tmp_file_fd)
{
	char	*tmp;

	tmp = solve_value_body(all, input, 1);
	if (ft_strlen(tmp) > 0)
		write(tmp_file_fd, tmp, ft_strlen(input));
	write(tmp_file_fd, "\n", 1);
	free(tmp);
}

void	heredoc_loop(t_all *all, char *delim, int ghost, int tmp_file_fd)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strlen(input) > 0 && !ft_strncmp(input, delim, ft_strlen(input)))
			break ;
		if (!ghost)
			write_on_heredoc(all, input, tmp_file_fd);
		free(input);
	}
	if (!ghost)
		close(tmp_file_fd);
	if (!input)
		exit(0);
	exit(1);
}

int	open_heredoc(t_all *all, char *delim, int ghost)
{
	int		tmp_file_fd;
	char	*f_name;
	pid_t	pid;
	int		status;

	tmp_file_fd = 0;
	if (!ghost)
		f_name = tmp_heredoc_file(0);
	pid = fork();
	if (!pid)
	{
		ft_set_signals(HEREDOC);
		tmp_file_fd = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		heredoc_loop(all, delim, ghost, tmp_file_fd);
	}
	waitpid(pid, &status, 0);
	if (!status)
		return (ERROR_HEREDOC_CLOSED);
	if (!ghost)
	{
		tmp_file_fd = open(f_name, O_RDONLY, 0644);
		free(f_name);
	}
	return (tmp_file_fd);
}
