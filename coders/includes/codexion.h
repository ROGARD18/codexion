/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:46:54 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 21:10:12 by anrogard         ###   ########.fr       */
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

typedef struct s_thread_data
{
    int             thread_id;
    t_config        *config;
    pthread_mutex_t *dongle_mutex;
}   t_thread_data;

typedef struct s_tools
{
    t_config        *config;
    pthread_mutex_t dongle_mutex;
    t_thread_data   *threads_data;
    pthread_t       *threads;
}   t_tools;

t_config	*parsing(int ac, char **av);
void		sleep_ms(int milliseconds);
void		*thread_work(void *tools);

#endif