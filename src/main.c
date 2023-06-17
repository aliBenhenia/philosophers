/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <abenheni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:34:53 by abenheni          #+#    #+#             */
/*   Updated: 2023/06/16 19:40:50 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	printf_message(t_philo *ph, char *str)
{
	pthread_mutex_lock(&ph->data->printf_mutex);
	printf("%ld %d %s\n", get_time() - ph->data->start_time, ph->key, str);
	pthread_mutex_unlock(&ph->data->printf_mutex);
	return (1);
}

void	*call_back(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->key % 2 == 0)
	{
		while (i++ <= 500)
			usleep(1);
	}
	simulator(philo);
	return (NULL);
}

int	death_checker(t_philo *philo)
{
	int	i;

	i = 0;
	usleep(200);
	while (i++ < philo->num_of_philo)
	{
		pthread_mutex_lock(&philo->lock_death);
		if (get_time() - philo->last_time_eat >= (unsigned long)philo->time_die)
		{
			pthread_mutex_lock(&philo->data->printf_mutex);
			printf("%ld %d died\n",
				get_time() - philo->data->start_time, philo->key);
			return (1);
		}
		pthread_mutex_unlock(&philo->lock_death);
		philo = philo->next;
	}
	return (0);
}

void	threads_creater(t_philo	**ph)
{
	int			i;
	t_philo		*philo;

	philo = *ph;
	i = 0;
	while (i++ < philo->num_of_philo)
	{
		philo->last_time_eat = get_time();
		philo = philo->next;
	}
	i = 0;
	while (i++ < philo->num_of_philo)
	{
		pthread_create(&philo->thread, NULL, (void *)call_back, philo);
		pthread_detach(philo->thread);
		philo = philo->next;
	}
}

int	main(int ac, char *av[])
{
	t_philo	*philo;

	philo = NULL;
	if (check_args(ac, av) == 0)
		return (1);
	parsing_args(&philo, av);
	threads_creater(&philo);
	state_controller(philo);
	return (0);
}
