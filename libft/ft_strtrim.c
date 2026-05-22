/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:36:03 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/17 14:44:37 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	trim(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*trimmed;

	if (!s1)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (trim(set, s1[i]))
		i++;
	while (j >= 0 && trim(set, s1[j]))
		j--;
	trimmed = ft_substr(s1, i, (j - i + 1));
	return (trimmed);
}
/*
#include <stdio.h>

int	main(void)
{
	const char	*s1 = "abbababbHello Worldbbaabab";
	const char	*set = "ab";
	printf("%s", ft_strtrim(s1, set));
	return (0);
}
*/
