/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:51:57 by farah             #+#    #+#             */
/*   Updated: 2024/03/01 14:02:18 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define OK 0
# define ERROR 1
# define NO_INFILE 2
# define NO_PERMISSIONS 3

typedef struct s_info
{
	char	**command1;
	char	**command2;
	char	*path1;
	char	*path2;
	int		fd1;
	int		fd2;
	int		no_infile;
	int		no_permissions;
	char	*temp_file;
}			t_info;

/* Access */
int		ft_file_exists(char *file);
int		ft_read_permission(char *file);
int		ft_write_permission(char *file);
int		ft_infile_permissions(char *file, t_info *commands);
int		ft_outfile_permissions(char *file, t_info *commands);

/* Command path */
char	*ft_find_command_path(char **envp, char *command, int i);
char	*ft_return_accessible_path(char **available_paths, char *command);
t_info	*ft_fill_commands(char **argv, char **envp);
void	ft_free_commands(t_info *commands);

/* Father Child Processes */
int		command1_child(pid_t child_id, t_info *commands, char **envp,
			int pipe_fd[2]);
int		command2_child(pid_t child_id, t_info *commands, char **envp,
			int pipe_fd[2]);
int		ft_father_child(char **envp, t_info *commands);

/* Aid */
void	ft_free_char_pp(char **stack);
int		ft_char_pp_len(char **stack);
void	print_char_pp(char **stack);
int		ft_open_infile(char *file, t_info *commands);
int		ft_open_outfile(char *file, t_info *commands);
int		ft_file_permissions(char *file1, char *file2, t_info *commands);
int		ft_find_flag(char const *s);
char	*ft_create_file_name(void);

/* Split commands */
char	**ft_return_commands(char *s);

/* Clean up */
void	ft_cleanup(char *in_file, t_info *commands);

#endif
