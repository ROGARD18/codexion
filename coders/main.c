/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:45:44 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 21:47:07 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int	create_threads(t_tools *tools, t_config *config)
{
	int	i;

	tools->threads = malloc(sizeof(pthread_t)
			* config->number_of_coders);
	tools->td = malloc(sizeof(t_thread_data) * config->number_of_coders);
	if (!tools->threads || !tools->td)
		return (-1);
	pthread_mutex_init(&tools->dongle_mutex, NULL);
	i = 0;
	while (i < config->number_of_coders)
	{
		tools->td[i].thread_id = i + 1;
		tools->td[i].config = config;
		tools->td[i].dongle_mutex = &tools->dongle_mutex;
		pthread_create(&tools->threads[i], NULL, thread_work, &tools->td[i]);
		i++;
	}
	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_join(tools->threads[i], NULL);
		i++;
	}
	return (0);
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
	pthread_mutex_init(&tools->dongle_mutex, NULL);
	create_threads(tools, config);
	printf("numbers_of_coders = %d\n", config->number_of_coders);
	free(config);
	free(tools);
	pthread_mutex_destroy(&mtx);
	return (0);
}
