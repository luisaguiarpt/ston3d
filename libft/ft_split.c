/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:41:54 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/17 16:02:35 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	countwords(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static char	*cpyword(const char *str, char c)
{
	int		i;
	int		len;
	char	*word;

	if (!str)
		return (NULL);
	i = 0;
	len = 0;
	while (str[len] != c && str[len] != 0)
		len++;
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

static char	**memlib(char **array, int index)
{
	int	i;

	i = 0;
	if (!array)
		return (NULL);
	while (i < index)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**array;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	array = malloc((countwords(str, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	while (i < countwords(str, c))
	{
		while (str[j] == c && str[j])
			j++;
		array[i] = cpyword(&str[j], c);
		if (!array[i])
			return (memlib(array, i));
		while (str[j] != c && str[j])
			j++;
		i++;
	}
	if (array)
		array[i] = 0;
	return (array);
}
/*
#include <stdio.h>

int	main(void)
{
	//char	*str = "    Hello    world  ";
	//char	c = ' ';
	char	**array = ft_split("^^^1^^2a,^^^^3^^^^--h^^^^", '^');
	int		i = 0;
	while (array[i])
	{
		printf("%s", array[i]);
		i++;
	}
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}
*/
