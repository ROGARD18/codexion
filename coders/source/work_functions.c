/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:51:40 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/03/23 16:22:57 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	compiling(int id, t_thread_data *td)
{
	td->last_compile_start = get_time();
	printf("%lld %d is compiling\n",td->last_compile_start, id);
	sleep_ms(td->config->time_to_compile);
}

void	debugging(int id, t_thread_data *td)
{
	printf("%d is debugging\n", id);
	sleep_ms(td->config->time_to_debug);
}

void	refactoring(int id, t_thread_data *td)
{
	printf("%d is refactoring\n", id);
	sleep_ms(td->config->time_to_refactor);
}
