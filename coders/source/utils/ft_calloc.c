/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 21:45:07 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/29 22:06:44 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	r;
	void	*s;

	r = nmemb * size;
	if (nmemb != 0 && r / nmemb != size)
		return (NULL);
	if (r == 0)
	{
		s = malloc(1);
		if (!s)
			return (NULL);
		return (s);
	}
	s = malloc(r);
	if (!s)
		return (NULL);
	memset(s, 0, r);
	return (s);
}
