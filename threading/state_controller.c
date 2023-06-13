#include "../includes/philo.h"

// void	state_controller(t_philo *philo)
// {
// 	while (1)
// 	{
// 		usleep(200);
// 		if (death_checker(philo) || meals_checker(philo))
// 			break;
// 	}
// }
// int	meals_checker(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i++ < philo->num_of_philo)
// 	{
// 		pthread_mutex_lock(&philo->lock_meal);
// 		if (philo->nbr_meal < philo->num_of_time_to_eat)
// 		{
// 			if (philo->key != 1)
// 			{
// 				pthread_mutex_unlock(&philo->fork);
// 				pthread_mutex_unlock(&philo->next->fork);
// 			}
// 			pthread_mutex_unlock(&philo->lock_meal);
// 			return (0);
// 		}
// 		pthread_mutex_unlock(&philo->lock_meal);
// 		philo = philo->next;
// 	}
// 	return (1);
// }