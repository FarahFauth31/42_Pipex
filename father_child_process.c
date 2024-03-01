/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father_child_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:10:19 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/02/29 20:15:09 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "libft/libft.h"
#include "pipex.h"

int	command1_child(pid_t child_id, t_info *commands, char **envp,
		int pipe_fd[2])
{
	if (child_id == 0)
	{
		if (dup2(commands->fd1, STDIN_FILENO) == -1 || dup2(pipe_fd[1],
				STDOUT_FILENO) == -1)
			exit (-1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(commands->fd1);
		if (execve(commands->path1, commands->command1, envp) == -1)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(commands->path1, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit (127);
		}
	}
	return (OK);
}

int	command2_child(pid_t child_id, t_info *commands, char **envp,
		int pipe_fd[2])
{
	if (child_id == 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1 || dup2(commands->fd2,
				STDOUT_FILENO) == -1)
			exit (-1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(commands->fd2);
		if (execve(commands->path2, commands->command2, envp) == -1)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(commands->path2, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit (127);
		}
	}
	return (OK);
}

int	ft_wait_exit_status(pid_t child_id[2])
{
	int	status1;
	int	status2;

	waitpid(child_id[0], &status1, 0);
	waitpid(child_id[1], &status2, 0);
	if (WIFEXITED(status1))
		WEXITSTATUS(status1);
	if (WIFEXITED(status2))
		WEXITSTATUS(status2);
	return (OK);
}

int	ft_father_child(char **envp, t_info *commands)
{
	int		pipe_fd[2];
	pid_t	child_id[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe failure");
		return (ERROR);
	}
	child_id[0] = fork();
	command1_child(child_id[0], commands, envp, pipe_fd);
	child_id[1] = fork();
	command2_child(child_id[1], commands, envp, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (child_id[0] == -1 || child_id[1] == -1)
	{
		perror("Fork failure");
		return (ERROR);
	}
	ft_wait_exit_status(child_id);
	return (OK);
}
