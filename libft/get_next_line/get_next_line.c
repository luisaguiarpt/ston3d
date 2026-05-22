/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:26:15 by josepedr          #+#    #+#             */
/*   Updated: 2025/05/20 13:08:36 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (fd < 0 || fd > 1024)
		return (NULL);
	line = NULL;
	line = join_string(line, buffer);
	while (!has_new_line(buffer))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0 || !buffer[0])
		{
			shift(buffer);
			free(line);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		line = join_string(line, buffer);
	}
	shift(buffer);
	return (line);
}
