/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:39:24 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 16:39:49 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

bool	is_cub_file(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len < 4)
		return (false);
	if (line[len - 4] != '.'
		|| line[len - 3] != 'c'
		|| line[len - 2] != 'u'
		|| line[len - 1] != 'b')
		return (false);
	else
		return (true);
}

bool	is_xpm_file(char *line)
{
	int	start;
	int	end;
	int	len;

	start = 0;
	end = ft_strlen(line) - 1;
	while (is_space(line[start]))
		start++;
	while (is_space(line[end]) && end > start)
		end--;
	len = end - start + 1;
	if (len < 4)
		return (false);
	if (line[end - 3] != '.'
		|| line[end - 2] != 'x'
		|| line[end - 1] != 'p'
		|| line[end] != 'm')
		return (false);
	else
		return (true);
}

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line[i])
		return (true);
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else
			return (false);
	}
	return (true);
}

void	get_map_width(t_core *core)
{
	int	i;
	int	j;

	i = 0;
	while (core->map.grid[i])
	{
		j = 0;
		while (core->map.grid[i][j])
			j++;
		if (j > core->map.width)
			core->map.width = j;
		i++;
	}
}

void	remove_newline(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
