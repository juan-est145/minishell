/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_swamp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:06:54 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/20 10:22:13 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	print_swamp()
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
	printf("⠀⣶⣶⣶⣶⣶⣿⣿⣷⣶⣶⣶⣶⣶⣶⣶⣿⣿⣿⣖⠒⠒⠚⠛⢻⣻⣿⣿⣿⣶⡖⠒⣞⣾⣷⣶⣾⣿⣷⣶⣶⣶⣒⡒⠒⠚⠛⠒⠒⠒⣶⣶⣶⣶⣤⣬⣽⣿⡅⠀⣼⠃⠀⠀\n");
	printf("⠀⢹⡿⠉⠛⣿⣿⠟⠙⣿⡟⠙⣿⠋⠙⢿⣿⠋⢹⣿⠉⢻⣿⠟⢻⡉⠛⢿⡟⠉⢻⣶⣿⠉⢻⡟⢻⣿⣉⠉⣻⡟⠙⡇⠀⠀⡟⠉⢻⡆⡇⠀⣀⣼⡿⠗⠺⢿⣿⣾⠏⠀⠀⠀\n");
	printf("⠀⢸⡇⠀⠀⢹⡟⠀⠀⣿⡇⠀⣿⠀⢀⠈⢿⠀⢸⣿⠀⢸⣷⡀⠘⠿⠶⣼⡇⠀⠘⠛⠛⠀⢸⡇⠀⠿⠿⠿⣿⡇⠀⣇⠀⠀⡇⠀⢸⣇⣇⣾⠟⣿⣃⡀⢀⣸⣿⡇⠀⠀⠀⠀\n");
	printf("⠀⢸⡇⠀⢤⠀⠁⣰⠀⣿⡇⠀⣿⠀⠘⣧⡀⠀⢸⣿⠀⢸⡟⠛⢷⣶⠄⠈⡇⠀⢸⣿⡟⠀⢸⡇⠀⣿⣷⣶⣿⡇⠀⣿⣤⣤⡇⠀⢸⣿⣿⣿⠀⢹⣏⠀⠈⣹⣿⡇⠀⠀⠀⠀\n");
	printf("⠀⣸⣷⣀⣼⣦⣠⣿⣤⣿⣧⣀⣿⣤⣰⡟⢳⣄⣸⣿⣤⣼⣿⣦⣤⣄⣤⣾⣧⣀⣾⣿⣷⣄⣼⣧⣤⣽⣴⣤⣼⣷⣤⣤⣦⣤⣧⣤⣤⣤⣼⠏⠀⠈⠻⢶⡾⠟⣿⡇⠀⠀⠀⠀\n");
	printf("⠀⠻⠿⠿⣿⣿⠿⠿⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠿⠿⣿⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⠿⢿⣿⡿⢿⡄⠀⠀⠀⠀⠀⠀⠘⣿⡄⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠉⠉⠉⠀⠀⠀⢀⣾⠏⣠⠏⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡄⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⠋⡴⠃⠀⢀⣄⠀⠀⠀⠀⠀⠀⠀⠸⣿⡄⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⢡⡞⠀⠀⣰⣿⣿⠀⠀⠀⠀⢤⠀⠀⠀⠹⣿⡀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣮⣁⢀⣼⡟⢹⡟⠀⠀⠀⠀⣾⡆⠀⠀⠀⣿⡇\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠻⠿⠋⠀⢸⣧⣍⣒⣂⣀⣿⢿⣦⣤⣶⡿⠃\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀\n");
}
