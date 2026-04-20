/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:51 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/20 14:05:46 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
** Sets alive=false for every coder and broadcasts on all condition variables
** so threads blocked in pthread_cond_wait (inside take_dongles) wake up,
** see alive==false and exit cleanly.
** Threads blocked on a raw pthread_mutex_lock(dongle) will acquire the mutex
** naturally once its current owner releases it, then check alive and return.
** We must NOT unlock mutexes we do not own — that is undefined behaviour.
*/
void	ending_all_threads(t_threads *threads_obj)
{
	int	i;

	i = 0;
	while (i < threads_obj->number_of_coders)
	{
		threads_obj->td[i].alive = false;
		i++;
	}
	i = 0;
	while (i < threads_obj->number_of_coders)
	{
		pthread_cond_broadcast(&threads_obj->td[0].conds[i]);
		i++;
	}
}

bool	all_finish(t_threads *obj)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < obj->number_of_coders)
	{
		if (obj->td[i++].alive == 0)
			count++;
	}
	if (count == obj->number_of_coders)
		return (true);
	return (false);
}

void	*monitor_work(void *arg)
{
	t_threads	*obj;
	long long	time;
	long long	burnout_delay;
	int			i;

	obj = (t_threads *)arg;
	while (1)
	{
		if (all_finish(obj))
			return (NULL);
		i = 0;
		while (i < obj->number_of_coders)
		{
			burnout_delay = (long long)obj->td[i].config->time_to_burnout;
			time = get_time();
			if (obj->td[i].alive && time
				- obj->td[i].last_cmp_start > burnout_delay)
			{
				pthread_mutex_lock(obj->print_mtx);
				printf("%lld %d burned out\n", time - obj->td[i].time_start,
					obj->td[i].id);
				pthread_mutex_unlock(obj->print_mtx);
				ending_all_threads(obj);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
