/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:44:54 by anrogard          #+#    #+#             */
/*   Updated: 2026/04/24 22:04:22 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <string.h>

int	peek(t_prio_q *pq)
{
	if (pq->size == 0)
		return (-1);
	return (pq->queue[0]);
}

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
	int			smallest;
	int			left;
	int			right;
	long long	prio_smallest;

	smallest = index;
	left = 2 * index + 1;
	right = 2 * index + 2;
	prio_smallest = get_priority(pq, pq->queue[smallest], sheduler);
	if (left < pq->size && get_priority(pq, pq->queue[left],
			sheduler) < prio_smallest)
	{
		smallest = left;
		prio_smallest = get_priority(pq, pq->queue[smallest], sheduler);
	}
	if (right < pq->size)
	{
		if (get_priority(pq, pq->queue[right], sheduler) < prio_smallest)
			smallest = right;
	}
	if (smallest != index)
	{
		swap(&pq->queue[index], &pq->queue[smallest]);
		heapify_down(pq, smallest, sheduler);
	}
}
