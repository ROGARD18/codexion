/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:05:23 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/03/29 16:22:58 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <stdio.h>

int	free_all(t_config *config, t_threads *threads, pthread_mutex_t *mtx)
{
	if (config)
		free(config);
	if (mtx)
		free(mtx);
	if (threads)
	{
		if (threads->td)
			free(threads->td);
		if (threads->conds)
			free(threads->conds);
		if (threads->threads_list)
			free(threads->threads_list);
		free(threads);
	}
	printf("\n\nFREE ALL\n\n");
	return (-1);
}
