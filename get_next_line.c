#include "get_next_line.h"
#include <stddef.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;
	int			bytes_read;
	int			i;
	int			j;

	if (!buffer)
		buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return NULL;

	bytes_read = read(fd, buffer, BUFFER_SIZE);

	if (bytes_read <= 0)  
	{
		free(line);
		return NULL;
	}
	buffer[bytes_read] = '\0';

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}

	line[i] = '\0';  
	
	j = 0;
	if (buffer[i] == '\n')
	{
		while (buffer[i + j + 1] != '\0')
		{
			buffer[i] = buffer[i + j + 1];
			j++;
		}
	}
 return line;  // Okunan satırı döndür
}


#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char *line = get_next_line(fd);
    while (line)  // Dosyanın sonuna kadar her satırı oku
    {
        printf("%s\n", line);
        free(line);  // Okunan satırı serbest bırak
        line = get_next_line(fd);
    }

    close(fd);  // Dosyayı kapat
    return 0;
}