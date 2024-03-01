/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/02/29 19:10:09 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "pipex.h"

void	ft_free_char_pp(char **stack)
{
	int	i;

	i = 0;
	while (stack[i] != NULL)
	{
		free(stack[i]);
		i++;
	}
	free (stack);
}

int	ft_char_pp_len(char **stack)
{
	int	i;

	i = 0;
	while (stack[i] != NULL)
		i++;
	return (i);
}

void	print_char_pp(char **stack)
{
	int	i;

	i = 0;
	while (stack[i] != NULL)
	{
		ft_printf("%s\n", stack[i]);
		i++;
	}
}

int	ft_open_infile(char *file, t_info *commands)
{
	int		fd;

	fd = open(file, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror("Open failure");
		return (ERROR);
	}
	commands->fd1 = fd;
	return (OK);
}

int	ft_open_outfile(char *file, t_info *commands)
{
	int		fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror("Open failure");
		return (ERROR);
	}
	commands->fd2 = fd;
	return (OK);
}
