/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:46:54 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 17:08:33 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

#include <pthread.h>

typedef	struct
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_requiered;
	int		dongle_cooldown;
	char	*sheduler;
}	t_config;

typedef struct
{
	int id;
	pthread_t thread;
}	t_thread;

typedef struct
{
	int thread_id;
	pthread_mutex_t *mutex;
}	t_tools;

t_config	*parsing(int ac, char **av);
void sleep_ms(int milliseconds);
void *thread_work(void *tools);

#endif