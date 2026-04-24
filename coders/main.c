/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:43:28 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 20:39:22 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	create__all_td(t_threads *obj, pthread_mutex_t *d_mtx,
		t_config *conf)
{
	int				i;
	t_thread_data	*tmp;

	obj->td = malloc(sizeof(t_thread_data) * conf->number_of_coders);
	if (!obj->td)
		return (0);
	i = 0;
	while (i < obj->number_of_coders)
	{
		tmp = init_td(conf, obj, obj->time, i);
		if (!tmp)
			return (0);
		obj->td[i] = *tmp;
		free(tmp);
		obj->td[i].dongle_left = &d_mtx[i];
		obj->td[i].dongle_right = &d_mtx[(i + 1) % conf->number_of_coders];
		i++;
	}
	return (1);
}

int	create_threads(t_threads *obj, t_config *conf, pthread_mutex_t *d_mtx)
{
	int			i;
	pthread_t	monitor;

	obj->number_of_coders = conf->number_of_coders;
	obj->threads_list = malloc(sizeof(pthread_t) * conf->number_of_coders);
	obj->time = get_time();
	if (!obj->threads_list || !create__all_td(obj, d_mtx, conf))
		return (-1);
	obj->pq->td = obj->td;
	i = 0;
	while (i < conf->number_of_coders)
	{
		pthread_create(&obj->threads_list[i], NULL, thread_work, &obj->td[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_work, obj);
	i = 0;
	while (i < conf->number_of_coders)
		pthread_join(obj->threads_list[i++], NULL);
	pthread_join(monitor, NULL);
	destroy_all_mutex(conf->number_of_coders, d_mtx);
	return (0);
}

int	main(int ac, char **av)
{
	t_config		*conf;
	t_threads		*obj;
	pthread_mutex_t	*d_mtx;
	int				i;

	conf = parsing(ac, av);
	if (!conf)
		return (1);
	d_mtx = malloc(sizeof(pthread_mutex_t) * conf->number_of_coders);
	if (!d_mtx)
		return (free_all(conf, NULL, NULL));
	init_all_mutex(conf->number_of_coders, d_mtx);
	obj = init_threads_obj(conf, get_time(), d_mtx);
	if (!obj)
		return (free_all(conf, NULL, d_mtx));
	obj->pq = init_prio_q(conf->number_of_coders, NULL, conf->sheduler);
	i = 0;
	while (obj->pq && i < conf->number_of_coders)
		pthread_cond_init(&obj->conds[i++], NULL);
	if (!obj->pq || create_threads(obj, conf, d_mtx) == -1)
		return (free_all(conf, obj, d_mtx));
	free_all(conf, obj, d_mtx);
	return (0);
}
