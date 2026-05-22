/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:04:16 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/17 14:45:34 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *str, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!str)
		return (NULL);
	i = 0;
	result = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (i < ft_strlen(str))
	{
		result[i] = f(i, str[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}
