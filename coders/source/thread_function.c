/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/19 16:52:14 by anrogard         ###   ########.fr       */
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
	struct timeval	start;
	struct timeval	end;
	long			seconds;
	long			microseconds;
	int index = 0;

	td = (t_thread_data *)arg;
	while (td->config->number_of_compiles_requiered > 0)
	{
		printf("%d compiles ----------------> %d\n", td->id,td->config->number_of_compiles_requiered);
		index++;
		td->compiled_time += 1;
		if (td->last_compile_start.tv_sec == 0)
			gettimeofday(&td->last_compile_start, NULL);
		gettimeofday(&start, NULL);
		seconds = start.tv_sec - td->last_compile_start.tv_sec;
		microseconds = start.tv_usec - td->last_compile_start.tv_usec;
		// printf("waiting time microseconds: %ld\n", seconds * 1000000 + microseconds);
		if (seconds * 1000 + microseconds / 1000 > td->config->time_to_burnout)
		{
			td->burnout = 1;
			printf("%d BURRRNNNN OUTT\n", td->id);
			return (NULL);
		}
		take_dongles(td);
		compiling(td->id, td);
		released_dongles(td);
		gettimeofday(&end, NULL);
		td->last_compile_start = start;
		// seconds = end.tv_sec - start.tv_sec;
		// microseconds = end.tv_usec - start.tv_usec;
		// if (microseconds < 0)
		// {
		// 	seconds -= 1;
		// 	microseconds += 1000000;
		// }
		// printf("(%d) a écoulé : %ld secondes et %ld microsecondes\n", td->id, 	
		// 	seconds, microseconds);
		debugging(td->id, td);
		refactoring(td->id, td);
		td->config->number_of_compiles_requiered -= 1;
	}
	printf("Compiled %d time\n", index);
	return (NULL);
}
