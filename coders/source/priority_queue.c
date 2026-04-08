/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:44:54 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/08 16:53:48 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <string.h>

/*
** Returns the priority value for a given coder index.
** FIFO : order of arrival in the queue (smaller seq = higher priority).
** EDF  : last_cmp_start (= deadline - time_to_burnout, constant offset so
**        ordering is identical to comparing deadlines directly).
*/
static long long	get_priority(t_prio_q *pq, int coder_index, char *sheduler)
{
	if (strcmp(sheduler, "fifo") == 0)
		return ((long long)pq->enqueue_order[coder_index]);
	return (pq->td[coder_index].last_cmp_start);
}

void	heapify_up(t_prio_q *pq, int index, char *sheduler)
{
	long long	child_prio;
	long long	parent_prio;
	int			parent;

	if (index == 0)
		return ;
	parent = (index - 1) / 2;
	child_prio = get_priority(pq, pq->queue[index], sheduler);
	parent_prio = get_priority(pq, pq->queue[parent], sheduler);
	if (child_prio < parent_prio)
	{
		swap(&pq->queue[index], &pq->queue[parent]);
		heapify_up(pq, parent, sheduler);
	}
}

void	heapify_down(t_prio_q *pq, int index, char *sheduler)
{
	int	smallest;
	int	left;
	int	right;

	smallest = index;
	left = 2 * index + 1;
	right = 2 * index + 2;
	if (left < pq->size)
	{
		if (get_priority(pq, pq->queue[left], sheduler) < get_priority(pq,
				pq->queue[smallest], sheduler))
			smallest = left;
	}
	if (right < pq->size)
	{
		if (get_priority(pq, pq->queue[right], sheduler) < get_priority(pq,
				pq->queue[smallest], sheduler))
			smallest = right;
	}
	if (smallest != index)
	{
		swap(&pq->queue[index], &pq->queue[smallest]);
		heapify_down(pq, smallest, sheduler);
	}
}

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

int	peek(t_prio_q *pq)
{
	if (pq->size == 0)
		return (-1);
	return (pq->queue[0]);
}
