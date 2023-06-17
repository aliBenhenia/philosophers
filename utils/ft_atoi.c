/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <abenheni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:35:25 by abenheni          #+#    #+#             */
/*   Updated: 2023/06/16 19:35:26 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_error(void)
{
	write(2, "invalid argument\n", 18);
	exit(1);
}

int	ft_atoi(const char *s)
{
	long	r;
	int		sign;

	r = 0;
	sign = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = sign * -1;
		s++;
	}
	while ((*s >= '0' && *s <= '9'))
	{
		r = r * 10 + *s - '0';
		s++;
	}
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s != '\0')
		print_error();
	return ((int)r * sign);
}
