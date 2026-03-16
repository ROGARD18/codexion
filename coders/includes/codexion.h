/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:46:54 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 19:10:58 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>

typedef enum e_error
{
	SHEDULER_ERROR,
	NUMBER_AC_ERROR,
	NEGATIVE_ERROR,
	MALLOC_ERROR
}	t_error;

typedef struct s_config
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

typedef struct s_thread
{
	int			id;
	pthread_t	thread;
}	t_thread;

typedef struct s_tools
{
	int				thread_id;
	pthread_mutex_t	*mutex;
	t_config		*config;
}	t_tools;

typedef struct s_dongle
{
	ptrhread_mutex_t	mtx;
}	t_dongle;

t_config	*parsing(int ac, char **av);
void		sleep_ms(int milliseconds);
void		*thread_work(void *tools);

#endif