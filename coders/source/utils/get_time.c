/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 12:57:45 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 16:44:14 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
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
	struct timespec timeToWait;

	timeToWait.tv_sec = 1;
	timeToWait.tv_nsec = 1000 * 1000000;
	if (timeToWait.tv_nsec >= 1000000000)
	{
		timeToWait.tv_sec /= 1000000000;
		timeToWait.tv_nsec = timeToWait.tv_nsec % 1000000000;
	}
	return (timeToWait);
}