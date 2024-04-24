/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:17:28 by user42            #+#    #+#             */
/*   Updated: 2024/04/24 15:24:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRUEBA_H
# define PRUEBA_H

#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdbool.h>

//LISTA ENLAZADA DE VARIABLES DE ENTORNO
typedef struct s_lst_env
{
	char				*text;//TEXTO DE ESA FILA DE LA VARIABLE DE ENTORNO
	struct s_lst_env	*next;//SIGUIENTE VARIABLE DE ENTORNO
}	t_lst_env;//APODO


//ARCHIVE ENV
int	srch_path(char **env, char *search);
char *ft_getenv(char **env, char *search);
void init_lst_env(char **env, t_lst_env *lst);
char *ft_fusion_string(char *s1, char *s2);
//ARCHIVE UTILS 1
void free_matrix(char **matrix);
void free_lst_env (t_lst_env *lst);
int ft_strlen(const char *s);
int ft_contain(char *text, char search);
void	ft_lstadd_back(t_lst_env **lst, t_lst_env *new);
void	liberar_memoria(char **matr);
void	rellenar(char *palabra, char const *frase, char c);
void	aux(char **matr, char const *s, char c);
int	ntimes(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_lst_contain_change(t_lst_env **lst, char *search);
int ft_lst_contain(t_lst_env **lst, char *search);
t_lst_env	*ft_lstnew_ms(char *content);
//BUILTINGS
void ft_getpwd(char *text, t_lst_env *lst_env);
void ft_echo(char **cmd);
void ft_env(t_lst_env *lst_env, char *text);
void ft_export(char *new, t_lst_env *lst_env);
bool ft_unset_normi(t_lst_env *temp, bool flag);
void ft_unset(char *text, t_lst_env *lst_env);
void ft_cd(char *text, t_lst_env *lst_env);

#endif