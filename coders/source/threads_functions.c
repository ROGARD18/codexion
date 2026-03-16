/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:13:23 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 17:24:22 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "codexion.h"

void *compiling(int id)
{
    printf("%d is compiling\n", id);
    return (NULL);
}


void *debugging(int id)
{
    printf("%d is debugging\n", id);
    return (NULL);
}

void *refactoring(int id)
{
    printf("%d is refactoring\n", id);
    return (NULL);
}

void *thread_work(void *arg)
{
    t_tools *tools;

    tools = (t_tools *)arg;
    pthread_mutex_lock(tools->mutex);
    compiling(tools->thread_id);
    debugging(tools->thread_id);
    refactoring(tools->thread_id);
    pthread_mutex_unlock(tools->mutex);
    return (NULL);
}