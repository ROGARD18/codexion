/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogard-antoine <rogard-antoine@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:49:32 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/03/17 17:03:23 by rogard-anto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

void	init_all_mutex(int nb_coders, pthread_mutex_t *mtx)
{
	while (nb_coders--)
		pthread_mutex_init(&(*mtx++), NULL);
}

void	destroy_all_mutex(int nb_coders, pthread_mutex_t *mtx)
{
	while (nb_coders--)
		pthread_mutex_destroy(&(*mtx++));
}
