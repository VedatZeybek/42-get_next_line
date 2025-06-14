/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:30:14 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/14 21:35:55 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int	find_next_line(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (-1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
}

char	*read_until_next_line(int fd, char *buffer)
{
	char	*old_buffer;
	int		i;
	int		read_byte;
	char	*temp;

	i = find_next_line(buffer);
	while (i <= 0)
	{
		temp = malloc(BUFFER_SIZE + 1);
		if (!temp)
			return (NULL);
		read_byte = read(fd, temp, BUFFER_SIZE);
		if (read_byte <= 0)
		{
			free(temp);
			return (buffer);
		}
		temp[read_byte] = '\0';
		old_buffer = buffer;
		buffer = ft_strjoin(old_buffer, temp);
		free(old_buffer);
		free(temp);
		if (!buffer)
			return (NULL);
		i = find_next_line(buffer);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*new_buffer;
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	i = find_next_line(buffer);
	if (i <= 0)
	{
		buffer = read_until_next_line(fd, buffer);
		if (buffer == NULL)
			return (NULL);
	}
	if (buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	i = find_next_line(buffer);
	if (i <= 0) // Newline yoksa tüm buffer'ı line olarak al
		i = ft_strlen(buffer);
	line = ft_substr(buffer, 0, i);
	new_buffer = ft_substr(buffer, i, ft_strlen(buffer) - i);
	free(buffer);
	buffer = new_buffer;

	if (buffer && buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}


int main()
{
	int fd = open("text.txt" , O_CREAT | O_RDWR, 0644);
	if (fd == -1)
	{
		printf("error\n");
		return (1);
	}
	
	char *n1 = get_next_line(fd);
	char *n2 = get_next_line(fd);
	char *n3 = get_next_line(fd);
	char *n4 = get_next_line(fd);
	
	printf("Line 1: %s\n", n1);
	printf("Lİne 2: %s\n", n2);
	printf("Line 3: %s\n", n3);
	printf("Line 4: %s\n", n4);

	if (n1) free(n1);
	if (n2) free(n2);
	if (n3) free(n3);
	if (n4) free(n4);

	close(fd);

}