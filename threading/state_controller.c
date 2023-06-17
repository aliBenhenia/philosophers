/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <abenheni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:35:15 by abenheni          #+#    #+#             */
/*   Updated: 2023/06/16 19:35:16 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	state_controller(t_philo *philo)
{
	while (1)
	{
		usleep(200);
		if (death_checker(philo) || meals_checker(philo))
			break ;
	}
}

int	meals_checker(t_philo *philo)
{
	int	i;

	i = 0;
	while (i++ < philo->num_of_philo)
	{
		pthread_mutex_lock(&philo->lock_meal);
		if (philo->nbr_meal < philo->num_of_time_to_eat)
		{
			if (philo->key != 1)
			{
				pthread_mutex_unlock(&philo->fork);
				pthread_mutex_unlock(&philo->next->fork);
			}
			pthread_mutex_unlock(&philo->lock_meal);
			return (0);
		}
		pthread_mutex_unlock(&philo->lock_meal);
		philo = philo->next;
	}
	return (1);
}

void	simulator(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		if (philo->nbr_meal == philo->num_of_time_to_eat)
			break ;
		printf_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->next->fork);
		printf_message(philo, "has taken a fork");
		printf_message(philo, "is eating");
		pthread_mutex_lock(&philo->lock_death);
		philo->last_time_eat = get_time();
		pthread_mutex_unlock(&philo->lock_death);
		pthread_mutex_lock(&philo->lock_meal);
		if (philo->num_of_time_to_eat != NOT_PASSED)
			philo->nbr_meal++;
		pthread_mutex_unlock(&philo->lock_meal);
		custom_sleep(philo->time_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		printf_message(philo, "is sleeping");
		custom_sleep(philo->time_sleep);
		printf_message(philo, "is thinking");
	}
}
