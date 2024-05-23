/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:04 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/23 13:14:05 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_AST_H
# define PROCESS_AST_H

typedef struct s_ast		t_ast;
typedef struct s_lst_env	t_lst_env;

void						read_cmd(t_ast *node, t_pipex *str_pipe,
								char *prompt);
void						read_pipe(t_ast *node, t_lst_env **lst_env,
								t_pipex *str_pipe);
#endif
