/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:51 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/26 21:05:42 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <stdio.h>
#include <stdlib.h>

void	ending_all_threads(t_threads *threads_obj)
{
	int	i;

	i = 0;
	while (i < threads_obj->number_of_coders)
	{
		threads_obj->td[i].alive = false;
		i++;
	}
}

t_prio_q	*init_prio_q(int number_of_coders, t_thread_data *td)
{
	t_prio_q	*pq;
	int			i;

	i = 0;
	pq = malloc(sizeof(t_prio_q));
	if (!pq)
		return ((t_prio_q *)NULL);
	pq->td = td;
	pq->size = 0;
	while (i < number_of_coders)
	{
		enqueue(pq, i, number_of_coders);
		i++;
	}
	return (pq);
}

void	*monitor_work(void *arg)
{
	int				i;
	t_threads		*threads_obj;
	t_thread_data	td;
	pthread_t		*threads_list;
	long long		time;
	t_prio_q		*pq;

	threads_obj = (t_threads *)arg;
	threads_list = threads_obj->threads;
	pq = init_prio_q(threads_obj->number_of_coders, threads_obj->td);
	while (1)
	{
		i = 0;
		while (i < threads_obj->number_of_coders - 1)
		{
			td = threads_obj->td[i];
			time = get_time();
			if (td.compiled_time == td.config->number_of_compiles_requiered
				&& time - td.time_start
				- td.last_compile_start > td.config->time_to_burnout)
			{
				printf("%lld %d burned out\n", time - td.time_start, td.id);
				ending_all_threads(threads_obj);
				return (NULL);
			}
			i++;
		}
	}
	printf("FINI\n");
	return (NULL);
}
