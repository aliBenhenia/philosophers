/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addfront.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <abenheni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:35:19 by abenheni          #+#    #+#             */
/*   Updated: 2023/06/16 19:35:20 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	addfront(t_philo **head, t_philo *new)
{
	t_philo	*current;

	if ((*head) == NULL)
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
