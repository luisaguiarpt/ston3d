/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:39:37 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 16:39:49 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static bool	is_bonus_char(char c)
{
	if (c == 'a' || c == 'b' || c == 'c' || c == 'G' || c == '0' || c == ' '
		|| c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
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
			if (!is_bonus_char(line[i]))
				return (false);
		}
		else if (line[i] != ' '
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

char	**copy_map(char **grid)
{
	char	**dup;
	int		i;

	if (!grid)
		return (NULL);
	i = 0;
	while (grid[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (grid[i])
	{
		dup[i] = ft_strdup(grid[i]);
		if (!dup[i])
		{
			ft_free_tab(dup);
			return (NULL);
		}
		i++;
	}
	return (dup);
}
