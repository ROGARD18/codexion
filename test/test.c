/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrogard <anrogard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:40:09 by anrogard          #+#    #+#             */
/*   Updated: 2026/03/16 00:44:01 by anrogard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// void* myThreadFunc(void* arg) {
//     (void)arg;
//     while(1) {
//         printf("Thread is running...\n");
//         sleep(1);
//     }
//     return NULL;
// }

// int main() {
//     pthread_t thread;
//     pthread_create(&thread, NULL, myThreadFunc, NULL);
//     sleep(5);
//     //Requesting to cancel the thread after 5 seconds. 
//     pthread_cancel(thread);
//     // Wait for the thread to terminate
//     pthread_join(thread, NULL);  

//     printf("Main thread finished.\n");
//     return 0;
// }