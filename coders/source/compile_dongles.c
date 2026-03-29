/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_dongles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/29 16:25:25 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	take_dongles(t_thread_data *td)
{
	long long	time;

	pthread_mutex_lock(&td->queue_mtx);
	enqueue(td->pq, td->id - 1, td->config->number_of_coders, td->config->sheduler);
	while (peek(td->pq) != (td->id - 1) && td->alive)
		pthread_cond_wait(&td->conds[td->id - 1], &td->queue_mtx);
	if (td->config->number_of_coders == 1)
	{
		time = get_time() - td->time_start;
		pthread_mutex_lock(td->dongle_right);
		printf("%lld %d has taken a dongle\n", time, td->id);
	}
	else if (td->id == td->config->number_of_coders)
	{
		pthread_mutex_lock(td->dongle_left);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle \\\n", time, td->id);
		pthread_mutex_lock(td->dongle_right);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle /\n", time, td->id);
	}
	else
	{
		pthread_mutex_lock(td->dongle_right);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle \\\n", time, td->id);
		pthread_mutex_lock(td->dongle_left);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle /\n", time, td->id);
	}
	pthread_mutex_unlock(&td->queue_mtx);
}

void	released_dongles(t_thread_data *td)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&td->queue_mtx);
	if (td->config->number_of_coders == 1)
	{
		pthread_mutex_unlock(td->dongle_right);
		sleep_ms(td->config->dongle_cooldown);
	}
	else
	{
		pthread_mutex_unlock(td->dongle_left);
		sleep_ms(td->config->dongle_cooldown);
		pthread_mutex_unlock(td->dongle_right);
		sleep_ms(td->config->dongle_cooldown);
	}
	dequeue(td->pq, td->config->sheduler);
	while (i++ < td->config->number_of_coders - 1)
		pthread_cond_broadcast(&td->conds[i]);
	pthread_mutex_unlock(&td->queue_mtx);
}

// void	take_dongles(t_thread_data *td)
// {
//     pthread_mutex_lock(&td->queue_mtx);

//     enqueue(pq, td->id - 1, td->number_of_coders);
//     while (peek(pq) != (td->id - 1) && td->alive)
//     {
//         pthread_cond_wait(&obj->conds[td->id - 1], &obj->queue_mtx);
//     }

//     pthread_mutex_lock(td->dongle_left);
//     pthread_mutex_lock(td->dongle_right);

//     pthread_mutex_unlock(&obj->queue_mtx);
// }

// void	released_dongles(t_thread_data *td, t_prio_q *pq, t_threads *obj)
// {
//     pthread_mutex_lock(&obj->queue_mtx);

//     pthread_mutex_unlock(td->dongle_left);
//     pthread_mutex_unlock(td->dongle_right);

//     dequeue(pq);

//     for (int i = 0; i < obj->number_of_coders; i++)
//         pthread_cond_broadcast(&obj->conds[i]);

//     pthread_mutex_unlock(&obj->queue_mtx);
// }
