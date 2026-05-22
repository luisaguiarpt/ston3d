/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:56:20 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/15 16:29:10 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cast1;
	unsigned char	*cast2;

	if (!s1 || !s2)
		return (INT_MAX);
	cast1 = (unsigned char *)s1;
	cast2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < (n - 1) && cast2[i] && cast1[i] == cast2[i])
	{
		i++;
	}
	return (cast1[i] - cast2[i]);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%d", ft_strncmp("", "", 0));
	return (0);
}
*/
