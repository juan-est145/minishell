/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:44:54 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/30 19:01:25 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

// PARA FACILITAR LA LECTURA DEL CODIGO ||||| hacer ifdefine etc
# define READ 0
# define WRITE 1

# define CHILD 0
# define FATHER 1

typedef struct s_pipex
{
	char		**path_seg;
	int			fd[2];
	t_ast		*ast_head;
	t_lst_env	**lst_env;
}				t_pipex;
// ARCHIVE_UTILS_CMD
void			up_env(t_lst_env **lst_env);
char			*create_path(t_pipex *str_pipes, char **comand, int i);
void			free_copie_env(t_lst_env **lst);

// ARCHIVE_UTILS_CMD1
void			print_pipes(int fd[2]);

#endif