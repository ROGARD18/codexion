/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:05:23 by rogard-anto       #+#    #+#             */
/*   Updated: 2026/03/29 20:14:10 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <stdio.h>

int free_all(t_config *config, t_threads *threads_obj, pthread_mutex_t *mtx)
{
    int i;

    if (config)
        free(config);
    if (mtx)
        free(mtx);
    if (threads_obj)
    {
        // 1. Libérer la Priority Queue (si elle existe via le premier thread data)
        if (threads_obj->td && threads_obj->td[0].pq)
        {
            free(threads_obj->td[0].pq->queue);
            free(threads_obj->td[0].pq);
        }
        // 2. Détruire et libérer les Mutex alloués manuellement
        if (threads_obj->print_mtx)
        {
            pthread_mutex_destroy(threads_obj->print_mtx);
            free(threads_obj->print_mtx);
        }
        if (threads_obj->queue_mtx)
        {
            pthread_mutex_destroy(threads_obj->queue_mtx);
            free(threads_obj->queue_mtx);
        }
        // 3. Détruire les conditions avant de libérer le tableau
        if (threads_obj->conds)
        {
            i = 0;
            while (i < threads_obj->number_of_coders)
                pthread_cond_destroy(&threads_obj->conds[i++]);
            free(threads_obj->conds);
        }
        if (threads_obj->td)
            free(threads_obj->td);
        if (threads_obj->threads_list)
            free(threads_obj->threads_list);
        free(threads_obj);
    }
    return (-1);
}
