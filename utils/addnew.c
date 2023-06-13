#include "../includes/philo.h"

t_philo	*addnew(char *av[],int i)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->key = i + 1;
	new->num_of_philo = ft_atoi(av[1]);
	new->time_eat = ft_atoi(av[3]);
	new->time_sleep = ft_atoi(av[4]);
	new->time_die = ft_atoi(av[2]);
	new->nbr_meal = -1290;
	if(av[5])
	{
		new->nbr_meal = 0;
		new->num_of_time_to_eat = ft_atoi(av[5]);
	}
	else
		new->num_of_time_to_eat = -77;
	pthread_mutex_init(&new->fork,NULL);
	pthread_mutex_init(&new->lock_death,NULL);
	pthread_mutex_init(&new->lock_meal,NULL);
	new->next = NULL;
	return (new);
}
