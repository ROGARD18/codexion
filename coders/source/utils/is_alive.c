/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 20:31:00 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 21:39:15 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	is_alive(t_thread_data *td)
{
	bool	status;

	if (pthread_mutex_lock(td->state_mtx) != 0)
		return (false);
	status = td->alive;
	pthread_mutex_unlock(td->state_mtx);
	return (status);
}
