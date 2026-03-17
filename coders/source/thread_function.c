/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogard-antoine <rogard-antoine@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/17 16:51:49 by rogard-anto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	take_dongles(t_thread_data *td)
{
	if (td->config->number_of_coders == 1)
	{
		pthread_mutex_lock(td->dongle_right);
		printf("%d has taken a dongle\n", td->thread_id);
	}
	else if (td->thread_id == td->config->number_of_coders)
	{
		pthread_mutex_lock(td->dongle_left);
		printf("%d has taken a dongle\n", td->thread_id);
		pthread_mutex_lock(td->dongle_right);
		printf("%d has taken a dongle\n", td->thread_id);
	}
	else
	{
		pthread_mutex_lock(td->dongle_right);
		printf("%d has taken a dongle\n", td->thread_id);
		pthread_mutex_lock(td->dongle_left);
		printf("%d has taken a dongle\n", td->thread_id);
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
	compiling(td->thread_id, td->config->time_to_compile);
	released_dongles(td);
	debugging(td->thread_id, td->config->time_to_debug);
	refactoring(td->thread_id, td->config->time_to_refactor);
	return (NULL);
}
