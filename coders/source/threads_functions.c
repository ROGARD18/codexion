/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 21:27:13 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	compiling(int id, int time_to_compile)
{
	printf("%d is compiling\n", id);
	sleep_ms(time_to_compile);
}

void	debugging(int id, int time_to_debug)
{
	printf("%d is debugging\n", id);
	sleep_ms(time_to_debug);
}

void	refactoring(int id, int time_to_refactor)
{
	printf("%d is refactoring\n", id);
	sleep_ms(time_to_refactor);
}

void	*thread_work(void *arg)
{
	t_thread_data	*td;

	td = (t_thread_data *)arg;
	pthread_mutex_lock(td->dongle_mutex);
	printf("%d has taken a dongle\n", td->thread_id);
	compiling(td->thread_id, td->config->time_to_compile);
	debugging(td->thread_id, td->config->time_to_debug);
	refactoring(td->thread_id, td->config->time_to_refactor);
	sleep_ms(td->config->dongle_cooldown);
	pthread_mutex_unlock(td->dongle_mutex);
	return (NULL);
}
