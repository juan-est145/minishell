/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:12:11 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/08 15:31:09 by juestrel         ###   ########.fr       */
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

typedef enum e_unset_flags
{
	NEUTRAL,
	BREAK,
	REPEAT_NODE
}							t_unset_flags;

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

int							redirect_stdout(t_ast *node, t_pipex *str_pipe,
								t_process_cmd type_cmd);
void						dup_fd_arrays(t_process_cmd type_cmd,
								t_pipex *str_pipe, int fd[2]);
int							here_doc(char *limit);
int							here_doc_echo(char limit);
void						ft_echo_hd_normi(bool open, int fd, char delimiter);

// BUILTINGS
pid_t						ft_getpwd(char *text, t_ast *node,
								t_pipex *str_pipe, t_process_cmd type_cmd);
void						pwd_process(char *text, t_ast *node,
								t_pipex *str_pipe, t_process_cmd type_cmd);
void						pwd_null_error(void);
pid_t						ft_echo(char *text, t_ast *node, t_pipex *str_pipe,
								t_process_cmd type_cmd);
bool						ft_echo_normi(char *text, int i, bool open,
								char delimiter);
void						echo_process(char *text, t_ast *node,
								t_pipex *str_pipe, t_process_cmd type_cmd);
pid_t						ft_env(t_lst_env **lst_env, t_ast *node,
								t_pipex *str_pipe, t_process_cmd cmd_type);
void						env_process(t_lst_env **lst_env, t_ast *node,
								t_pipex *str_pipe, t_process_cmd cmd_type);
pid_t						ft_export(char *new, t_lst_env **lst_env,
								t_pipex *str_pipe, t_process_cmd type_cmd);
void						export_process(char *new, t_lst_env **lst_env);
void						export_parent_process(char *new,
								t_lst_env **lst_env);
pid_t						ft_unset(char *text, t_lst_env **lst_env,
								t_process_cmd type_cmd);
void						unset_parent_process(char *text,
								t_lst_env **lst_env);
void						unset_process(char *text, t_lst_env **lst_env);
t_unset_flags				ft_unset_normi2(char **split, t_lst_env *previous,
								t_unset_flags flag, t_lst_env **temp);
t_unset_flags				ft_unset_normi(t_lst_env **temp, t_unset_flags flag,
								t_lst_env *previous);
bool						found_env(char *env, char *env_to_remove);
pid_t						ft_cd(char *text, t_lst_env **lst_env,
								t_process_cmd type_cmd, t_pipex *str_pipes);
void						cd_process(char *text, t_lst_env **lst_env,
								t_pipex *str_pipes);
int							cd_parent_process(char *text, t_lst_env **lst_env,
								t_pipex *str_pipes);
int							cd_too_many_arguments(char **split,
								t_pipex *str_pipes);
int							old_pwd_failure(t_pipex *str_pipes);
int							cd_no_argument(char *old_pwd, char **split,
								t_lst_env **lst_env, t_pipex *str_pipes);
void						cd_process_continue(t_pipex *str_pipes,
								t_lst_env **lst_env, char **split);
pid_t						ft_exit(t_ast **head, t_lst_env *lst_env,
								char *prompt, t_process_cmd type_cmd);
void						exit_process(t_ast **head, t_lst_env *lst_env,
								char *prompt);

void						handle_cd_env(t_lst_env **lst_env,
								char *export_text, char *pwd,
								t_pipex *str_pipes);
void						is_first(char *text, t_lst_env **lst_env);
char						**search_lst_env(char *text, t_lst_env **lst_env);
int							check_array_length(char **array);
int							errors_cd(char *old_pwd, char **dir, char **split,
								char *text);
void						process_cmd_fork_failure(t_lst_env **lst_env,
								t_pipex *str_pipe);
void						update_env(t_lst_env **lst_env, t_pipex *str_pipes,
								char *pwd, char *old_pwd);
#endif