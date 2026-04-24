/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:43:28 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 21:31:02 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	create__all_td(t_threads *obj, pthread_mutex_t *mutexs,
		t_config *conf)
{
	int				i;
	t_thread_data	*tmp;

	obj->td = malloc(sizeof(t_thread_data) * conf->number_of_coders);
	if (!obj->td)
		return (-1);
	i = 0;
	while (i < obj->number_of_coders)
	{
		tmp = init_td(conf, obj, obj->time, i);
		if (!tmp)
			return (0);
		obj->td[i] = *tmp;
		free(tmp);
		obj->td[i].dongle_left = &mutexs[i];
		obj->td[i].dongle_right = &mutexs[(i + 1) % conf->number_of_coders];
		i++;
	}
	return (0);
}

int	create_threads(t_threads *obj, t_config *conf, pthread_mutex_t *mutexs)
{
	int			i;
	int			created;
	pthread_t	monitor;

	obj->number_of_coders = conf->number_of_coders;
	obj->threads_list = malloc(sizeof(pthread_t) * conf->number_of_coders);
	if (!obj->threads_list || create__all_td(obj, mutexs, conf) == -1)
		return (-1);
	obj->pq->td = obj->td;
	obj->time = get_time();
	i = 0;
	created = 0;
	while (i < conf->number_of_coders)
	{
		if (pthread_create(&obj->threads_list[i], NULL, thread_work,
				&obj->td[i]) != 0)
			break ;
		i++;
		created++;
	}
	if (created < conf->number_of_coders)
	{
		ending_all_threads(obj);
		while (i < created)
			pthread_join(obj->threads_list[i++], NULL);
		return (-1);
	}
	if (pthread_create(&monitor, NULL, monitor_work, obj) != 0)
	{
		ending_all_threads(obj);
		i = 0;
		while (i < created)
			pthread_join(obj->threads_list[i++], NULL);
		return (-1);
	}
	i = 0;
	while (i < conf->number_of_coders)
		pthread_join(obj->threads_list[i++], NULL);
	pthread_join(monitor, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_config		*conf;
	t_threads		*obj;
	pthread_mutex_t	*mutexs;
	int				i;

	conf = parsing(ac, av);
	if (!conf)
		return (-1);
	mutexs = malloc(sizeof(pthread_mutex_t) * conf->number_of_coders);
	if (!mutexs)
		return (free_all(conf, NULL, NULL));
	if (init_all_mutex(conf->number_of_coders, mutexs) != 0)
		return (free_all(conf, NULL, mutexs));
	obj = init_threads_obj(conf, get_time(), mutexs);
	if (!obj)
		return (free_all(conf, NULL, mutexs));
	obj->pq = init_prio_q(conf->number_of_coders, NULL, conf->sheduler);
	if (!obj->pq)
		return (free_all(conf, obj, mutexs));
	i = 0;
	while (i < conf->number_of_coders)
	{
		if (pthread_cond_init(&obj->conds[i++], NULL) != 0)
			return (free_all(conf, obj, mutexs));
	}
	if (create_threads(obj, conf, mutexs) == -1)
		return (free_all(conf, obj, mutexs));
	free_all(conf, obj, mutexs);
	return (0);
}
