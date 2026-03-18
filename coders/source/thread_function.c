/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/18 16:37:17 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	take_dongles(t_thread_data *td)
{
	if (td->config->number_of_coders == 1)
	{
		pthread_mutex_lock(td->dongle_right);
		printf("%d has taken a dongle\n", td->id);
	}
	else if (td->id == td->config->number_of_coders)
	{
		pthread_mutex_lock(td->dongle_left);
		printf("%d has taken a dongle\n", td->id);
		pthread_mutex_lock(td->dongle_right);
		printf("%d has taken a dongle\n", td->id);
	}
	else
	{
		pthread_mutex_lock(td->dongle_right);
		printf("%d has taken a dongle\n", td->id);
		pthread_mutex_lock(td->dongle_left);
		printf("%d has taken a dongle\n", td->id);
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
	long			seconds;
	long			microseconds;

	td = (t_thread_data *)arg;
	gettimeofday(&td->start, NULL);
	take_dongles(td);
	compiling(td->id, td);
	released_dongles(td);
	gettimeofday(&td->end, NULL);
	seconds = td->end.tv_sec - td->start.tv_sec;
	microseconds = td->end.tv_usec - td->start.tv_usec;
	if (microseconds < 0) {
        seconds -= 1;
        microseconds += 1000000;
    }
	printf("(%d) a écoulé : %ld secondes et %ld microsecondes\n", td->id,
		seconds, microseconds);
	debugging(td->id, td);
	refactoring(td->id, td);
	return (NULL);
}
