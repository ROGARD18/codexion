/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:05:23 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/03/18 16:56:43 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

int	free_all(t_config *config, t_threads *threads, pthread_mutex_t *mtx)
{
	if (config)
		free(config);
	if (mtx)
		free(mtx);
	if (threads)
	{
		if (threads->threads)
			free(threads->threads);
		if (threads->td)
			free(threads->td);
		free(threads);
	}
	return (-1);
}
