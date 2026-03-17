/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogard-antoine <rogard-antoine@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:45:44 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/17 16:21:51 by rogard-anto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int	create_threads(t_tools *tools, t_config *config, pthread_mutex_t *mtx)
{
	int	i;

	tools->threads = malloc(sizeof(pthread_t)
			* config->number_of_coders);
	if (!tools->threads)
		return (-1);
	tools->td = malloc(sizeof(t_thread_data) * config->number_of_coders);
	if (!tools->td)
		return (-1);
	pthread_mutex_init(mtx, NULL);
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
	pthread_mutex_destroy(mtx);
	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_join(tools->threads[i], NULL);
		i++;
	}
	free(tools->threads);
	free(tools->td);
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
	{
		free(config);
		free(tools);
		return (-1);	
	}
	mtx = malloc(sizeof(pthread_mutex_t) * config->number_of_coders);
	if (!mtx)
	{
		free(config);
		free(tools);
		return (-1);	
	}
	if (create_threads(tools, config, mtx))
	{
		free(config);
		free(tools);
		return (-1);	
	}
	printf("numbers_of_coders = %d\n", config->number_of_coders);
	free(config);
	free(tools);
	free(mtx);
	return (0);
}
