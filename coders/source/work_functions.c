/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogard-antoine <rogard-antoine@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:51:40 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/03/17 17:03:11 by rogard-anto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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
