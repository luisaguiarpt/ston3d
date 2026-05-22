/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:38:13 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/10 14:16:13 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (size > 0)
	{
		i = 0;
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}
/*	
#include <stdio.h>

int	main(void)
{
	char	*src = "Hello";
	char	dest[9];
	
	printf("Before: %s\n", dest);
	ft_strlcpy(dest, src, sizeof(dest));
	printf("After: %s\n", dest);
	printf("%zu", ft_strlcpy(dest, src, sizeof(dest)));
	return (0);
}
*/
