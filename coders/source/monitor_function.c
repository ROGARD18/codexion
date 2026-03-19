/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:51 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/19 12:20:13 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <stdio.h>

void	*monitor_work(void *arg)
{
	int i;
	t_threads *threads;
	pthread_t *threads_list;
	t_thread_data *td_list;

	threads = (t_threads *)arg;
	td_list = threads->td;
	threads_list = threads->threads;
	while (threads->run)
	{
		i = 0;
		while (threads_list[i])
		{
			if (td_list[i].burnout == 1)
            {
                threads->run = 0;
				printf("---------------verified burnout ----------\n");
                return NULL;
            }
            i++;
			sleep_ms(1);
		}
	}
	return (NULL);
}
