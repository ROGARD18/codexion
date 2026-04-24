/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:53:19 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 22:00:04 by anrogard         ###   ########.fr       */
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
		printf("ERROR ! The number of arguments must be 8.\n");
	else if (error == NEGATIVE_ERROR)
		printf("ERROR ! Arguments cannot be negative !\n");
	else if (error == ONE_CODER_ERROR)
		printf("ERROR ! Need more than one coder !\n");
	else if (error == SHEDULER_ERROR)
		printf("ERROR ! The last argument (sheduler) must be 'fifo' or 'edf'.");
	if (config)
		free(config);
	return (NULL);
}

t_config	*parsing(int ac, char **av)
{
	t_config	*cf;

	cf = malloc(sizeof(t_config));
	if (!cf)
		return (handling_parsing_error(MALLOC_ERROR, NULL));
	if (ac != 9)
		return (handling_parsing_error(NUMBER_AC_ERROR, cf));
	cf->number_of_coders = atoi(av[1]);
	if (cf->number_of_coders == 1)
		return (handling_parsing_error(ONE_CODER_ERROR, cf));
	cf->time_to_burnout = atoi(av[2]);
	cf->time_to_compile = atoi(av[3]);
	cf->time_to_debug = atoi(av[4]);
	cf->time_to_refactor = atoi(av[5]);
	cf->number_of_compiles_requiered = atoi(av[6]);
	cf->dongle_cooldown = atoi(av[7]);
	cf->sheduler = av[8];
	if (cf->number_of_coders < 1 || cf->time_to_burnout < 0
		|| cf->time_to_compile < 0 || cf->time_to_debug < 0
		|| cf->time_to_refactor < 0 || cf->dongle_cooldown < 0
		|| cf->number_of_compiles_requiered < 0)
		return (handling_parsing_error(NEGATIVE_ERROR, cf));
	if (strcmp(cf->sheduler, "fifo") != 0 && strcmp(cf->sheduler, "edf") != 0)
		return (handling_parsing_error(SHEDULER_ERROR, cf));
	return (cf);
}
