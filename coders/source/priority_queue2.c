/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 20:41:01 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 20:43:58 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	enqueue(t_prio_q *pq, int coder_index, int number_of_coders, char *sheduler)
{
	if (pq->size >= number_of_coders)
	{
		printf("NOT ENQUE !\n");
		return (-1);
	}
	pq->enqueue_order[coder_index] = pq->seq_counter++;
	pq->queue[pq->size] = coder_index;
	heapify_up(pq, pq->size, sheduler);
	pq->size++;
	return (0);
}

int	dequeue(t_prio_q *pq, char *sheduler)
{
	if (pq->size == 0)
		return (-1);
	pq->queue[0] = pq->queue[pq->size - 1];
	pq->size--;
	heapify_down(pq, 0, sheduler);
	return (0);
}
