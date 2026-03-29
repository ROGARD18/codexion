/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:44:54 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/29 16:26:20 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	heapify_up(t_prio_q *pq, int index, char *sheduler)
{
	int	parent;

	if (index == 0)
		return ;
	parent = (index - 1) / 2;
	if (pq->td[pq->queue[index]].last_compile_start < 
        pq->td[pq->queue[parent]].last_compile_start)
	{
		swap(&pq->queue[index], &pq->queue[parent]);
		heapify_up(pq, parent, sheduler);
	}
}

void	heapify_down(t_prio_q *pq, int index, char *sheduler)
{
	int	smallest = index;
	int	left = 2 * index + 1;
	int	right = 2 * index + 2;

	if (left < pq->size &&
        pq->td[pq->queue[left]].last_compile_start < 
        pq->td[pq->queue[smallest]].last_compile_start)
		smallest = left;
	if (right < pq->size && 
        pq->td[pq->queue[right]].last_compile_start < 
        pq->td[pq->queue[smallest]].last_compile_start)
		smallest = right;
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
		printf("size = %d\n", pq->size);
		return (-1);
	}
	printf("pq->size = %d ", pq->size);
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
