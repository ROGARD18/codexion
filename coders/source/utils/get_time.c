/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 12:57:45 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 21:12:21 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <sys/time.h>

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

struct timespec	get_interval(void)
{
	struct timespec	time_to_wait;

	time_to_wait.tv_sec = 1;
	time_to_wait.tv_nsec = 1000 * 1000000;
	if (time_to_wait.tv_nsec >= 1000000000)
	{
		time_to_wait.tv_sec /= 1000000000;
		time_to_wait.tv_nsec = time_to_wait.tv_nsec % 1000000000;
	}
	return (time_to_wait);
}
