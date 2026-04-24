/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:49:32 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/04/24 21:17:38 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

int	init_all_mutex(int nb_coders, pthread_mutex_t *mtxs)
{
	int	i;

	i = 0;
	while (i < nb_coders)
	{
		if (pthread_mutex_init(&mtxs[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&mtxs[--i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	destroy_all_mutex(int nb_coders, pthread_mutex_t *mtxs)
{
	while (nb_coders--)
		pthread_mutex_destroy(&mtxs[nb_coders]);
}
