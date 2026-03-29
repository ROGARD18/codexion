/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_dongles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/29 19:48:48 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	take_dongles(t_thread_data *td)
{
	pthread_mutex_lock(td->queue_mtx);
	enqueue(td->pq, td->id - 1, td->config->number_of_coders, td->config->sheduler);
	while (peek(td->pq) != (td->id - 1) && td->alive)
		pthread_cond_wait(&td->conds[td->id - 1], td->queue_mtx);
	pthread_mutex_unlock(td->queue_mtx);
	if (!td->alive)
		return ;
	if (td->config->number_of_coders == 1)
	{
		pthread_mutex_lock(td->dongle_left);
		printf("%lld %d has taken a dongle\n", get_time() - td->time_start, td->id);
		pthread_mutex_unlock(td->dongle_left);
	}
	else if (td->id == td->config->number_of_coders)
	{
		pthread_mutex_lock(td->dongle_left);
		pthread_mutex_lock(td->print_mtx);
		printf("%lld %d has taken a dongle\n", get_time() - td->time_start, td->id);
		pthread_mutex_unlock(td->print_mtx);
		pthread_mutex_lock(td->dongle_right);
		pthread_mutex_lock(td->print_mtx);
		printf("%lld %d has taken a dongle\n", get_time() - td->time_start, td->id);
		pthread_mutex_unlock(td->print_mtx);
	}
	else
	{
		pthread_mutex_lock(td->dongle_right);
		pthread_mutex_lock(td->print_mtx);
		printf("%lld %d has taken a dongle\n", get_time() - td->time_start, td->id);
		pthread_mutex_unlock(td->print_mtx);
		pthread_mutex_lock(td->dongle_left);
		pthread_mutex_lock(td->print_mtx);
		printf("%lld %d has taken a dongle\n", get_time() - td->time_start, td->id);
		pthread_mutex_unlock(td->print_mtx);
	}
}

void	released_dongles(t_thread_data *td)
{
	int i;

	// 1. Libérer les ressources physiques
	pthread_mutex_unlock(td->dongle_left);
	pthread_mutex_unlock(td->dongle_right);

	// 2. Sortir de la file d'attente logicielle
	pthread_mutex_lock(td->queue_mtx);
	dequeue(td->pq, td->config->sheduler);
	
	// Réveiller tout le monde pour que le prochain check son tour
	i = 0;
	while (i < td->config->number_of_coders)
	{
		pthread_cond_broadcast(&td->conds[i]);
		i++;
	}
	pthread_mutex_unlock(td->queue_mtx);

	// 3. Cooldown APRÈS avoir tout libéré
	sleep_ms(td->config->dongle_cooldown, td);
}
