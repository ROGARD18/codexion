/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:53:19 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/18 18:39:31 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	*handling_parsing_error(t_error error, t_config *config)
{
	if (error == NUMBER_AC_ERROR)
		printf("The number of arguments must be 8.\n");
	else if (error == NEGATIVE_ERROR)
		printf("Arguments cannot be negative !\n");
	else if (error == SHEDULER_ERROR)
		printf("The last argument (sheduler) must be 'fifo' or 'edf'.");
	if (config)
		free(config);
	return (NULL);
}

t_config	*parsing(int ac, char **av)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (!config)
		return (handling_parsing_error(MALLOC_ERROR, NULL));
	if (ac != 9)
		return (handling_parsing_error(NUMBER_AC_ERROR, config));
	config->number_of_coders = atoi(av[1]);
	config->time_to_burnout = atoi(av[2]);
	config->time_to_compile = atoi(av[3]);
	config->time_to_debug = atoi(av[4]);
	config->time_to_refactor = atoi(av[5]);
	config->number_of_compiles_requiered = atoi(av[6]);
	printf("compiles ================= %d\n", config->number_of_compiles_requiered);
	config->dongle_cooldown = atoi(av[7]);
	config->sheduler = av[8];
	if (config->number_of_coders < 1 || config->time_to_burnout < 0
		|| config->time_to_compile < 0 || config->time_to_debug < 0
		|| config->time_to_refactor < 0 || config->dongle_cooldown < 0
		|| config->number_of_compiles_requiered < 0)
		return (handling_parsing_error(NEGATIVE_ERROR, config));
	if (strcmp(config->sheduler, "fifo") != 0 && strcmp(config->sheduler,
			"edf") != 0)
		return (handling_parsing_error(SHEDULER_ERROR, config));
	return (config);
}
