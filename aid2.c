/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aid2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/03/01 14:02:17 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "pipex.h"

int	ft_file_permissions(char *file1, char *file2, t_info *commands)
{
	if (ft_infile_permissions(file1, commands) == ERROR
		|| ft_outfile_permissions(file2, commands) == ERROR)
		return (ERROR);
	return (OK);
}

char	*ft_create_file_name(void)
{
	char	*number;
	int		n;

	n = 0;
	while (n >= 0)
	{
		number = ft_itoa(n);
		if (ft_file_exists(number) == ERROR)
			return (number);
		n++;
	}
	return (NULL);
}

int	ft_find_flag(char const *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == '-')
			return (1);
		i++;
	}
	return (0);
}
