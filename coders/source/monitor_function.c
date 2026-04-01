/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:51 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/01 15:11:37 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ending_all_threads(t_threads *threads_obj)
{
	int	i;

	i = 0;
	while (i < threads_obj->number_of_coders)
	{
		threads_obj->td[i].alive = false;
		pthread_cond_broadcast(&threads_obj->td->conds[i]);
		i++;
	}
	i = 0;
	usleep(0);
	while (i < threads_obj->number_of_coders)
		pthread_mutex_unlock(&threads_obj->dongles_mtx[i++]);
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
	int			i;

	obj = (t_threads *)arg;
	while (1)
	{
		if (obj->number_of_coders == 1 && obj->td[0].alive == false)
			return (NULL);
		i = 0;
		while (i++ < obj->number_of_coders - 1)
		{
			time = get_time();
			arg = (void *)obj->td[i].config->time_to_burnout;
			if (all_finish(obj))
				return (NULL);
			if (time - obj->td[i].last_cmp_start > (long long)arg)
			{
				obj->td[i].alive = false;
				pthread_mutex_lock(obj->print_mtx);
				printf("%lld %d burned out\n", time - obj->td[i].time_start,
					obj->td[i].id);
				pthread_mutex_unlock(obj->print_mtx);
				ending_all_threads(obj);
				return (NULL);
			}
		}
	}
	return (NULL);
}
