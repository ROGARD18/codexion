/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:43:19 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 21:39:51 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	compiling(int id, t_thread_data *td)
{
	if (!is_alive(td))
		return ;
	if (pthread_mutex_lock(td->print_mtx) == 0)
	{
		printf("%lld %d is compiling\n", get_time() - td->time_start, id);
		pthread_mutex_unlock(td->print_mtx);
	}
	if (pthread_mutex_lock(td->state_mtx) == 0)
	{
		td->last_cmp_start = get_time();
		pthread_mutex_unlock(td->state_mtx);
	}
	usleep(td->config->time_to_compile * 1000);
}

void	debugging(int id, t_thread_data *td)
{
	if (!is_alive(td))
		return ;
	if (pthread_mutex_lock(td->print_mtx) == 0)
	{
		printf("%lld %d is debugging\n", get_time() - td->time_start, id);
		pthread_mutex_unlock(td->print_mtx);
	}
	usleep(td->config->time_to_debug * 1000);
}

void	refactoring(int id, t_thread_data *td)
{
	if (!is_alive(td))
		return ;
	if (pthread_mutex_lock(td->print_mtx) == 0)
	{
		printf("%lld %d is refactoring\n", get_time() - td->time_start, id);
		pthread_mutex_unlock(td->print_mtx);
	}
	usleep(td->config->time_to_refactor * 1000);
}

int	do_work(t_thread_data *td)
{
	if (!is_alive(td))
		return (-1);
	if (take_dongles(td) == -1)
		return (-1);
	compiling(td->id, td);
	released_dongles(td);
	if (!is_alive(td))
		return (-1);
	debugging(td->id, td);
	if (!is_alive(td))
		return (-1);
	refactoring(td->id, td);
	return (0);
}

void	*thread_work(void *arg)
{
	t_thread_data	*td;
	int				i;

	td = (t_thread_data *)arg;
	i = 0;
	while (i < td->config->number_of_compiles_requiered)
	{
		if (!is_alive(td) || do_work(td) == -1)
			return (NULL);
		i++;
	}
	if (pthread_mutex_lock(td->state_mtx) == 0)
	{
		td->alive = false;
		pthread_mutex_unlock(td->state_mtx);
	}
	return (NULL);
}
