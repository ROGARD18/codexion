/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:51 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/27 18:21:32 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <stdio.h>
#include <stdlib.h>

void	init_all_cond(void)
{
	pthread_cond_t	
}

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

t_prio_q	*init_prio_q(int number_of_coders, t_thread_data *td, char *mode)
{
	// (void)number_of_coders;
	t_prio_q	*pq;
	int			i;

	i = 0;
	pq = malloc(sizeof(t_prio_q));
	if (!pq)
		return ((t_prio_q *)NULL);
	pq->queue = malloc(sizeof(int) * number_of_coders);
	pq->td = td;
	pq->size = 0;
	pq->mode = mode;
	while (i < number_of_coders)
	{
		if (enqueue(pq, i, number_of_coders, mode) == -1)
			return ((t_prio_q *)NULL);
		i++;
	}
	return (pq);
}

void	*monitor_work(void *arg)
{
	int				i;
	char *mode;
	t_threads		*threads_obj;
	t_thread_data	td;
	pthread_t		*threads_list;
	long long		time;
	t_prio_q		*pq;
	int				index_peek;

	threads_obj = (t_threads *)arg;
	mode = threads_obj->td[0].config->sheduler;
	threads_list = threads_obj->threads;
	pq = init_prio_q(threads_obj->number_of_coders, threads_obj->td, mode);
	while (1)
	{
		i = 0;
		while (i < threads_obj->number_of_coders - 1)
		{
			index_peek = peek(pq);
			printf("PEEK: %d\n", index_peek);
			td = threads_obj->td[index_peek];
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
