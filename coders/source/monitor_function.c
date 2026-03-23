/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:51 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/23 16:44:41 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <stdio.h>

void	ending_all_threads(t_threads *threads_obj)
{
	int	i;
	pthread_mutex_t	*run;

	i = 0;
	while (i < threads_obj->number_of_coders)
	{
		run = threads_obj->td[i].run;
		pthread_mutex_lock(run);
		threads_obj->td[i].alive = false;
		pthread_mutex_unlock(run);
		i++;
	}
}

void	*monitor_work(void *arg)
{
	int			i;
	t_threads	*threads_obj;
	pthread_t	*threads_list;
	long long	time;

	threads_obj = (t_threads *)arg;
	threads_list = threads_obj->threads;
	while (1)
	{
		i = 0;
		while (i < threads_obj->number_of_coders - 1)
		{
			printf("i = %d\n", i);
			time = get_time();
			if (threads_obj->td[i].id)
				printf("->   id = %d\n", threads_obj->td[i].id);
			else
				printf("->   id = NULL\n");
			if (time)
				printf("->   time = %lld\n", time);
			else
				printf("->   time = NULL\n");
			if (threads_obj->td[i].last_compile_start)
				printf("->   last_compile_start = %lld\n",
					threads_obj->td[i].last_compile_start);
			else
				printf("->   last_compile_start = NULL\n");
			if (threads_obj->td[i].config->time_to_burnout)
				printf("->   time_to_burnout = %lld\n",
					threads_obj->td[i].config->time_to_burnout);
			else
				printf("->   time_to_burnout = NULL\n");
			if (time
				- threads_obj->td[i].last_compile_start > threads_obj->td[i].config->time_to_burnout)
			{
				printf("--------------- Burnout n* %d----------\n", threads_obj->td->id);
				ending_all_threads(threads_obj);
				return (NULL);
			}
			i++;
		}
	}
	printf("FINI\n");
	return (NULL);
}
