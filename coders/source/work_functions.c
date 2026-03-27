/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:51:40 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/03/27 17:03:13 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	compiling(int id, t_thread_data *td)
{
	long long	time;

	time = get_time();
	td->last_compile_start = time - td->time_start;
	printf("%lld %d is compiling\n", td->last_compile_start, id);
	sleep_ms(td->config->time_to_compile);
}

void	debugging(int id, t_thread_data *td)
{
	long long	time;

	time = get_time();
	td->last_compile_start = time - td->time_start;
	printf("%lld %d is debugging\n", td->last_compile_start, id);
	sleep_ms(td->config->time_to_debug);
}

void	refactoring(int id, t_thread_data *td)
{
	long long	time;

	time = get_time();
	td->last_compile_start = time - td->time_start;
	printf("%lld %d is refactoring\n", td->last_compile_start, id);
	sleep_ms(td->config->time_to_refactor);
}
void	*thread_work(void *arg)
{
	t_thread_data	*td;

	td = (t_thread_data *)arg;
	take_dongles(td);
	compiling(td->id, td);
	td->compiled_time += 1;
	released_dongles(td);
	debugging(td->id, td);
	refactoring(td->id, td);
	return (NULL);
}
