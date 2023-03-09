/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrolova <afrolova@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:35:31 by afrolova          #+#    #+#             */
/*   Updated: 2022/11/18 12:17:48 by afrolova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char *get_next_line(int fd)
{
    int     	i = 0;
    int			rd = 0;
    char    	character;
	char 		*buffer;

    if (BUFFER_SIZE <= 0)
		return(NULL);
	buffer = malloc(sizeof(char) * 10000);
	if(!buffer)
		return(free(buffer), NULL);
    while ((rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
    {
        buffer[i++] = character;
		if (character == '\n')
            break;
    }
    if ((!buffer[i - 1] && !rd) || rd == -1)
    {
        free(buffer);
        return (NULL);
    }
    buffer[i] =  '\0';
    return(buffer);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	(void)argc;
	fd = open((argv[1]), O_RDONLY);
	if (fd <= 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		//line = (char *)malloc(sizeof(*line) * 1);
		line = get_next_line(fd);
		//printf("|%s|\n", line);
		//i++;
	}
	free(line);
	close(fd);
	return (0);
}
