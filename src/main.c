#include "../includes/philo.h"


unsigned long get_time()
{
	struct timeval tv;
	unsigned long time;
	gettimeofday(&tv,NULL);
	time = tv.tv_usec / 1000 + (tv.tv_sec * 1000);
	return(time);
}

unsigned long start_time;
int state = 1;
pthread_mutex_t printf_mutex;
pthread_mutex_t meal_mutex;
pthread_mutex_t sleep_mutex;

int printf_message(t_philo *ph,char *str)
{
	pthread_mutex_lock(&printf_mutex);
	printf("%ld %d %s\n",get_time() - start_time,ph->key,str);
	pthread_mutex_unlock(&printf_mutex);
	return 1;
}

void custom_sleep(int ms)
{
	unsigned long time;

	time = get_time();
	while (get_time() - time < (unsigned long)ms)
		usleep(200);
}

void *call_back(t_philo *philo)
{
	if (philo->key % 2 == 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		if (philo->nbr_meal == philo->num_of_time_to_eat && philo->key == 2)
		{
			pthread_mutex_unlock(&philo->fork);
			// pthread_mutex_unlock(&philo->next->fork);
			break;
		}
		if (philo->nbr_meal == philo->num_of_time_to_eat)
		{
			pthread_mutex_unlock(&philo->fork);
			// pthread_mutex_unlock(&philo->next->fork);
			break;
		}
		printf_message(philo,"has taken a fork");
		pthread_mutex_lock(&philo->next->fork);
		printf_message(philo,"has taken a fork");
		printf_message(philo,"is eating");
		pthread_mutex_lock(&philo->lock_death);
		philo->last_time_eat = get_time();
		pthread_mutex_unlock(&philo->lock_death);
		pthread_mutex_lock(&philo->lock_meal);
		if (philo->num_of_time_to_eat != -77)
			philo->nbr_meal++;
		pthread_mutex_unlock(&philo->lock_meal);
		custom_sleep(philo->time_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		printf_message(philo,"is sleeping");
		custom_sleep(philo->time_sleep); 
		printf_message(philo,"is thinking");
	}
	return (NULL);
}

int	death_checker(t_philo *philo)
{
	int	i;

	i = 0;
	usleep(1000);
	while (i++ < philo->num_of_philo)
	{
		pthread_mutex_lock(&philo->lock_death);
		if (get_time() - philo->last_time_eat >= (unsigned long)philo->time_die)
		{
			pthread_mutex_lock(&printf_mutex);
			printf("%ld %d died\n",get_time() - start_time,philo->key);
			return (1);
		}
		pthread_mutex_unlock(&philo->lock_death);
		philo = philo->next;
	}
	return (0);
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

void	threads_creater(t_philo	**ph)
{
	int		i;
	t_philo *philo;

	philo = *ph;
	i = 0;
	while (i < philo->num_of_philo)
	{
		philo->last_time_eat = get_time();
		philo = philo->next;
		i++;
	}
	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_create(&philo->thread,NULL,(void *)call_back,philo);
		i++;
		pthread_detach(philo->thread);
		philo = philo->next;
	}
}


int	check_args(int ac, char *av[])
{
	if (ac == 2)
		return (1);
	if(ac > 6 || ac < 5)
		return 0;
	if(ft_atoi(av[1]) < 0 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0 )
		return 0;
	if(av[5])
	{
		if(ft_atoi(av[5]) < 0)
			return 0;
	}
	return 1;
}

void	state_controller(t_philo *philo)
{
	while (1)
	{
		usleep(200);
		if (death_checker(philo) || meals_checker(philo))
			break;
	}
}

int main(int ac, char *av[])
{ 
   t_philo	*philo;
	philo = NULL;

    if(check_args(ac,av) == 0)
		return (1);
   	parsing_args(&philo,av, ac);
	start_time = get_time();
	pthread_mutex_init(&printf_mutex,NULL);
	pthread_mutex_init(&sleep_mutex,NULL);
  	threads_creater(&philo);
	state_controller(philo);
    return 0;
}
