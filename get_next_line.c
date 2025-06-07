#include "get_next_line.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{

	static char	*buffer;
	char		*line;
	int 		read_byte;
	int			i;
	int			j;

	buffer = malloc(BUFFER_SIZE + 1);
	line = malloc(BUFFER_SIZE + 1);
	read_byte = read(fd, buffer, BUFFER_SIZE);
	i = 0;
	buffer[read_byte] = '\0'; //void *dest_buufferda must be modifiable value hatası veriyor
	printf("buffer: %s\n", buffer);
	while (buffer && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	j = 0;
	while (buffer[j + i])
	{
		buffer[j] = buffer[j + i];
		j++;
	}
	buffer[i + j] = '\0';
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
	
	printf("read result: %s \n", get_next_line(fd));
	printf("read result: %s \n", get_next_line(fd));

	//printf("dest buffer : %s \n", 	get_next_line(fd)

    close(fd);
    return 0;
}