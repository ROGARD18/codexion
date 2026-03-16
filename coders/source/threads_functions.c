/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 19:09:49 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "codexion.h"

void	compiling(int id, int time_to_compile)
{
	printf("%d is compiling\n", id);
	sleep_ms(time_to_compile);
}

void	debugging(int id, int time_to_debug)
{
	printf("%d is debugging\n", id);
	sleep_ms(time_to_debug);
}

void	refactoring(int id, int time_to_refactor)
{
	printf("%d is refactoring\n", id);
	sleep_ms(time_to_refactor);
}

void	*thread_work(void *arg)
{
	t_tools		*tools;
	t_config	*config;

	tools = (t_tools *)arg;
	config = tools->config;
	pthread_mutex_lock(tools->mutex);
	printf("L' ID est = %d\n", tools->thread_id);
	compiling(tools->thread_id, config->time_to_compile);
	debugging(tools->thread_id, config->time_to_debug);
	refactoring(tools->thread_id, config->time_to_refactor);
	sleep_ms(config->dongle_cooldown);
	pthread_mutex_unlock(tools->mutex);
	return (NULL);
}
