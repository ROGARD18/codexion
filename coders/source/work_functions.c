/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:51:40 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/04/21 00:54:43 by anrogard         ###   ########.fr       */
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
	if (!td->alive)
	{
		pthread_mutex_unlock(td->dongle_right);
		pthread_mutex_unlock(td->dongle_left);
		return ;
	}
	pthread_mutex_lock(td->print_mtx);
	printf("%lld %d is compiling\n", time - td->time_start, id);
	pthread_mutex_unlock(td->print_mtx);
	td->last_cmp_start = get_time();
	usleep(td->config->time_to_compile * 1000);
}

void	debugging(int id, t_thread_data *td)
{
	if (!td->alive)
		return ;
	pthread_mutex_lock(td->print_mtx);
	printf("%lld %d is debugging\n", get_time() - td->time_start, id);
	pthread_mutex_unlock(td->print_mtx);
	usleep(td->config->time_to_debug * 1000);
}

void	refactoring(int id, t_thread_data *td)
{
	if (!td->alive)
		return ;
	pthread_mutex_lock(td->print_mtx);
	printf("%lld %d is refactoring\n", get_time() - td->time_start, id);
	pthread_mutex_unlock(td->print_mtx);
	usleep(td->config->time_to_refactor * 1000);
}

int	do_work(t_thread_data *td)
{
	if (!td->alive || take_dongles(td) == -1)
		return (-1);
	compiling(td->id, td);
	released_dongles(td);
	if (!td->alive)
		return (-1);
	debugging(td->id, td);
	if (!td->alive)
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
		if (!td->alive || do_work(td) == -1)
			return (NULL);
		i++;
	}
	pthread_mutex_lock(td->queue_mtx);
	td->alive = 0;
	pthread_mutex_unlock(td->queue_mtx);
	return (NULL);
}
