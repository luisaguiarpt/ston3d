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
	int	len;

	len = ft_strlen(line) - 1;
	if (len < 4)
		return (false);
	while (len > 0 && is_space(line[len]))
		len--;
	if (line[len - 3] != '.'
		|| line[len - 2] != 'x'
		|| line[len - 1] != 'p'
		|| line[len] != 'm')
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

static bool	is_bonus_char(char c)
{
	if (c == 'a' || c == 'b' || c == 'c' || c == 'G')
		return (true);
	else
		return (false);
}

bool	is_valid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (BONUS)
		{
			if (is_bonus_char(line[i]))
				return (true);
		}
		if (line[i] != ' '
			&& line[i] != '0'
			&& line[i] != '1'
			&& line[i] != 'N'
			&& line[i] != 'S'
			&& line[i] != 'E'
			&& line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}

void	remove_newline(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
