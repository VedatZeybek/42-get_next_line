#include "get_next_line.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	find_next_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i + 1); // '\n' karakterini atla
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{

	static char	*buffer;
	char		*new_buffer;
	char		*line;
	char		*temp;
	int 		read_byte;
	int			i;
	int			j;

	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0'; // sıfırla !!! //İÇİNİ SIFIRLAMAZSAN ÇÖP DEĞERLER KALIYOR.

	}
	//printf("before buffer: %s\n", buffer);
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
			if (buffer[0] == '\0')
				return (NULL);
			line = buffer;
			buffer = NULL;
			return (line);
		}
		temp[read_byte] = '\0';
		buffer = ft_strjoin(buffer, temp);
		free(temp);
		i = find_next_line(buffer);
	}
	//printf("after buffer: %s\n", buffer);

	line = ft_substr(buffer, 0, i);


	new_buffer = ft_substr(buffer, i, ft_strlen(buffer) - i); //BAŞINDA \n KARAKTERİ BIRAKIYORSUN
	free(buffer); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	buffer = new_buffer;
	//printf("Saigono buffer %s \n", buffer);

	
	//free(new_buffer); !!BU HER ŞEYİ BOZAR
	return (line);
}


// static variable buffer kullan. bufferı oku.
// bufferın içinden next lineı bul. 

int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

	
	printf("Line: %s", get_next_line(fd)); 
	printf("Line: %s", get_next_line(fd));
	printf("Line: %s", get_next_line(fd)); 


    close(fd);
    return 0;
}
