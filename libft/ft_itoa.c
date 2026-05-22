/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:46:20 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/15 14:02:46 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

static void	fill_str(int n, int index, char *str)
{
	if (n > 9)
		fill_str(n / 10, index - 1, str);
	str[index] = n % 10 + '0';
}

static int	countnum(int n)
{
	int	len;
	int	nb;

	nb = n;
	len = (nb < 1);
	if (nb < 0)
		nb = nb * -1;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*string;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	string = malloc((countnum(n) + 1) * sizeof(char));
	if (!string)
		return (NULL);
	if (n < 0)
		string[0] = '-';
	fill_str(n * ((n >= 1) - (n < 1)), countnum(n) - 1, string);
	string[countnum(n)] = 0;
	return (string);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s", ft_itoa(1));
	return (0);
}
*/
