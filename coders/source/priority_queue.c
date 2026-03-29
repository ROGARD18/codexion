/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogard-antoine <rogard-antoine@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:44:54 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/28 12:37:08 by rogard-anto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	heapify_up(t_prio_q *pq, int index, char *mode)
{
	int	parent;

	if (index == 0)
		return ;
	parent = (index - 1) / 2;
	if (pq->td[pq->queue[index]].last_compile_start < 
        pq->td[pq->queue[parent]].last_compile_start)
	{
		swap(&pq->queue[index], &pq->queue[parent]);
		heapify_up(pq, parent, mode);
	}
}

void	heapify_down(t_prio_q *pq, int index, char *mode)
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
		heapify_down(pq, smallest, mode);
	}
}

int	enqueue(t_prio_q *pq, int coder_index, int number_of_coders, char *mode)
{
	if (pq->size >= number_of_coders)
	{
		printf("NOT ENQUE !");
		return (-1);
	}
	printf("pq->size = %d ", pq->size);
	pq->queue[pq->size] = coder_index;
	heapify_up(pq, pq->size, mode);
	pq->size++;
	return (0);
}

int	dequeue(t_prio_q *pq, char *mode)
{
	if (pq->size == 0)
		return (-1);
	pq->queue[0] = pq->queue[pq->size - 1];
	pq->size--;
	heapify_down(pq, 0, mode);
	return (0);
}

int	peek(t_prio_q *pq)
{
	if (pq->size == 0)
		return (-1);
	return (pq->queue[0]);
}
