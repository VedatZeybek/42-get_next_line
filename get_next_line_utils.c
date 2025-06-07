#include <stdlib.h>

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*result;
	size_t	total;
	size_t	i;

	total = count * size;
	result = (unsigned char *)malloc(total);
	if (!result)
		return (NULL);
	i = 0;
	while (i < total)
	{
		result[i] = 0;
		i++; 
	}
	result[i] = '\0';
	return	((void *)result);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*result;
	size_t		j;
	size_t		i;

	result = malloc(((ft_strlen(s1) + ft_strlen(s2))) + 1);
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	while (j < ft_strlen(s1))
	{
		result[j] = s1[j];
		j++;
	}
	while (i < ft_strlen(s2))
	{
		result[j] = s2[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = start;
	j = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (len == 0 || i >= ft_strlen(s))
	{
		str = ft_calloc(1, 1);
		return (str);
	}
	str = malloc((len * sizeof(char)) + 1);
	if (!str)
		return (NULL);
	while (i < start + len && j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
