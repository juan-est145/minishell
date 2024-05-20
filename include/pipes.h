/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:44:54 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/13 17:28:01 by mfuente-         ###   ########.fr       */
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
	int		cant_cmd;		// CANTIDAD DE COMANDOS
	char	***comands;	// ARRAY TRIDIMENSIONAL PARA GUARDAR TODOS LOS COMANDOS
	char	**path_seg;	// VARIABLE DE ENTORNO, SEGMENTADA
}	t_pipex;				// APODO

// ARCHIVE_UTILS_CMD
void	up_env(t_lst_env **lst_env);
char	*create_path(t_pipex *str_pipes, char **comand, int i);
void	free_copie_env(t_lst_env **lst);

#endif