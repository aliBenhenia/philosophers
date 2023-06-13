#include "../includes/philo.h"

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
    {
        write(2, "invalid argument\n",18);
        exit(1);
    }
	return ((int)r * sign);
}