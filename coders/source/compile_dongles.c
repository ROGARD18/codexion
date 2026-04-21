/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_dongles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/21 01:48:36 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <unistd.h>

void	print_dongle(t_thread_data *td)
{
	if (!td->alive)
		return ;
	pthread_mutex_lock(td->print_mtx);
	if (!td->alive)
	{
		pthread_mutex_unlock(td->print_mtx);
		return ;
	}
	printf("%lld %d has taken a dongle\n", get_time() - td->time_start, td->id);
	printf("%lld %d has taken a dongle\n", get_time() - td->time_start, td->id);
	pthread_mutex_unlock(td->print_mtx);
}

int	take_dongles(t_thread_data *td)
{
	int	next;

	pthread_mutex_lock(td->queue_mtx);
	enqueue(td->pq, td->id - 1, td->config->number_of_coders,
		td->config->sheduler);
	while (peek(td->pq) != (td->id - 1) && td->alive)
		pthread_cond_wait(&td->conds[td->id - 1], td->queue_mtx);
	if (!td->alive)
	{
		pthread_mutex_unlock(td->queue_mtx);
		return (-1);
	}
	dequeue(td->pq, td->config->sheduler);
	next = peek(td->pq);
	if (next != -1)
		pthread_cond_broadcast(&td->conds[next]);
	pthread_mutex_unlock(td->queue_mtx);
	if (td->id % 2 == 0)
	{
		pthread_mutex_lock(td->dongle_right);
		pthread_mutex_lock(td->dongle_left);
	}
	else
	{
		pthread_mutex_lock(td->dongle_left);
		pthread_mutex_lock(td->dongle_right);
	}
	print_dongle(td);
	return (0);
}

void	released_dongles(t_thread_data *td)
{
	pthread_mutex_unlock(td->dongle_left);
	pthread_mutex_unlock(td->dongle_right);
}
