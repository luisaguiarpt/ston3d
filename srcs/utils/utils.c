/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:40:33 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 16:40:34 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else
		return (false);
}

int	absolute_value(int n)
{
	if (n >= 0)
		return (n);
	else
		return (-n);
}

int	rgb_to_int(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	exit_error(t_core *core, char *message)
{
	free_core(core);
	ft_printf("Error\n%s", message);
	exit(EXIT_FAILURE);
}
