/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:45:44 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 17:30:14 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

void create_threads(int number_of_coders, void *(*thread_work)(void *),
	t_tools *tools)
{
	int count_id;
	int i;
	pthread_t thread_list[number_of_coders];

	i = 0;
	count_id = 1;
	while (number_of_coders--)
	{
		tools->thread_id = count_id;
		pthread_create(&thread_list[i++], NULL, thread_work, tools);
		count_id++;
	}
	i = 0;
	while (thread_list[i])
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_config	*config;
	t_tools		*tools;
	pthread_mutex_t mtx;

	config = parsing(ac, av);
	if (!config)
		return (-1);

	tools = malloc(sizeof(t_tools));
	tools->mutex = &mtx;
	pthread_mutex_init(&mtx, NULL);
	create_threads(config->number_of_coders, &thread_work, tools);
	printf("numbers_of_coders = %d\n", config->number_of_coders);
 
	free(config);
	free(tools);
	pthread_mutex_destroy(&mtx);
	
	return (0);
}
