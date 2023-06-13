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