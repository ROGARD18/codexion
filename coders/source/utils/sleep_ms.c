/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:54:44 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/29 19:30:02 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <codexion.h>

void sleep_ms(int milliseconds, t_thread_data *td)
{
    long long start;

    start = get_time();
    while ((get_time() - start) < milliseconds)
    {
        if (!td->alive) 
            break;
        usleep(1);
    }
}
