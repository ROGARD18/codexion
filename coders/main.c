/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:45:44 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/23 22:36:07 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int	create_threads(t_threads *threads_obj, t_config *config, pthread_mutex_t *mtx, long long time)
{
	int			i;
	pthread_t	monitor;
	pthread_mutex_t	run;

	threads_obj->number_of_coders = config->number_of_coders;
	threads_obj->threads = malloc(sizeof(pthread_t) * config->number_of_coders);
	if (!threads_obj->threads)
		return (-1);
	threads_obj->td = malloc(sizeof(t_thread_data) * config->number_of_coders);
	if (!threads_obj->td)
		return (-1);
	init_all_mutex(config->number_of_coders, mtx);
	pthread_mutex_init(&run, NULL);
	i = 0;
	while (i < config->number_of_coders)
	{
		threads_obj->td[i].id = i + 1;
		threads_obj->td[i].config = config;
		threads_obj->td[i].compiled_time = 0;
		threads_obj->td[i].last_compile_start = 0;
		threads_obj->td[i].time_start = time;
		threads_obj->td[i].alive = true;
		if (config->number_of_coders == 1)
		{
			threads_obj->td[i].dongle_left = NULL;
			threads_obj->td[i].dongle_right = &mtx[i];
		}
		if (i == 0)
			threads_obj->td[i].dongle_left = &mtx[config->number_of_coders - 1];
		else
			threads_obj->td[i].dongle_left = &mtx[i - 1];
		threads_obj->td[i].dongle_right = &mtx[i % config->number_of_coders];
		pthread_create(&threads_obj->threads[i], NULL, thread_work, &threads_obj->td[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_work, threads_obj);
	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_join(threads_obj->threads[i], NULL);
		i++;
	}
	destroy_all_mutex(config->number_of_coders, mtx);
	pthread_mutex_destroy(&run);
	return (0);
}

int	main(int ac, char **av)
{
	t_config		*config;
	t_threads		*threads;
	long long		time;
	pthread_mutex_t	*mtx;

	config = parsing(ac, av);
	time = get_time();
	threads = malloc(sizeof(t_threads));
	if (!config || !threads)
		return (free_all(config, threads, NULL));
	mtx = malloc(sizeof(pthread_mutex_t) * config->number_of_coders);
	if (!mtx)
		return (free_all(config, threads, mtx));
	if (create_threads(threads, config, mtx, time))
		return (free_all(config, threads, mtx));
	printf("numbers_of_coders = %d\n", config->number_of_coders);
	free_all(config, threads, mtx);
	return (0);
}
