/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:53:19 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 01:10:37 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

t_config	*parsing(int ac, char **av)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (ac != 9)
	{
		printf("The number of arguments must be 8.\n");
		printf("You have %d", ac);

		return (NULL);
	}
	config->number_of_coders = atoi(av[1]);
	config->time_to_burnout = atoi(av[2]);
	config->time_to_compile = atoi(av[3]);
	config->time_to_debug = atoi(av[4]);
	config->time_to_refactor = atoi(av[5]);
	config->number_of_compiles_requiered = atoi(av[6]);
	config->dongle_cooldown =atoi(av[7]);
	config->sheduler = av[8];

	return config;
}
