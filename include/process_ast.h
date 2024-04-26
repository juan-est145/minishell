/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:06:11 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/26 12:32:59 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_AST_H
# define PROCESS_AST_H

typedef struct s_ast		t_ast;
typedef struct s_lst_env	t_lst_env;

void						read_cmd(t_ast *node, t_lst_env *lst_env);
#endif
