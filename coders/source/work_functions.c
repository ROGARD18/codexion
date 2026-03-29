/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:51:40 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/03/29 17:38:08 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int verify_life(t_thread_data *td)
{
	if (!td->alive)
		return (-1);
	return (0);
}

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
	int				i;

	i = -1;
	td = (t_thread_data *)arg;
	while (i++ < td->config->number_of_compiles_requiered - 1)
	{
		// if (verify_life(td) == -1)
		// {
		// 	printf("-1\n");
		// 	return (NULL);
		// }
		take_dongles(td);
		if (verify_life(td) == -1)
		{
			printf("-1\n");
			return (NULL);
		}
		compiling(td->id, td);
		if (verify_life(td) == -1)
		{
			printf("-1\n");
			return (NULL);
		}
		td->compiled_time += 1;
		released_dongles(td);
		if (verify_life(td) == -1)
		{
			printf("-1\n");
			return (NULL);
		}
		debugging(td->id, td);
		if (verify_life(td) == -1)
		{
			printf("-1\n");
			return (NULL);
		}
		refactoring(td->id, td);
		if (verify_life(td) == -1)
		{
			printf("-1\n");
			return (NULL);
		}
	}
	return (NULL);
}
