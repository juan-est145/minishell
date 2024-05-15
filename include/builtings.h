/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:17:28 by user42            #+#    #+#             */
/*   Updated: 2024/05/15 17:46:38 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINGS_H
# define BUILTINGS_H

# include <stdbool.h>
# include <stdio.h>

// LISTA ENLAZADA DE VARIABLES DE ENTORNO
typedef struct s_lst_env
{
	char				*text;
	char				**env;
	struct s_lst_env	*next;
}						t_lst_env;

typedef struct s_ast	t_ast;

// ARCHIVE ENV
int						srch_path(char **env, char *search);
char					*ft_getenv(char **env, char *search);
t_lst_env				*init_lst_env(char **env);
char					*ft_fusion_string(char *s1, char *s2);
int						ft_lstsize_ms(t_lst_env *lst);
// ARCHIVE UTILS
void					free_matrix(char **matrix);
void					free_lst_env(t_lst_env *lst);
int						ft_contain(char *text, char search);
void					liberar_memoria(char **matr);
void					rellenar(char *palabra, char const *frase, char c);
void					ft_lstadd_back_ms(t_lst_env **lst, t_lst_env *new);

void					aux(char **matr, char const *s, char c);
int						ntimes(char const *s, char c);
int						ft_lst_contain_change(t_lst_env **lst, char *search);
int						ft_lst_contain(t_lst_env **lst, char *search);
t_lst_env				*ft_lstnew_ms(char *content);	
char					*get_pwd_cd(t_lst_env *lst_env);
int						ignore_space(char *text, int i);

// BUILTINGS
void					ft_getpwd(char *text);
void					ft_echo(char *text, t_ast *node);
void					ft_env(t_lst_env **lst_env, char *text);
void					ft_export(char *new, t_lst_env **lst_env);
void					ft_unset(char *text, t_lst_env **lst_env);
bool					ft_unset_normi(t_lst_env **temp, bool flag,
							t_lst_env *previous);
void					ft_cd(char *text, t_lst_env **lst_env);
void					ft_exit(t_ast **head, t_lst_env *lst_env, char *prompt);

void					handle_cd_env(t_lst_env **lst_env, char *f(char *s1,
								char *s2), char *export_text, char *pwd);
void					is_first(char *text, t_lst_env **lst_env);
char					**search_lst_env(char *text, t_lst_env **lst_env);
int						check_array_length(char **array);
int						errors_cd(char *old_pwd, char **dir, char **split,
							char *text);
int						cd_no_argument(char *old_pwd, char **split,
							t_lst_env **lst_env);

#endif