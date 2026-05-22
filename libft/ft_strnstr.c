/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:02:17 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/11 17:35:19 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	ptr = (char *)haystack;
	i = 0;
	if (needle[i] == 0)
		return (ptr);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while ((j + i) < len && haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return (&ptr[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
