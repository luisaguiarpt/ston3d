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

int	ft_putstrfd(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstrfd(fd, "(null)"));
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putcharfd(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putnbrfd(int fd, int n)
{
	int	counter;

	counter = 0;
	if (n == -2147483648)
	{
		write(fd, "-2", 2);
		counter += 2;
		counter += ft_putnbrfd(fd, 147483648);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		counter++;
		counter += ft_putnbrfd(fd, -n);
	}
	else if (n > 9)
	{
		counter += ft_putnbrfd(fd, n / 10);
		counter += ft_putnbrfd(fd, n % 10);
	}
	else
		counter += ft_putcharfd(fd, n + '0');
	return (counter);
}

int	ft_unsigned_putnbrfd(int fd, unsigned int n)
{
	int	counter;

	counter = 0;
	if (n > 9)
	{
		counter += ft_unsigned_putnbrfd(fd, n / 10);
		counter += ft_unsigned_putnbrfd(fd, n % 10);
	}
	else
		counter += ft_putcharfd(fd, n + '0');
	return (counter);
}
