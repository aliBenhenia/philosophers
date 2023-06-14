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

