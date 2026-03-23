/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/23 19:32:48 by anrogard         ###   ########.fr       */
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
	int				index;

	index = 0;
	td = (t_thread_data *)arg;
	while (td->config->number_of_compiles_requiered > 0)
	{
		if (!td->alive)
		{
			printf("\nKILL THREAD n* %d\n\n", td->id);
			return NULL;
		}
		index++;
		td->compiled_time += 1;
		take_dongles(td);
		printf("%d compiles restantes ----------------> %d\n", td->id,
			td->config->number_of_compiles_requiered);
		compiling(td->id, td);
		released_dongles(td);
		debugging(td->id, td);
		refactoring(td->id, td);
		td->config->number_of_compiles_requiered -= 1;
	}
	printf("Compiled %d time\n", index);
	return (NULL);
}
