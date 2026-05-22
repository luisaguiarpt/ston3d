/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:51:03 by ldias-da          #+#    #+#             */
/*   Updated: 2025/04/15 13:38:03 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Creates a new string and allows freeing the input
 * @param	s1, s2	Input strings to join
 * @param	flags	0: free s1	1: free s2	2: free both
 * @return	Pointer to newly created joined string
 * @notes	If no string is to be freed, use ft_strjoin
 */
char	*ft_strjoin2(char *s1, char *s2, int flag)
{
	char	*new;
	char	*ptr;
	char	*s1_p;
	char	*s2_p;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (s1);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	ptr = new;
	s1_p = s1;
	s2_p = s2;
	while (s1 && *s1)
		*new++ = *s1++;
	while (s2 && *s2)
		*new++ = *s2++;
	*new = 0;
	if (flag == 0 || flag == 2)
		free(s1_p);
	if (flag == 1 || flag == 2)
		free(s2_p);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*new;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	ptr = new;
	while (*s1)
		*new++ = *s1++;
	while (*s2)
		*new++ = *s2++;
	*new = 0;
	return (ptr);
}
