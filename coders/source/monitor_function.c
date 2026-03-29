/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogard-antoine <rogard-antoine@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:51 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/29 14:38:05 by rogard-anto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <stdio.h>
#include <stdlib.h>

// void	init_all_cond(void)
// {
// 	pthread_cond_t	
// }

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
    t_threads	*obj = (t_threads *)arg;
    long long	now;
    int			i;

    while (1)
    {
        for (i = 0; i < obj->number_of_coders; i++)
        {
            now = get_time();
            if (now - obj->td[i].last_compile_start > obj->td[i].config->time_to_burnout)
            {
                pthread_mutex_lock(&obj->print_mtx);
                printf("%lld %d burned out\n", now - obj->td[i].time_start, obj->td[i].id);
                ending_all_threads(obj);
                pthread_mutex_unlock(&obj->print_mtx);
                return (NULL);
            }
        }
        usleep(500);
    }
    return (NULL);
}
