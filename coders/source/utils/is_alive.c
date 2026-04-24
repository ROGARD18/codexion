/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 20:31:00 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 20:31:17 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	is_alive(t_thread_data *td)
{
	bool	status;

	pthread_mutex_lock(td->state_mtx);
	status = td->alive;
	pthread_mutex_unlock(td->state_mtx);
	return (status);
}
