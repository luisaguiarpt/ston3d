/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:36:33 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/11 18:07:16 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*cast1;
	unsigned char	*cast2;

	cast1 = (unsigned char *)s1;
	cast2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (cast1[i] != cast2[i])
			return (cast1[i] - cast2[i]);
		i++;
	}
	return (0);
}
