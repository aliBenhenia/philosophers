/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <abenheni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:35:28 by abenheni          #+#    #+#             */
/*   Updated: 2023/06/16 19:35:29 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_usec / 1000 + (tv.tv_sec * 1000);
	return (time);
}

void	custom_sleep(int ms)
{
	unsigned long	time;

	time = get_time();
	while (get_time() - time < (unsigned long)ms)
		usleep(200);
}
