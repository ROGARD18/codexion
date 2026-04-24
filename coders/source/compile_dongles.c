/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_dongles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:43:09 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 20:32:35 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	lock_dongle_left(t_thread_data *td)
{
	struct timespec	target;

	pthread_mutex_lock(td->dongle_left);
	pthread_mutex_lock(td->dgl_mtx_left);
	while (get_time() < *(td->dgl_avail_left))
	{
		target = get_interval();
		pthread_cond_timedwait(td->dgl_cond_left, td->dgl_mtx_left, &target);
	}
	pthread_mutex_unlock(td->dgl_mtx_left);
}

static void	lock_dongle_right(t_thread_data *td)
{
	struct timespec	target;

	pthread_mutex_lock(td->dongle_right);
	pthread_mutex_lock(td->dgl_mtx_right);
	while (get_time() < *(td->dgl_avail_right))
	{
		target = get_interval();
		pthread_cond_timedwait(td->dgl_cond_right, td->dgl_mtx_right, &target);
	}
	pthread_mutex_unlock(td->dgl_mtx_right);
}

static void	print_dongle(t_thread_data *td)
{
	pthread_mutex_lock(td->print_mtx);
	if (is_alive(td))
	{
		printf("%lld %d has taken a dongle\n", get_time() - td->time_start,
			td->id);
		printf("%lld %d has taken a dongle\n", get_time() - td->time_start,
			td->id);
	}
	pthread_mutex_unlock(td->print_mtx);
}

int	take_dongles(t_thread_data *td)
{
	int	next;

	pthread_mutex_lock(td->queue_mtx);
	enqueue(td->pq, td->id - 1, td->config->number_of_coders,
		td->config->sheduler);
	while (peek(td->pq) != (td->id - 1) && is_alive(td))
		pthread_cond_wait(&td->conds[td->id - 1], td->queue_mtx);
	if (!is_alive(td))
		return (pthread_mutex_unlock(td->queue_mtx), -1);
	dequeue(td->pq, td->config->sheduler);
	next = peek(td->pq);
	if (next != -1)
		pthread_cond_broadcast(&td->conds[next]);
	pthread_mutex_unlock(td->queue_mtx);
	if (td->id % 2 == 0)
	{
		lock_dongle_left(td);
		lock_dongle_right(td);
	}
	else
	{
		lock_dongle_right(td);
		lock_dongle_left(td);
	}
	print_dongle(td);
	return (0);
}

void	released_dongles(t_thread_data *td)
{
	long long end_time;

	end_time = get_time() + td->config->dongle_cooldown;
	pthread_mutex_lock(td->dgl_mtx_left);
	*(td->dgl_avail_left) = end_time;
	pthread_mutex_unlock(td->dgl_mtx_left);
	pthread_mutex_lock(td->dgl_mtx_right);
	*(td->dgl_avail_right) = end_time;
	pthread_mutex_unlock(td->dgl_mtx_right);
	pthread_mutex_unlock(td->dongle_left);
	pthread_mutex_unlock(td->dongle_right);
}