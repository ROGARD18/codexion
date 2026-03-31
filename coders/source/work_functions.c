/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:51:40 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/03/31 16:38:51 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	compiling(int id, t_thread_data *td)
{
	long long	time;

	time = get_time();
	td->last_cmp_start = time;
	pthread_mutex_lock(td->print_mtx);
	printf("%lld %d is compiling\n", time - td->time_start, id);
	pthread_mutex_unlock(td->print_mtx);
	sleep_ms(td->config->time_to_compile, td);
}

void	debugging(int id, t_thread_data *td)
{
	pthread_mutex_lock(td->print_mtx);
	printf("%lld %d is debugging\n", get_time() - td->time_start, id);
	pthread_mutex_unlock(td->print_mtx);
	sleep_ms(td->config->time_to_debug, td);
}

void	refactoring(int id, t_thread_data *td)
{
	pthread_mutex_lock(td->print_mtx);
	printf("%lld %d is refactoring\n", get_time() - td->time_start, id);
	pthread_mutex_unlock(td->print_mtx);
	usleep(td->config->time_to_refactor);
}

int	do_work(t_thread_data *td)
{
	if (td->alive == 0)
		return (-1);
	// printf("%d wait for dongles\n", td->id);
	if (take_dongles(td) == -1)
	{
		printf("OUI\n");
		return (-1);
	}
	// printf("%d OK for dongles\n", td->id);
	// if (td->alive == 0)
	// {
	// 	released_dongles(td);
	// 	return (-1);
	// }
	compiling(td->id, td);
	if (td->alive == 0)
		return (-1);
	td->compiled_time += 1;
	released_dongles(td);
	if (td->alive == 0)
		return (-1);
	debugging(td->id, td);
	if (td->alive == 0)
		return (-1);
	refactoring(td->id, td);
	return (0);
}

void	*thread_work(void *arg)
{
	t_thread_data	*td;
	int				i;

	i = -1;
	td = (t_thread_data *)arg;
	if (!td->dongle_left)
	{
		printf("There is only one dongle on the table.");
		td->alive = 0;
		return (NULL);
	}
	while (i < td->config->number_of_compiles_requiered - 1)
	{
		if (do_work(td) == -1)
		{
			printf("OUI pour %d\n", td->id);
			return (NULL);
		}
		i++;
	}
	td->alive = 0;
	return (NULL);
}
