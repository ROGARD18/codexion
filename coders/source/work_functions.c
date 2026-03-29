/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:51:40 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/03/29 21:06:13 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

void	compiling(int id, t_thread_data *td)
{
	long long	time;

	time = get_time();
	td->last_compile_start = time;
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
	sleep_ms(td->config->time_to_refactor, td);
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
		return (NULL);
	}
	while (i++ < td->config->number_of_compiles_requiered - 1)
	{
		if (td->alive == 0)
			return (NULL);
		take_dongles(td);
		if (td->alive == 0)
			return (NULL);
		compiling(td->id, td);
		if (td->alive == 0)
			return (NULL);
		td->compiled_time += 1;
		released_dongles(td);
		if (!td->alive)
			return (NULL);
		debugging(td->id, td);
		if (!td->alive)
			return (NULL);
		refactoring(td->id, td);
	}
	td->alive = 0;
	printf("FINI\n");
	return (NULL);
}
