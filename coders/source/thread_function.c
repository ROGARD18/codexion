/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/26 19:04:44 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	take_dongles(t_thread_data *td)
{
	long long time;

	if (td->config->number_of_coders == 1)
	{
		time = get_time() - td->time_start;
		pthread_mutex_lock(td->dongle_right);
		printf("%lld %d has taken a dongle\n",time, td->id);
	}
	else if (td->id == td->config->number_of_coders)
	{
		pthread_mutex_lock(td->dongle_left);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle\n",time, td->id);
		pthread_mutex_lock(td->dongle_right);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle\n",time, td->id);
	}
	else
	{
		pthread_mutex_lock(td->dongle_right);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle\n",time, td->id);
		pthread_mutex_lock(td->dongle_left);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle\n",time, td->id);
	}
}

void	released_dongles(t_thread_data *td)
{
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
}

void	*thread_work(void *arg)
{
	t_thread_data	*td;

	td = (t_thread_data *)arg;
	take_dongles(td);
	compiling(td->id, td);
	td->compiled_time += 1;
	released_dongles(td);
	debugging(td->id, td);
	refactoring(td->id, td);
	return (NULL);
}
