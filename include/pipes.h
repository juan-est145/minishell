/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:44:54 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/22 09:55:56 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

// PARA FACILITAR LA LECTURA DEL CODIGO
# define READ 0
# define WRITE 1

# define CHILD 0
# define FATHER 1

typedef struct s_pipex
{
	char			**path_seg;	// VARIABLE DE ENTORNO, SEGMENTADA
	int				fd[2];		// FD DE LA FUNCION PIPE
	t_ast			*ast_head;
	t_lst_env		**lst_env;
}	t_pipex;					// APODO

// ARCHIVE_UTILS_CMD
void	up_env(t_lst_env **lst_env);
char	*create_path(t_pipex *str_pipes, char **comand, int i);
void	free_copie_env(t_lst_env **lst);

#endif