/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:45:44 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/29 20:16:38 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

t_prio_q	*init_prio_q(int number_of_coders, t_thread_data *td, char *sheduler)
{
	// (void)number_of_coders;
	t_prio_q	*pq;
	int			i;

	i = 0;
	pq = malloc(sizeof(t_prio_q));
	if (!pq)
		return ((t_prio_q *)NULL);
	pq->queue = malloc(sizeof(int) * number_of_coders);
	pq->td = td;
	pq->size = 0;
	pq->sheduler = sheduler;
	return (pq);
}

int	create_threads(t_threads *threads_obj, t_config *config,
		pthread_mutex_t *mtx, long long time)
{
	int				i;
	pthread_t		monitor;
	pthread_mutex_t	run;
	t_prio_q		*pq;

	threads_obj->number_of_coders = config->number_of_coders;
	threads_obj->threads_list = malloc(sizeof(pthread_t) * config->number_of_coders);
	if (!threads_obj->threads_list)
		return (-1);
	threads_obj->td = malloc(sizeof(t_thread_data) * config->number_of_coders);
	if (!threads_obj->td)
		return (-1);
	pq = init_prio_q(config->number_of_coders, threads_obj->td, config->sheduler);
	init_all_mutex(config->number_of_coders, mtx);
	pthread_mutex_init(&run, NULL);
	i = 0;
	while (i < config->number_of_coders)
	{
		threads_obj->td[i].id = i + 1;
		threads_obj->td[i].compiled_time = 0;
		threads_obj->td[i].time_start = time;
		threads_obj->td[i].config = config;
		threads_obj->td[i].last_compile_start = time;
		threads_obj->td[i].alive = true;
		threads_obj->td[i].conds = threads_obj->conds;
		threads_obj->td[i].pq = pq;
		threads_obj->td[i].print_mtx = threads_obj->print_mtx;
		threads_obj->td[i].queue_mtx = threads_obj->queue_mtx;
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
		pthread_create(&threads_obj->threads_list[i], NULL, thread_work,
			&threads_obj->td[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_work, threads_obj);
	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_join(threads_obj->threads_list[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	destroy_all_mutex(config->number_of_coders, mtx);
	pthread_mutex_destroy(&run);
	return (0);
}

int	main(int ac, char **av)
{
	int				i;
	t_config		*config;
	t_threads		*threads_obj;
	long long		time;
	pthread_mutex_t	*mtx;

	i = -1;
	config = parsing(ac, av);
	threads_obj = malloc(sizeof(t_threads));
	if (!config || !threads_obj)
		return (free_all(config, threads_obj, NULL));
	threads_obj->queue_mtx = malloc (sizeof(pthread_mutex_t));
	threads_obj->print_mtx = malloc (sizeof(pthread_mutex_t));
	if (!threads_obj->queue_mtx || !threads_obj->print_mtx)
		return (free_all(config, threads_obj, NULL));
	pthread_mutex_init(threads_obj->queue_mtx, NULL);
	pthread_mutex_init(threads_obj->print_mtx, NULL);
	threads_obj->conds = malloc(sizeof(pthread_cond_t) * config->number_of_coders);
	if (!threads_obj->conds)
		return (free_all(config, threads_obj, NULL));
	while (i++ < config->number_of_coders - 1)
		pthread_cond_init(&threads_obj->conds[i], NULL);
	time = get_time();
	mtx = malloc(sizeof(pthread_mutex_t) * config->number_of_coders);
	if (!mtx)
		return (free_all(config, threads_obj, mtx));
	if (create_threads(threads_obj, config, mtx, time))
		return (free_all(config, threads_obj, mtx));
	free_all(config, threads_obj, mtx);
	return (0);
}
