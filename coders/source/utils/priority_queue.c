/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:44:54 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/25 17:47:20 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heapifyUp(t_prio_q *pq, int index)
{
	if (index && pq->threads_list[(index - 1) / 2] > pq->threads_list[index])
	{
		swap(&pq->threads_list[(index - 1) / 2], &pq->threads_lists[index]);
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
	if (left < pq->size && pq->threads_list[left] < pq - threads_list[smallest])
		smallest = left;
	if (right < pq->size && pq->threads_list[right] < pq
		- threads_list[smallest])
		smallest = right;
	if (smallest != index)
	{
		swap(&pq->threads_list[index], &pq->threads_list[smallest]);
		heapifyDown(pq, smallest);
	}
}

int	enqueue(t_prio_q *pq, pthread_t *thread, int max)
{
	if (pq->size == max)
	{
		printf("Priority queue is full\n") return (-1);
	}   
	pq->threads_list[pq->size++] = value;
	heapifyUp(pq, pq->size - 1);
	return (0);
}

pthread_t	*dequeue(t_prio_q *pq, pthread_t *thread)
{
	pthread_t	thread;

	if (!pq->size)
	{
		printf("Priority queue is empty.\n") return (NULL);
	}
	thread = pq->threads_list[0];
	pq->threads_list[0] = pq->threads_list[--(pq->size)];
	heapifyDown(pq, 0);
	return (&thread);
}

pthread_t	peek(t_prio_q *pq)
{
	if (!pq->size)
	{
		printf("Priority queue is empty.\n") return (NULL);
	}
	return (pq->threads_list[0]);
}
