/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_dongles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogard-antoine <rogard-antoine@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/29 14:38:24 by rogard-anto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	take_dongles(t_thread_data *td)
{
	long long time;

	if (td->config->number_of_coders == 1)
	{
		time = get_time() - td->time_start;
		pthread_mutex_lock(td->dongle_right);
		printf("%lld %d has taken a dongle\n",time, td->id);
	}
	else if (td->id == td->config->number_of_coders)
	{
		pthread_mutex_lock(td->dongle_left);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle \\\n",time, td->id);
		pthread_mutex_lock(td->dongle_right);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle /\n",time, td->id);
	}
	else
	{
		pthread_mutex_lock(td->dongle_right);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle \\\n",time, td->id);
		pthread_mutex_lock(td->dongle_left);
		time = get_time() - td->time_start;
		printf("%lld %d has taken a dongle /\n",time, td->id);
	}
}

void	released_dongles(t_thread_data *td)
{
	if (td->config->number_of_coders == 1)
	{
		pthread_mutex_unlock(td->dongle_right);
		sleep_ms(td->config->dongle_cooldown);
	}
	else
	{
		pthread_mutex_unlock(td->dongle_left);
		sleep_ms(td->config->dongle_cooldown);
		pthread_mutex_unlock(td->dongle_right);
		sleep_ms(td->config->dongle_cooldown);
	}
}

// void	take_dongles(t_thread_data *td, t_prio_q *pq, t_threads *obj)
// {
//     pthread_mutex_lock(&obj->q_mtx);

//     enqueue(pq, td->id - 1, obj->number_of_coders); 
//     while (peek(pq) != (td->id - 1) && td->alive)
//     {
//         pthread_cond_wait(&obj->conds[td->id - 1], &obj->q_mtx);
//     }
    
//     pthread_mutex_lock(td->dongle_left);
//     pthread_mutex_lock(td->dongle_right);
    
//     pthread_mutex_unlock(&obj->q_mtx);
// }

// void	released_dongles(t_thread_data *td, t_prio_q *pq, t_threads *obj)
// {
//     pthread_mutex_lock(&obj->q_mtx);
    
//     pthread_mutex_unlock(td->dongle_left);
//     pthread_mutex_unlock(td->dongle_right);
    
//     dequeue(pq);
    
//     for (int i = 0; i < obj->number_of_coders; i++)
//         pthread_cond_broadcast(&obj->conds[i]);
        
//     pthread_mutex_unlock(&obj->q_mtx);
// }
