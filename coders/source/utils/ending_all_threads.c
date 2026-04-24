/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_all_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 21:25:17 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 21:39:23 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	ending_all_threads(t_threads *threads_obj)
{
	int	i;

	if (!threads_obj)
		return ;
	if (threads_obj->state_mtx && threads_obj->td)
	{
		i = 0;
		while (i < threads_obj->number_of_coders)
		{
			pthread_mutex_lock(&threads_obj->state_mtx[i]);
			threads_obj->td[i].alive = false;
			pthread_mutex_unlock(&threads_obj->state_mtx[i++]);
		}
	}
	if (threads_obj->queue_mtx && threads_obj->conds)
	{
		pthread_mutex_lock(threads_obj->queue_mtx);
		i = 0;
		while (i < threads_obj->number_of_coders)
			pthread_cond_broadcast(&threads_obj->conds[i++]);
		pthread_mutex_unlock(threads_obj->queue_mtx);
	}
}
