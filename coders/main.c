/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:45:44 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/31 16:25:34 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

void	create_helper(t_threads *threads_obj, pthread_mutex_t *dongles_mtx, int i,
		t_config *config)
{
	threads_obj->td[i] = init_td(config, threads_obj, threads_obj->time, i);
	if (config->number_of_coders == 1)
	{
		threads_obj->td[i].dongle_left = NULL;
		threads_obj->td[i].dongle_right = &dongles_mtx[i];
	}
	else
	{
		if (i == 0)
			threads_obj->td[i].dongle_left = &dongles_mtx[config->number_of_coders - 1];
		else
			threads_obj->td[i].dongle_left = &dongles_mtx[i - 1];
		threads_obj->td[i].dongle_right = &dongles_mtx[i];
	}
	pthread_create(&threads_obj->threads_list[i], NULL, thread_work,
		&threads_obj->td[i]);
	i++;
}

int	create_threads(t_threads *threads_obj, t_config *config,
		pthread_mutex_t *dongles_mtx)
{
	int			i;
	pthread_t	monitor;

	threads_obj->number_of_coders = config->number_of_coders;
	threads_obj->threads_list = malloc(sizeof(pthread_t)
			* config->number_of_coders);
	if (!threads_obj->threads_list)
		return (-1);
	i = 0;
	while (i < config->number_of_coders)
	{
		create_helper(threads_obj, dongles_mtx, i, config);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_work, threads_obj);
	i = 0;
	while (i < config->number_of_coders)
		pthread_join(threads_obj->threads_list[i++], NULL);
	pthread_join(monitor, NULL);
	destroy_all_mutex(config->number_of_coders, dongles_mtx);
	return (0);
}

int	main(int ac, char **av)
{
	int				i;
	t_config		*config;
	t_threads		*threads_obj;
	pthread_mutex_t	*dongles_mtx;

	i = -1;
	config = parsing(ac, av);
	if (!config)
		return (free_all(config, NULL, NULL));
	dongles_mtx = malloc(sizeof(pthread_mutex_t) * config->number_of_coders);
	if (!dongles_mtx)
		return (free_all(config, NULL, dongles_mtx));
	pthread_mutex_init(dongles_mtx, NULL);
	init_all_mutex(config->number_of_coders, dongles_mtx);
	threads_obj = init_threads_obj(config, get_time(), dongles_mtx);
	if (!threads_obj)
		return (free_all(config, threads_obj, NULL));
	threads_obj->pq = init_prio_q(config->number_of_coders, threads_obj->td,
			config->sheduler);
	if (!threads_obj->pq)
		return (free_all(config, threads_obj, NULL));
	while (i++ < config->number_of_coders - 1)
		pthread_cond_init(&threads_obj->conds[i], NULL);
	if (create_threads(threads_obj, config, dongles_mtx))
		return (free_all(config, threads_obj, dongles_mtx));
	free_all(config, threads_obj, dongles_mtx);
	return (0);
}
