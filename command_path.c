/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:33:45 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/02/29 19:09:49 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "libft/libft.h"
#include "pipex.h"

char	*ft_return_accessible_path(char **available_paths, char *command)
{
	int		i;
	char	*path;
	char	*temp_path;

	i = 0;
	if (available_paths == NULL)
		return (NULL);
	while (available_paths[i] != NULL)
	{
		path = ft_strjoin(available_paths[i], "/");
		if (path == NULL)
			return (NULL);
		temp_path = ft_strjoin(path, command);
		free(path);
		if (temp_path == NULL)
			return (NULL);
		if (access(temp_path, X_OK) == 0)
			return (temp_path);
		free(temp_path);
		i++;
	}
	return (NULL);
}

char	*ft_find_command_path(char **envp, char *command, int i)
{
	char	*temp_path;
	char	**available_paths;

	if (command == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			temp_path = ft_strtrim(envp[i], "PATH=");
			if (temp_path == NULL)
				return (NULL);
			available_paths = ft_split(temp_path, ':');
			free(temp_path);
			temp_path = ft_return_accessible_path(available_paths, command);
			ft_free_char_pp(available_paths);
			if (temp_path == NULL)
				return (ft_strdup(command));
			return (temp_path);
		}
		i++;
	}
	return (ft_strdup(command));
}

t_info	*ft_fill_commands(char **argv, char **envp)
{
	t_info	*commands;

	commands = (t_info *)malloc(sizeof(t_info));
	if (commands == NULL)
		return (NULL);
	commands->command1 = ft_return_commands(argv[1]);
	commands->path1 = ft_find_command_path(envp, commands->command1[0], 0);
	commands->command2 = ft_return_commands(argv[2]);
	commands->path2 = ft_find_command_path(envp, commands->command2[0], 0);
	commands->no_infile = 0;
	commands->no_permissions = 0;
	commands->temp_file = NULL;
	if (commands->command1 == NULL || commands->command2 == NULL
		|| commands->path1 == NULL || commands->path2 == NULL)
	{
		ft_putstr_fd("pipex: ", 2);
		perror("Malloc fail");
		ft_free_commands(commands);
		return (NULL);
	}
	return (commands);
}
