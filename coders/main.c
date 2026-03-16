/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:45:44 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 19:03:13 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

void	create_threads(int number_of_coders, void *(*thread_work)(void *),
	t_tools *tools)
{
	int			i;
	pthread_t	thread_list[number_of_coders - 1];

	i = 0;
	while (number_of_coders--)
	{
		tools->thread_id = i + 1;
		pthread_create(&thread_list[i++], NULL, thread_work, tools);
	}
	i = 0;
	while (i < number_of_coders - 1)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_config		*config;
	t_tools			*tools;
	pthread_mutex_t	mtx;

	config = parsing(ac, av);
	if (!config)
		return (-1);
	tools = malloc(sizeof(t_tools));
	tools->mutex = &mtx;
	tools->config = config;
	pthread_mutex_init(&mtx, NULL);
	create_threads(config->number_of_coders, &thread_work, tools);
	printf("numbers_of_coders = %d\n", config->number_of_coders);
	free(config);
	free(tools);
	pthread_mutex_destroy(&mtx);
	return (0);
}
