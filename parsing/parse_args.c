#include "../includes/philo.h"

void	parsing_args(t_philo **philo,char *av[], int ac)
{
	int	i;
	int	num_of;
	t_philo	*new_philo;

	i = 0;
	num_of = ft_atoi(av[1]);
	while (i < num_of)
	{
		new_philo = addnew(av,i);
		i++;
		addfront(philo, new_philo);
	}
	new_philo->next = *philo;
}

