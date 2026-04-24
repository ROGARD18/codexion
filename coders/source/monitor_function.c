/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:51 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 21:40:00 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool	all_finish(t_threads *obj)
{
	int	i;

	i = 0;
	while (i < obj->number_of_coders)
	{
		if (pthread_mutex_lock(&obj->state_mtx[i]) != 0)
			return (false);
		if (obj->td[i].alive == true)
		{
			pthread_mutex_unlock(&obj->state_mtx[i]);
			return (false);
		}
		pthread_mutex_unlock(&obj->state_mtx[i]);
		i++;
	}
	return (true);
}

void	*monitor_work(void *arg)
{
	t_threads	*obj;
	int			i;
	long long	last_meal;

	obj = (t_threads *)arg;
	while (1)
	{
		i = 0;
		while (i < obj->number_of_coders)
		{
			if (pthread_mutex_lock(&obj->state_mtx[i]) == 0)
			{
				last_meal = obj->td[i].last_cmp_start;
				pthread_mutex_unlock(&obj->state_mtx[i]);
				if (get_time() - last_meal > obj->td[i].config->time_to_burnout)
				{
					if (pthread_mutex_lock(obj->print_mtx) == 0)
					{
						printf("%lld %d burned out\n", get_time()
							- obj->td[i].time_start, obj->td[i].id);
						ending_all_threads(obj);
						pthread_mutex_unlock(obj->print_mtx);
					}
					return (NULL);
				}
			}
			i++;
		}
		if (all_finish(obj))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
