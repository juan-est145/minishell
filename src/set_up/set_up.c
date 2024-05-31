/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:06:54 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/27 16:45:40 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	my_sigemptyset(sigset_t *set);

char	*initial_print(char **env)
{
	int		i;
	char	*prompt;
	char	*color_prompt;

	i = 0;
	prompt = ft_getenv(env, "LOGNAME=");
	prompt = ft_strjoin(prompt, "$ ");
	color_prompt = ft_strjoin(GREEN, prompt);
	free(prompt);
	prompt = ft_strjoin(color_prompt, RESET);
	free(color_prompt);
	while (i++ < 1500)
		printf("\n");
	print_swamp();
	return (prompt);
}

void	prepare_signals(void)
{
	struct sigaction	sa;
	struct sigaction	sa_quit;

	sa.sa_handler = &signal_handler;
	sa_quit.sa_handler = SIG_IGN;
	my_sigemptyset(&sa.sa_mask);
	my_sigemptyset(&sa_quit.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	my_sigemptyset(sigset_t *set)
{
	unsigned long	i;
	unsigned long	set_size;

	i = 0;
	set_size = sizeof(*set) / sizeof(((sigset_t *)0)->__val[0]);
	while (i < set_size)
	{
		set->__val[i] = 0;
		i++;
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	print_swamp(void)
{
	printf("           ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⡶⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⠟⠀⣠⠙⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣴⣶⣦⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡏⣿⠐⡇⢹⡄⠘⣇⠀⠀⠀⠀⠀⢀⡴⢛⣽⠟⢉⠉⠀⣹⢿⡀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⢹⠀⢻⠈⣧⠀⢹⡀⠀⠀⠀⣠⠟⣰⠟⠁⡰⠀⢀⡼⠃⢸⠇⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡜⣇⠘⣇⠘⣧⣼⡷⠤⢤⣴⠃⣰⠏⠀⡼⠁⢀⡞⠁⢠⡟⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣤⣀⣀⠀⣳⠹⣆⢹⣶⠟⠁⠀⠀⣰⠃⣰⠏⠀⣼⠁⢠⡟⢀⣴⠏⠀⠀⣀⣤⡾⠻⣇⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⣯⣽⣿⢿⣷⣿⢿⡇⠀⠀⠀⢀⣯⣤⣟⢀⣼⣧⣤⣾⡶⠟⢁⣠⣴⣿⠟⠋⠀⠀⣿⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣴⣖⠛⠋⢠⠀⣿⢷⣾⡟⠀⠀⠀⢾⣻⣿⡿⠋⣩⠾⠛⠻⠷⠶⢿⣿⣯⣅⠀⠀⠀⢀⣸⡄⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣤⣤⣀⡉⣉⣙⣛⣷⡏⠻⠦⣤⠀⣀⣀⣈⠙⠋⣀⣼⠃⠀⠀⠀⠠⣴⣾⣛⣿⡭⠶⠞⠛⠋⢻⡇⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⣻⣇⠀⢠⣇⣬⡿⠉⠉⠉⠉⠙⣦⣄⡈⠻⠋⠉⠉⠛⠛⠉⠘⣦⣴⣶⡶⣦⣬⣝⣿⣄⠀⠀⠀⠀⠀⣼⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⡾⠛⠁⠀⠈⢉⣛⣛⣛⣯⣥⡤⠤⠤⣤⣤⣄⣸⣧⠉⠙⠓⠒⠲⠶⠖⠒⣿⠋⠁⠈⠛⠛⠿⠿⢯⣅⣀⣀⣀⣤⣴⡟⠀⠀\n");
	printf("⠀⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣿⣿⣿⣖⠒⠒⠚⠛⢻⣻⣿⣿⣿⣶⡖⠒⣞⣾⣷⣶⣾⣿⣷⣶⣶⣶⣒⡒⠒⠚⠛⠒⠒⠒⣶⣶⣶⣶⣤⣬⣽⣿⡅⠀⣼⠃⠀⠀\n");
	printf("⠀⢹⡿⠉⠛⣿⣿⠟⠙⣿⡟⠙⣿⠋⠙⢿⣿⠋⢹⣿⠉⢻⣿⠟⡉⡉⠛⢿⡟⠉⢻⣶⣿⠉⢻⡟⠉⠉⠉⠉⣻⡟⠙⣿⣿⣿⡟⠉⢻⣿⡇⠀⣀⣼⡿⠗⠺⢿⣿⣾⠏⠀⠀⠀\n");
	printf("⠀⢸⡇⠀⠀⢹⡟⠀⠀⣿⡇⠀⣿⠀⢀⠈⢿⠀⢸⣿⠀⢸⣷⡀⠘⠿⠶⣼⡇⠀⠘⠛⠛⠀⢸⡇⠀⠿⠿⠿⣿⡇⠀⣿⣿⣿⡇⠀⢸⣿⣇⣾⠟⣿⣃⡀⢀⣸⣿⡇⠀⠀⠀⠀\n");
	printf("⠀⢸⡇⠀⢤⠀⠁⣰⠀⣿⡇⠀⣿⠀⠘⣧⡀⠀⢸⣿⠀⢸⡟⠛⢷⣶⠄⠈⡇⠀⢸⣿⡟⠀⢸⡇⠀⣶⣶⣶⣿⡇⠀⣿⣿⣿⡇⠀⢸⣿⣿⣿⠀⢹⣏⠀⠈⣹⣿⡇⠀⠀⠀⠀\n");
	printf("⠀⣸⣷⣀⣼⣦⣠⣿⣤⣿⣧⣀⣿⣤⣰⣿⢳⣄⣸⣿⣤⣼⣿⣦⣤⣄⣤⣾⣧⣀⣾⣿⣷⣄⣼⣧⣤⣤⣤⣤⣼⣷⣤⣤⣤⣤⣧⣤⣤⣤⣼⠏⠀⠈⠻⢶⡾⠟⣿⡇⠀⠀⠀⠀\n");
	printf("⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⡄⠀⠀⠀⠀⠀⠀⠘⣿⡄⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       ⠀⠀⠀⢀⣾⠏⣠⠏⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡄⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⠋⡴⠃⠀⢀⣄⠀⠀⠀⠀⠀⠀⠀⠸⣿⡄⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⢡⡞⠀⠀⣰⣿⣿⠀⠀⠀⠀⢤⠀⠀⠀⠹⣿⡀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣮⣁⢀⣼⡟⢹⡟⠀⠀⠀⠀⣾⡆⠀⠀⠀⣿⡇\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠻⠿⠋⠀⢸⣧⣍⣒⣂⣀⣿⢿⣦⣤⣶⡿⠃\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀\n");
}
