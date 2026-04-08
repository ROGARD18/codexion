/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 21:14:26 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/08 16:52:41 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <stdlib.h>

t_thread_data	init_td(t_config *config, t_threads *threads_obj,
		long long time, int i)
{
	t_thread_data	td;

	td.id = i + 1;
	td.compiled_time = 0;
	td.time_start = time;
	td.config = config;
	td.last_cmp_start = time;
	td.alive = true;
	td.conds = threads_obj->conds;
	td.pq = threads_obj->pq;
	td.print_mtx = threads_obj->print_mtx;
	td.queue_mtx = threads_obj->queue_mtx;
	return (td);
}

t_prio_q	*init_prio_q(int number_of_coders, t_thread_data *td,
		char *sheduler)
{
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
	pq->enqueue_order = malloc(sizeof(int) * number_of_coders);
	if (!pq->enqueue_order)
		return (NULL);
	pq->seq_counter = 0;
	return (pq);
}

t_threads	*init_threads_obj(t_config *config, long long time,
		pthread_mutex_t *dongles_mtx)
{
	t_threads	*threads_obj;

	threads_obj = malloc(sizeof(t_threads));
	if (!threads_obj)
		return (NULL);
	threads_obj->pq = NULL;
	threads_obj->td = ft_calloc(sizeof(t_thread_data),
			config->number_of_coders);
	threads_obj->threads_list = NULL;
	threads_obj->queue_mtx = malloc(sizeof(pthread_mutex_t));
	threads_obj->print_mtx = malloc(sizeof(pthread_mutex_t));
	if (!threads_obj->queue_mtx || !threads_obj->print_mtx)
		return (NULL);
	pthread_mutex_init(threads_obj->queue_mtx, NULL);
	pthread_mutex_init(threads_obj->print_mtx, NULL);
	threads_obj->conds = malloc(sizeof(pthread_cond_t)
			* config->number_of_coders);
	if (!threads_obj->conds)
		return (NULL);
	threads_obj->time = time;
	threads_obj->dongles_mtx = dongles_mtx;
	return (threads_obj);
}
