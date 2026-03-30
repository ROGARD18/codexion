/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_dongles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/30 18:24:46 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	print_dongle(t_thread_data *td)
{
	pthread_mutex_lock(td->print_mtx);
	printf("%lld %d has taken a dongle\n", get_time() - td->time_start, td->id);
	pthread_mutex_unlock(td->print_mtx);
}

void	take_dongles(t_thread_data *td)
{
	pthread_mutex_lock(td->queue_mtx);
	enqueue(td->pq, td->id - 1, td->config->number_of_coders,
		td->config->sheduler);
	while (peek(td->pq) != (td->id - 1) && td->alive)
		pthread_cond_wait(&td->conds[td->id - 1], td->queue_mtx);
	pthread_mutex_unlock(td->queue_mtx);
	if (!td->alive)
		return ;
	if (td->id == td->config->number_of_coders)
	{
		pthread_mutex_lock(td->dongle_left);
		print_dongle(td);
		pthread_mutex_lock(td->dongle_right);
		print_dongle(td);
	}
	else
	{
		pthread_mutex_lock(td->dongle_right);
		print_dongle(td);
		pthread_mutex_lock(td->dongle_left);
		print_dongle(td);
	}
}

void	released_dongles(t_thread_data *td)
{
	int	i;
	pthread_mutex_unlock(td->dongle_left);
	pthread_mutex_unlock(td->dongle_right);
	pthread_mutex_lock(td->queue_mtx);
	dequeue(td->pq, td->config->sheduler);
	i = 0;
	while (i < td->config->number_of_coders)
	{
		pthread_cond_broadcast(&td->conds[i]);
		i++;
	}
	pthread_mutex_unlock(td->queue_mtx);
	sleep_ms(td->config->dongle_cooldown, td);
}
