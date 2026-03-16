/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:45:44 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 21:14:48 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int    create_threads(t_tools *tools)
{
    int i;

    tools->threads = malloc(sizeof(pthread_t) * tools->config->number_of_coders);
    tools->threads_data = malloc(sizeof(t_thread_data) * tools->config->number_of_coders);
	if (!tools->threads || !tools-> threads_data)
		return (-1);
    pthread_mutex_init(&tools->dongle_mutex, NULL);

    i = 0;
    while (i < tools->config->number_of_coders)
    {
        tools->threads_data[i].thread_id = i + 1;
        tools->threads_data[i].config = tools->config;
        tools->threads_data[i].dongle_mutex = &tools->dongle_mutex;
        pthread_create(&tools->threads[i], NULL, thread_work, &tools->threads_data[i]);
        i++;
    }

    i = 0;
    while (i < tools->config->number_of_coders)
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
	tools->config = config;
	pthread_mutex_init(&tools->dongle_mutex, NULL);
	create_threads(tools);
	printf("numbers_of_coders = %d\n", config->number_of_coders);
	free(config);
	free(tools);
	pthread_mutex_destroy(&mtx);
	return (0);
}
