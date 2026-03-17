/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogard-antoine <rogard-antoine@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:45:44 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/17 16:47:37 by rogard-anto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
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

void	init_all_mutex(int nb_coders, pthread_mutex_t *mtx)
{
	while (nb_coders--)
		pthread_mutex_init(&(*mtx++), NULL);
}

void	destroy_all_mutex(int nb_coders, pthread_mutex_t *mtx)
{
	while (nb_coders--)
		pthread_mutex_destroy(&(*mtx++));
}

int	create_threads(t_tools *tools, t_config *config, pthread_mutex_t *mtx)
{
	int	i;

	tools->threads = malloc(sizeof(pthread_t) * config->number_of_coders);
	if (!tools->threads)
		return (-1);
	tools->td = malloc(sizeof(t_thread_data) * config->number_of_coders);
	if (!tools->td)
		return (-1);
	init_all_mutex(config->number_of_coders, mtx);
	i = 0;
	while (i < config->number_of_coders)
	{
		tools->td[i].thread_id = i + 1;
		tools->td[i].config = config;
		if (config->number_of_coders == 1)
		{
			tools->td[i].dongle_left = NULL;
			tools->td[i].dongle_right = &mtx[i];
		}
		if (i == 0)
			tools->td[i].dongle_left = &mtx[config->number_of_coders - 1];
		else
			tools->td[i].dongle_left = &mtx[i - 1];
		tools->td[i].dongle_right = &mtx[i % config->number_of_coders];
		pthread_create(&tools->threads[i], NULL, thread_work, &tools->td[i]);
		i++;
	}
	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_join(tools->threads[i], NULL);
		i++;
	}
	destroy_all_mutex(config->number_of_coders, mtx);
	return (0);
}

int	main(int ac, char **av)
{
	t_config		*config;
	t_tools			*tools;
	pthread_mutex_t	*mtx;

	config = parsing(ac, av);
	tools = malloc(sizeof(t_tools));
	if (!config || !tools)
		return (free_all(config, tools, NULL));
	mtx = malloc(sizeof(pthread_mutex_t) * config->number_of_coders);
	if (!mtx)
		return (free_all(config, tools, mtx));
	if (create_threads(tools, config, mtx))
		return (free_all(config, tools, mtx));
	printf("numbers_of_coders = %d\n", config->number_of_coders);
	free_all(config, tools, mtx);
	return (0);
}
