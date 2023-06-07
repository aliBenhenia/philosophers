#include "philo.h"

void	addfront(t_philo **head, t_philo *new)
{
	t_philo	*current;
	if((*head) == NULL)
	{
		*(head) = new;
		new->next = NULL;
		return ;
	}
	current = *(head);
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_philo	*addnew(char *av[],int i)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->key = i + 1;
	new->num_of_philo = atoi(av[1]);
	new->time_eat = atoi(av[3]);
	new->time_sleep = atoi(av[4]);
	new->time_die = atoi(av[2]);
	new->nbr_meal = -1290;
	if(av[5])
	{
		new->nbr_meal = 0;
		new->num_of_time_to_eat = atoi(av[5]);
	}
	pthread_mutex_init(&new->fork,NULL);
	pthread_mutex_init(&new->lock_death,NULL);
	pthread_mutex_init(&new->lock_meal,NULL);
	new->next = NULL;
	return (new);
}

void	parsing_args(t_philo **philo,char *av[])
{
	int	i;
	int	num_of;
	t_philo	*new_philo;

	i = 0;
	num_of = atoi(av[1]);
	while (i < num_of)
	{
		new_philo = addnew(av,i);
		i++;
		addfront(philo, new_philo);
	}
	new_philo->next = *philo;
}

unsigned long get_time()
{
	struct timeval tv;
	unsigned long time;
	gettimeofday(&tv,NULL);
	time = tv.tv_usec /1000 + (tv.tv_sec * 1000);
	return(time);
}


unsigned long start_time;
int state = 1;
pthread_mutex_t printf_mutex;
pthread_mutex_t meal_mutex;

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
	{
		usleep(100);
	}
}

void *routine(t_philo *philo)
{
	while (1)
	{
		if (philo->key % 2)
			usleep(100);
		if(philo->num_of_philo == 1)
			break;
		pthread_mutex_lock(&philo->fork);
		printf_message(philo,"has taken a fork");
		pthread_mutex_lock(&philo->next->fork);
		printf_message(philo,"has taken a fork");
		printf_message(philo,"is eating");
		pthread_mutex_lock(&philo->lock_death);
		philo->last_time_eat = get_time();
		pthread_mutex_unlock(&philo->lock_death);
		philo->nbr_meal++;
		custom_sleep(philo->time_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		printf_message(philo,"is sleeping");
		custom_sleep(philo->time_sleep); // time to sleep
		printf_message(philo,"is thinking");
	}
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
		// pthread_mutex_lock(&philo->my_lock);
		if (philo->nbr_meal != philo->num_of_time_to_eat)
			return (0);
		// pthread_mutex_unlock(&philo->my_lock);
		philo = philo->next;
	}
	return (1);
}

void	ft_create_threads(t_philo **ph)
{
	int	i;
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
		pthread_create(&philo->thread,NULL,(void *)routine,philo);
		i++;
		pthread_detach(philo->thread);
		philo = philo->next;
	}
	while (state)
	{	

		if (death_checker(philo) || meals_checker(philo))
			break;
		usleep(100);
	}
}

int	check_args(int ac, char *av[])
{
	if(ac > 6 || ac < 5)
		return 0;
	if(atoi(av[1]) < 0 || atoi(av[2]) < 0 || atoi(av[3]) < 0 || atoi(av[4]) < 0 )
		return 0;
	if(av[5])
	{
		if(atoi(av[5]) < 0)
			return 0;
	}
	return 1;
}

int main(int ac, char *av[])
{ 
   t_philo	*philo;
   philo = NULL;
   if(check_args(ac,av) == 0)
		return (1);
   parsing_args(&philo,av);
	start_time = get_time();
	pthread_mutex_init(&printf_mutex,NULL);
	pthread_mutex_init(&meal_mutex,NULL);
   ft_create_threads(&philo);

    // display(philo);
   return 0;
}
