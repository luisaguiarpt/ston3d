/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:47:53 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/09 14:33:20 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t	i;
	char	*cast;

	cast = (char *)ptr;
	i = 0;
	while (i < num)
	{
		cast[i] = value;
		i++;
	}
	return (ptr);
}
