/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/02/23 19:57:20 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "pipex.h"

void	ft_free_commands(t_info *commands)
{
	if (commands->command1 != NULL)
		ft_free_char_pp(commands->command1);
	if (commands->command2 != NULL)
		ft_free_char_pp(commands->command2);
	if (commands->path1 != NULL)
		free(commands->path1);
	if (commands->path2 != NULL)
		free(commands->path2);
	if (commands->temp_file != NULL)
		free(commands->temp_file);
	if (commands != NULL)
		free(commands);
}

void	ft_cleanup(char *in_file, t_info *commands)
{
	close(commands->fd1);
	close(commands->fd2);
	if (commands->no_infile == 1)
		unlink(in_file);
	if (commands->no_permissions == 1)
		unlink(commands->temp_file);
	ft_free_commands(commands);
}
