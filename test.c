
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		l2;
	char	*str;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (0);
	l2 = ft_strlen(s2);
	str = malloc((sizeof(char) * ft_strlen(s1)) + (sizeof(char) * l2 + 1));
	if (!str)
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	// free((void *)s1);
	return (str);
}

char	*ft_strdupi(const char *s1, int l)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (l + 1));
	if (!str)
		return (0);
	while (s1[i] && l > i)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int main(int ac, char **av)
{
    int i = 0;
    char s = 0;
    char *word;

	word = ft_strdupi("", 1);
    while(av[1][i])
    {
        if (s == 0 && (av[1][i] == '\'' || av[1][i] == '"'))
            s = av[1][i++];
        if (av[1][i] == s)
            s = 0;
        else
            word = ft_strjoin(word, ft_strdupi(&av[1][i], 1));
        i++;
    }
	if (s != 0)
	{
		printf("unmatched quote\n");
		return (0);
	}
    printf("%s\n", word);
}