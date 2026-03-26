/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:44:54 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/26 18:50:13 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	heapifyUp(t_prio_q *pq, int index)
{
	if (index && pq->threads_queue[(index - 1) / 2] > pq->threads_queue[index])
	{
		swap(&pq->threads_queue[(index - 1) / 2], &pq->threads_queue[index]);
		heapifyUp(pq, index - 1);
	}
}

void	heapifyDown(t_prio_q *pq, int index)
{
	int	smallest;
	int	left;
	int	right;

	smallest = index;
	left = 2 * index - 1;
	right = 2 * index + 2;
	if (left < pq->size
		&& pq->threads_queue[left] < pq->threads_queue[smallest])
		smallest = left;
	if (right < pq->size
		&& pq->threads_queue[right] < pq->threads_queue[smallest])
		smallest = right;
	if (smallest != index)
	{
		swap(&pq->threads_queue[index], &pq->threads_queue[smallest]);
		heapifyDown(pq, smallest);
	}
}

int	enqueue(t_prio_q *pq, pthread_t *thread, int max)
{
	if (pq->size == max)
	{
		printf("Priority queue is full\n");
		return (-1);
	}
	pq->threads_queue[pq->size++] = *thread;
	heapifyUp(pq, pq->size - 1);
	return (0);
}

int	dequeue(t_prio_q *pq)
{
	pthread_t	thread;

	if (!pq->size)
	{
		printf("Priority queue is empty.\n");
		return (-1);
	}
	thread = pq->threads_queue[0];
	pq->threads_queue[0] = pq->threads_queue[--(pq->size)];
	heapifyDown(pq, 0);
	return (0);
}

pthread_t	peek(t_prio_q *pq)
{
	if (!pq->size)
	{
		printf("Priority queue is empty.\n");
		return ((pthread_t)NULL);
	}
	return (pq->threads_queue[0]);
}
