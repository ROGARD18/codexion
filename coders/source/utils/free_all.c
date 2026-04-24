/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:05:23 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/04/24 20:34:48 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

void	free_all_helper(t_threads *threads_obj)
{
	int	i;

	i = 0;
	if (threads_obj->print_mtx)
	{
		pthread_mutex_destroy(threads_obj->print_mtx);
		free(threads_obj->print_mtx);
	}
	if (threads_obj->queue_mtx)
	{
		pthread_mutex_destroy(threads_obj->queue_mtx);
		free(threads_obj->queue_mtx);
	}
	if (threads_obj->conds)
	{
		while (i < threads_obj->number_of_coders)
			pthread_cond_destroy(&threads_obj->conds[i++]);
		free(threads_obj->conds);
	}
}

int	free_all(t_config *config, t_threads *threads_obj, pthread_mutex_t *mtx)
{
	int	i;
	int	nb;

	nb = config->number_of_coders;
	i = 0;
	if (config)
		free(config);
	if (mtx)
		free(mtx);
	if (!threads_obj)
		return (-1);
	free_all_helper(threads_obj);
	if (threads_obj->pq)
	{
		if (threads_obj->pq->queue)
			free(threads_obj->pq->queue);
		if (threads_obj->pq->enqueue_order)
			free(threads_obj->pq->enqueue_order);
		free(threads_obj->pq);
	}
	if (threads_obj->threads_list)
		free(threads_obj->threads_list);
	if (threads_obj->td)
		free(threads_obj->td);
	if (threads_obj->dgl_mtxs)
	{
		while (i < nb)
			pthread_mutex_destroy(&threads_obj->dgl_mtxs[i++]);
		free(threads_obj->dgl_mtxs);
	}
	i = 0;
	if (threads_obj->dgl_conds)
	{
		while (i < nb)
			pthread_cond_destroy(&threads_obj->dgl_conds[i++]);
		free(threads_obj->dgl_conds);
	}
	if (threads_obj->dgl_availables)
		free(threads_obj->dgl_availables);
	if (threads_obj->state_mtx)
	{
		while (i < nb)
			pthread_mutex_destroy(&threads_obj->state_mtx[i++]);
		free(threads_obj->state_mtx);
	}
	free(threads_obj);
	return (-1);
}
