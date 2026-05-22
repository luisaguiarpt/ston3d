/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:50:01 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/14 10:55:05 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	char	*dup;
	int		size;
	int		i;
	char	*cast;

	if (!str)
		return (NULL);
	i = 0;
	cast = (char *)str;
	size = ft_strlen(str);
	dup = malloc((size + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (str[i] != '\0')
	{
		dup[i] = cast[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
