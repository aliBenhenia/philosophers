/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <abenheni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:35:06 by abenheni          #+#    #+#             */
/*   Updated: 2023/06/18 19:06:03 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H
# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<pthread.h>
# include<time.h>
# include <sys/time.h>

typedef struct t_data
{
	pthread_mutex_t	printf_mutex;
	unsigned long	start_time;
}t_data;

# define NOT_PASSED -77

typedef struct t_philo
{
	int				key;
	int				num_of_philo;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				num_of_time_to_eat;
	unsigned long	last_time_eat;
	int				nbr_meal;
	pthread_mutex_t	fork;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	lock_meal;
	pthread_t		thread;
	t_data			*data;
	struct t_philo	*next;
}t_philo;

char			**ft_split(char const *s, char c);
int				ft_atoi(const char *s);
void			addfront(t_philo **head, t_philo *new);
t_philo			*addnew(char *av[], int i);
unsigned long	get_time(void);
int				parsing_args(t_philo **philo, char *av[]);
void			custom_sleep(int ms);
void			state_controller(t_philo *philo);
int				death_checker(t_philo *philo);
int				meals_checker(t_philo *philo);
int				check_args(int ac, char *av[]);
int				meals_checker(t_philo *philo);
int				printf_message(t_philo *ph, char *str);
void			simulator(t_philo *philo);
void			free_all_recources(t_philo *philo);
#endif