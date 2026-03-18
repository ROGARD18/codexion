/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:45:44 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/18 16:51:07 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int	create_threads(t_threads *threads, t_config *config, pthread_mutex_t *mtx)
{
	int			i;
	pthread_t	monitor;

	threads->threads = malloc(sizeof(pthread_t) * config->number_of_coders);
	if (!threads->threads)
		return (-1);
	threads->td = malloc(sizeof(t_thread_data) * config->number_of_coders);
	if (!threads->td)
		return (-1);
	init_all_mutex(config->number_of_coders, mtx);
	threads->td->monitor = &monitor;
	i = 0;
	while (i < config->number_of_coders)
	{
		threads->td[i].id = i + 1;
		threads->td[i].config = config;
		if (config->number_of_coders == 1)
		{
			threads->td[i].dongle_left = NULL;
			threads->td[i].dongle_right = &mtx[i];
		}
		if (i == 0)
			threads->td[i].dongle_left = &mtx[config->number_of_coders - 1];
		else
			threads->td[i].dongle_left = &mtx[i - 1];
		threads->td[i].dongle_right = &mtx[i % config->number_of_coders];
		pthread_create(&threads->threads[i], NULL, thread_work, &threads->td[i]);
		i++;
	}
	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_join(threads->threads[i], NULL);
		i++;
	}
	destroy_all_mutex(config->number_of_coders, mtx);
	return (0);
}

int	main(int ac, char **av)
{
	t_config		*config;
	t_threads		*threads;
	pthread_mutex_t	*mtx;

	config = parsing(ac, av);
	threads = malloc(sizeof(t_threads));
	if (!config || !threads)
		return (free_all(config, threads, NULL));
	mtx = malloc(sizeof(pthread_mutex_t) * config->number_of_coders);
	if (!mtx)
		return (free_all(config, threads, mtx));
	if (create_threads(threads, config, mtx))
		return (free_all(config, threads, mtx));
	printf("numbers_of_coders = %d\n", config->number_of_coders);
	free_all(config, threads, mtx);
	return (0);
}
