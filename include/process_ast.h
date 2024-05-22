/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:06:11 by juan-est145       #+#    #+#             */
/*   Updated: 2024/05/22 11:38:51 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_AST_H
# define PROCESS_AST_H

typedef struct s_ast		t_ast;
typedef struct s_lst_env	t_lst_env;

void						read_cmd(t_ast *node, t_pipex *str_pipe, char *prompt);
void						read_pipe(t_ast *node, t_lst_env **lst_env);
#endif
