/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <abenheni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:35:02 by abenheni          #+#    #+#             */
/*   Updated: 2023/06/16 19:46:00 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	parse_global_data(t_philo **philo)
{
	t_philo	*head;
	int		i;

	i = 0;
	(*philo)->data = malloc(sizeof(t_data));
	if ((*philo)->data == NULL)
		exit(1);
	(*philo)->data->start_time = get_time();
	pthread_mutex_init(&(*philo)->data->printf_mutex, NULL);
	head = (*philo);
	while (i++ < head->num_of_philo)
	{
		head->data = (*philo)->data;
		head = head->next;
	}
}

void	parsing_args(t_philo **philo, char *av[])
{
	int		i;
	int		num_of;
	t_philo	*new_philo;

	i = 0;
	num_of = ft_atoi(av[1]);
	while (i < num_of)
	{
		new_philo = addnew(av, i);
		i++;
		addfront(philo, new_philo);
	}
	new_philo->next = *philo;
	parse_global_data(philo);
}

int	check_args(int ac, char *av[])
{
	if (ac == 2)
		return (1);
	if (ac > 6 || ac < 5)
		return (0);
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return (0);
	if (av[5])
	{
		if (ft_atoi(av[5]) < 0)
			return (0);
	}
	return (1);
}
