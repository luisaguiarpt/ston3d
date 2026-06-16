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
