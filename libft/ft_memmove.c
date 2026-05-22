/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:51:46 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/10 14:15:27 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	size_t	i;
	char	*src_cast;
	char	*dest_cast;

	i = 0;
	if (!dest && !src)
		return (NULL);
	src_cast = (char *)src;
	dest_cast = (char *)dest;
	if (dest < src)
		ft_memcpy(dest, src, num);
	else if (dest > src)
	{
		i = num;
		while (i > 0)
		{
			dest_cast[i - 1] = src_cast[i - 1];
			--i;
		}
	}
	return (dest);
}
/*
#include <stdio.h>

int main() {
    char str[] = "Hello, world!";
    
    ft_memmove(str + 7, str, 5);
    str[12] = '\0';

    printf("%s\n", str);
    return 0;
}
*/
