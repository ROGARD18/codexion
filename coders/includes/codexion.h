/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:46:54 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/29 19:54:29 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdbool.h>

typedef enum e_error
{
	SHEDULER_ERROR,
	NUMBER_AC_ERROR,
	NEGATIVE_ERROR,
	MALLOC_ERROR
}								t_error;

typedef struct s_config
{
	int							number_of_coders;
	long long					time_to_burnout;
	long long					time_to_compile;
	long long					time_to_debug;
	long long					time_to_refactor;
	int							number_of_compiles_requiered;
	long long					dongle_cooldown;
	char						*sheduler;
}								t_config;

typedef struct s_thread_data	t_thread_data;

typedef struct s_prio_q
{
	int							*queue;
	t_thread_data				*td;
	int							size;
	char						*sheduler;
}								t_prio_q;

typedef struct s_thread_data
{
	int							id;
	int							compiled_time;
	long long					time_start;
	t_config					*config;
	long long					last_compile_start;
	bool						alive;
	pthread_mutex_t				*dongle_left;
	pthread_mutex_t				*dongle_right;
	pthread_mutex_t				*print_mtx;
	pthread_mutex_t				*queue_mtx;
	pthread_cond_t				*conds;
	t_prio_q					*pq;
}								t_thread_data;

typedef struct s_threads
{
	int							number_of_coders;
	pthread_mutex_t				*print_mtx;
	pthread_mutex_t				*queue_mtx;
	pthread_cond_t				*conds;
	t_thread_data				*td;
	pthread_t					*threads_list;
}								t_threads;

// ===SOURCE===
t_config						*parsing(int ac, char **av);
void							*thread_work(void *threads);
void							compiling(int id, t_thread_data *td);
void							debugging(int id, t_thread_data *td);
void							refactoring(int id, t_thread_data *td);
void							*monitor_work(void *arg);

void							take_dongles(t_thread_data *td);
void							released_dongles(t_thread_data *td);

// ===SOURCE/UTILS===
void							sleep_ms(int milliseconds, t_thread_data *td);
void							init_all_mutex(int nb_coders,
									pthread_mutex_t *mtx);
void							destroy_all_mutex(int nb_coders,
									pthread_mutex_t *mtx);
int								free_all(t_config *config, t_threads *threads,
									pthread_mutex_t *mtx);
long long						get_time(void);
void							swap(int *a, int *b);

// ===SOURCE/UTILS/PRIOQ===
void							heapifyUp(t_prio_q *pq, int index,
									char *sheduler);
void							heapifyDown(t_prio_q *pq, int index,
									char *sheduler);
int								enqueue(t_prio_q *pq, int coder_index,
									int number_of_coders, char *sheduler);
int								dequeue(t_prio_q *pq, char *sheduler);
int								peek(t_prio_q *pq);

#endif