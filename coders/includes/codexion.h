/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:46:54 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/18 16:50:02 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <sys/time.h>

typedef enum e_error
{
	SHEDULER_ERROR,
	NUMBER_AC_ERROR,
	NEGATIVE_ERROR,
	MALLOC_ERROR
}					t_error;

typedef struct s_config
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_requiered;
	int				dongle_cooldown;
	char			*sheduler;
}					t_config;

typedef struct s_thread_data
{
	int				id;
	t_config		*config;
	struct timeval	start;
	struct timeval	end;
	pthread_t		*monitor;
	pthread_mutex_t	*dongle_left;
	pthread_mutex_t	*dongle_right;
}					t_thread_data;

typedef struct s_threads
{
	t_thread_data	*td;
	pthread_t		*threads;
}					t_threads;

// ===SOURCE===
t_config			*parsing(int ac, char **av);
void				*thread_work(void *tools);
void				compiling(int id, t_thread_data *td);
void				debugging(int id, t_thread_data *td);
void				refactoring(int id, t_thread_data *td);

// ===SOURCE/UTILS===
void				sleep_ms(int milliseconds);
void				init_all_mutex(int nb_coders, pthread_mutex_t *mtx);
void				destroy_all_mutex(int nb_coders, pthread_mutex_t *mtx);
int					free_all(t_config *config, t_tools *tools,
						pthread_mutex_t *mtx);

#endif