/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogard-antoine <rogard-antoine@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:05:23 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/03/17 17:11:06 by rogard-anto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

int	free_all(t_config *config, t_tools *tools, pthread_mutex_t *mtx)
{
	if (config)
		free(config);
	if (mtx)
		free(mtx);
	if (tools)
	{
		if (tools->threads)
			free(tools->threads);
		if (tools->td)
			free(tools->td);
		free(tools);
	}
	return (-1);
}
