/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:01:57 by josepedr          #+#    #+#             */
/*   Updated: 2025/05/06 16:34:40 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr(int n)
{
	int	counter;

	counter = 0;
	if (n == -2147483648)
	{
		write(1, "-2", 2);
		counter += 2;
		counter += ft_putnbr(147483648);
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		counter++;
		counter += ft_putnbr(-n);
	}
	else if (n > 9)
	{
		counter += ft_putnbr(n / 10);
		counter += ft_putnbr(n % 10);
	}
	else
		counter += ft_putchar(n + '0');
	return (counter);
}

int	ft_unsigned_putnbr(unsigned int n)
{
	int	counter;

	counter = 0;
	if (n > 9)
	{
		counter += ft_unsigned_putnbr(n / 10);
		counter += ft_unsigned_putnbr(n % 10);
	}
	else
		counter += ft_putchar(n + '0');
	return (counter);
}
