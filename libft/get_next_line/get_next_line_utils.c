/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:41:18 by josepedr          #+#    #+#             */
/*   Updated: 2025/05/19 14:04:52 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	string_cat(char *new, char *line, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (line && line[i])
	{
		new[i] = line[i];
		i++;
	}
	j = 0;
	while (buffer [j] != '\n' && buffer[j])
		new[i++] = buffer[j++];
	if (buffer[j] == '\n')
		new[i++] = '\n';
	new[i] = 0;
}

char	*join_string(char *line, char *buffer)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (line)
		while (line[i])
			i++;
	while (buffer[j] != '\n' && buffer[j])
		j++;
	new = malloc(i + j + (buffer[j] == '\n') + 1);
	if (!new)
	{
		free(line);
		return (NULL);
	}
	string_cat(new, line, buffer);
	if (line)
		free(line);
	return (new);
}

void	shift(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[j + i])
	{
		buffer[j] = buffer[j + i];
		j++;
	}
	while (j < BUFFER_SIZE)
	{
		buffer[j] = 0;
		j++;
	}
}

int	has_new_line(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '\n')
			return (1);
		buffer++;
	}
	return (0);
}
