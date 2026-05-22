/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:33:25 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/11 16:03:09 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*cast;
	size_t			i;

	cast = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (cast[i] == (unsigned char)c)
			return ((void *)&cast[i]);
		i++;
	}
	return (NULL);
}
