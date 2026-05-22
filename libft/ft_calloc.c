/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:43:15 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/14 10:47:48 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*array;

	i = 0;
	array = malloc(count * size);
	if (!array)
		return (NULL);
	while (i < count * size)
	{
		array[i] = 0;
		i++;
	}
	return ((void *)array);
}
