/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:12:11 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/31 10:20:04 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINGS_H
# define BUILTINGS_H

# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>

// LISTA ENLAZADA DE VARIABLES DE ENTORNO
typedef struct s_lst_env
{
	char					*text;
	char					**env;
	struct s_lst_env		*next;
}							t_lst_env;

typedef struct s_ast		t_ast;
typedef enum e_process_cmd	t_process_cmd;
typedef struct s_pipex		t_pipex;

// ARCHIVE ENV
int							srch_path(char **env, char *search);
char						*ft_getenv(char **env, char *search);
t_lst_env					*init_lst_env(char **env);
char						*ft_fusion_string(char *s1, char *s2);
int							ft_lstsize_ms(t_lst_env *lst);
// ARCHIVE UTILS
void						free_matrix(char **matrix);
void						free_lst_env(t_lst_env *lst);
int							ft_contain(char *text, char search);
void						liberar_memoria(char **matr);
void						rellenar(char *palabra, char const *frase, char c);
void						ft_lstadd_back_ms(t_lst_env **lst, t_lst_env *new);

void						aux(char **matr, char const *s, char c);
int							ntimes(char const *s, char c);
int							ft_lst_contain_change(t_lst_env **lst,
								char *search);
int							ft_lst_contain(t_lst_env **lst, char *search);
t_lst_env					*ft_lstnew_ms(char *content);
char						*get_pwd_cd(t_lst_env *lst_env);
int							ignore_space(char *text, int i);

int							redirect_stdout(t_ast *node, int fd_pipe[2],
								t_process_cmd type_cmd);
int							here_doc(char *limit);

// BUILTINGS
pid_t						ft_getpwd(char *text, t_ast *node, int fd_pipe[2],
								t_process_cmd type_cmd);
void						pwd_process(char *text, t_ast *node, int fd_pipe[2],
								t_process_cmd type_cmd);
pid_t						ft_echo(char *text, t_ast *node, int fd_pipe[2],
								t_process_cmd type_cmd);
bool						ft_echo_normi(char *text, int i, bool open,
								char delimiter);
void						echo_process(char *text, t_ast *node,
								int fd_pipe[2], t_process_cmd type_cmd);
pid_t						ft_env(t_lst_env **lst_env, t_ast *node,
								int fd_pipe[2], t_process_cmd cmd_type);
void						env_process(t_lst_env **lst_env, t_ast *node,
								int fd_pipe[2], t_process_cmd cmd_type);
pid_t						ft_export(char *new, t_lst_env **lst_env,
								t_pipex *str_pipe, t_process_cmd type_cmd);
void						export_process(char *new, t_lst_env **lst_env);
void						export_parent_process(char *new,
								t_lst_env **lst_env);
void 						ft_unset(char *text, t_lst_env **lst_env);
bool						ft_unset_normi(t_lst_env **temp, bool flag,
								t_lst_env *previous);
pid_t						ft_cd(char *text, t_lst_env **lst_env,
								t_process_cmd type_cmd, t_pipex *str_pipes);
void						cd_process(char *text, t_lst_env **lst_env,
								t_pipex *str_pipes);
void						cd_parent_process(char *text, t_lst_env **lst_env,
								t_pipex *str_pipes);
int							cd_no_argument(char *old_pwd, char **split,
								t_lst_env **lst_env, t_pipex *str_pipes);
void						ft_exit(t_ast **head, t_lst_env *lst_env,
								char *prompt);

void						handle_cd_env(t_lst_env **lst_env,
								char *export_text, char *pwd,
								t_pipex *str_pipes);
void						is_first(char *text, t_lst_env **lst_env);
char						**search_lst_env(char *text, t_lst_env **lst_env);
int							check_array_length(char **array);
int							errors_cd(char *old_pwd, char **dir, char **split,
								char *text);
int							errors_cd(char *old_pwd, char **dir, char **split,
								char *text);

#endif