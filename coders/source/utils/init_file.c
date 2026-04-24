/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:42:52 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 21:40:13 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_prio_q	*init_prio_q(int number_of_coders, t_thread_data *td,
		char *sheduler)
{
	t_prio_q	*pq;

	pq = malloc(sizeof(t_prio_q));
	if (!pq)
		return (NULL);
	pq->td = td;
	pq->size = 0;
	pq->sheduler = sheduler;
	pq->queue = malloc(sizeof(int) * number_of_coders);
	pq->enqueue_order = malloc(sizeof(int) * number_of_coders);
	if (!pq->queue || !pq->enqueue_order)
		return (NULL);
	pq->seq_counter = 0;
	return (pq);
}

t_thread_data	*init_td(t_config *config, t_threads *obj, long long time,
		int i)
{
	t_thread_data	*td;
	int				next;

	td = ft_calloc(1, sizeof(t_thread_data));
	if (!td)
		return (NULL);
	next = (i + 1) % config->number_of_coders;
	td->id = i + 1;
	td->time_start = time;
	td->config = config;
	td->last_cmp_start = time;
	td->alive = true;
	td->conds = obj->conds;
	td->pq = obj->pq;
	td->print_mtx = obj->print_mtx;
	td->queue_mtx = obj->queue_mtx;
	td->dgl_avail_left = &obj->dgl_availables[i];
	td->dgl_mtx_left = &obj->dgl_mtxs[i];
	td->dgl_cond_left = &obj->dgl_conds[i];
	td->dgl_avail_right = &obj->dgl_availables[next];
	td->dgl_mtx_right = &obj->dgl_mtxs[next];
	td->dgl_cond_right = &obj->dgl_conds[next];
	td->state_mtx = &obj->state_mtx[i];
	return (td);
}

t_threads	*init_threads_obj(t_config *config, long long time,
		pthread_mutex_t *d_mtx)
{
	t_threads	*obj;
	int			i;

	obj = ft_calloc(1, sizeof(t_threads));
	if (!obj)
		return (NULL);
	obj->state_mtx = malloc(sizeof(pthread_mutex_t) * config->number_of_coders);
	obj->print_mtx = malloc(sizeof(pthread_mutex_t));
	obj->queue_mtx = malloc(sizeof(pthread_mutex_t));
	obj->conds = malloc(sizeof(pthread_cond_t) * config->number_of_coders);
	obj->dgl_availables = ft_calloc(config->number_of_coders,
			sizeof(long long));
	obj->dgl_mtxs = malloc(sizeof(pthread_mutex_t) * config->number_of_coders);
	obj->dgl_conds = malloc(sizeof(pthread_cond_t) * config->number_of_coders);
	if (!obj->state_mtx || !obj->print_mtx || !obj->queue_mtx || !obj->conds
		|| !obj->dgl_availables || !obj->dgl_mtxs || !obj->dgl_conds)
		return (NULL);
	if (pthread_mutex_init(obj->print_mtx, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(obj->queue_mtx, NULL) != 0)
		return (NULL);
	i = 0;
	while (i < config->number_of_coders)
	{
		if (pthread_mutex_init(&obj->dgl_mtxs[i], NULL) != 0)
			return (NULL);
		if (pthread_mutex_init(&obj->state_mtx[i], NULL) != 0)
			return (NULL);
		if (pthread_cond_init(&obj->dgl_conds[i], NULL) != 0)
			return (NULL);
		i++;
	}
	obj->dongles_mtx = d_mtx;
	obj->time = time;
	return (obj);
}
