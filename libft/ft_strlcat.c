/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:17:03 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/17 16:01:00 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dest_len;

	if ((!dest || !src) && size == 0)
		return (0);
	i = 0;
	j = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (size + src_len);
	if (size > 0)
	{
		while (dest[i] != '\0')
			i++;
		while (src[j] != '\0' && i < size - 1)
			dest[i++] = src[j++];
		dest[i] = '\0';
	}
	return (dest_len + src_len);
}
/*
#include <stdio.h>

int	main(void)
{
	char	dest[18] = "Hello ";
	char	src[] = "World";
	size_t	result = ft_strlcat(dest, src, sizeof (dest));
	printf("%s, %zu", dest, result);
	return (0);
}
*/
