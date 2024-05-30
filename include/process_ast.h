/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:04 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/30 11:58:14 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_AST_H
# define PROCESS_AST_H

typedef struct s_ast		t_ast;
typedef struct s_lst_env	t_lst_env;

typedef enum e_process_cmd
{
	SIMPLE_CMD,
	ENTRY_PIPE,
	EXIT_PIPE,
}							t_process_cmd;

void						read_cmd(t_ast *node, t_pipex *str_pipe,
								char *prompt);
void						read_pipe(t_ast *node, t_lst_env **lst_env,
								t_pipex *str_pipe, char *prompt);
#endif
