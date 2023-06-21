/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <abenheni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:34:53 by abenheni          #+#    #+#             */
/*   Updated: 2023/06/21 22:48:23 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_message(t_philo *ph, char *str)
{
	pthread_mutex_lock(&ph->data->printf_mutex);
	printf("%ld %d %s\n", get_time() - ph->data->start_time, ph->key, str);
	pthread_mutex_unlock(&ph->data->printf_mutex);
}

void	*call_back(void *arg)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)arg;
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

int	threads_creater(t_philo	**ph)
{
	int			i;
	t_philo		*philo;

	philo = *ph;
	i = 0;
	while (i++ < philo->num_of_philo)
	{
		philo->last_time_eat = philo->data->start_time;
		philo = philo->next;
	}
	i = 0;
	while (i++ < philo->num_of_philo)
	{
		if (pthread_create(&philo->thread, NULL, call_back, philo) == -1)
		{
			write(2, "error\n", 7);
			return (-1);
		}
		if (pthread_detach(philo->thread) == -1)
			return (-1);
		philo = philo->next;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo	*philo;

	philo = NULL;
	if (check_args(ac, av) == 0)
	{
		write(2, "invalid argument\n", 18);
		return (0);
	}
	if (parsing_args(&philo, av) == -1)
	{
		write(2, "error\n", 6);
		return (0);
	}
	if (threads_creater(&philo) == -1)
	{
		write(2, "error\n", 6);
		return (0);
	}
	state_controller(philo);
	return (0);
}
