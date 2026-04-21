/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:51 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/21 01:48:47 by anrogard         ###   ########.fr       */
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
	int			i;

	obj = (t_threads *)arg;
	while (1)
	{
		i = 0;
		while (i < obj->number_of_coders)
		{
			if (get_time()
				- obj->td[i].last_cmp_start > obj->td[i].config->time_to_burnout)
			{
				ending_all_threads(obj);
				pthread_mutex_lock(obj->print_mtx);
				printf("%lld %d burned out\n", get_time()
					- obj->td[i].time_start, obj->td[i].id);
				pthread_mutex_unlock(obj->print_mtx);
				return (NULL);
			}
			i++;
		}
		if (all_finish(obj))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
