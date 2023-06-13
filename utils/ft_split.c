#include "../includes/philo.h"

static int	countwords(char *s, char c)
{
	int	i;
	int	counter;
	int	flag;

	i = 0;
	counter = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			counter++;
		}
		else if (s[i] == c)
		{
			flag = 0;
		}
		i++;
	}
	return (counter);
}

static	char	*allocate_word(const char *s, char c)
{
	char	*w;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	w = malloc(i * sizeof(char) + 1);
	if (!w)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		w[i] = s[i];
		i++;
	}
	w[i] = '\0';
	return (w);
}

static char	**ft_free(char **tab, int i)
{
	while (i >= 0)
		free(tab[i--]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	i = countwords((char *)s, c);
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			tab[i] = allocate_word(s, c);
			if (!tab[i++])
				return (ft_free(tab, i));
			while (*s && *s != c)
				s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}