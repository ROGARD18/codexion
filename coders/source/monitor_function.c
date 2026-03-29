/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:51 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/29 22:27:26 by anrogard         ###   ########.fr       */
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
}

void	*monitor_work(void *arg)
{
	t_threads	*obj;
	long long	time;
	int			i;

	obj = (t_threads *)arg;
	while (1)
	{
		i = 0;
		while (i++ < obj->number_of_coders - 1)
		{
			time = get_time();
			arg = (void *)obj->td[i].config->time_to_burnout;
			if (time - obj->td[i].last_cmp_start > (long long)arg)
			{
				pthread_mutex_lock(obj->print_mtx);
				obj->td[i].alive = false;
				printf("%lld %d burned out\n", time - obj->td[i].time_start,
					obj->td[i].id);
				ending_all_threads(obj);
				pthread_mutex_unlock(obj->print_mtx);
				return (NULL);
			}
		}
	}
	return (NULL);
}
