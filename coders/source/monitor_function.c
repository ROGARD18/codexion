/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:51 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/29 17:38:39 by anrogard         ###   ########.fr       */
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

void	*monitor_work(void *arg)
{
    t_threads	*obj = (t_threads *)arg;
    long long	time;
    int			i;

	i = 0;
    while (1)
    {
        while (i++ < obj->number_of_coders - 1)
        {
            time = get_time();
            if (time - obj->td[i].last_compile_start > obj->td[i].config->time_to_burnout)
            {
                pthread_mutex_lock(&obj->print_mtx);
                printf("%lld %d burned out\n", time - obj->td[i].time_start, obj->td[i].id);
                ending_all_threads(obj);
                pthread_mutex_unlock(&obj->print_mtx);
                return (NULL);
            }
        }
        sleep_ms(500);
    }
    return (NULL);
}
