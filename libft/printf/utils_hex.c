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

int	ft_hex_putnbr_lower(int n)
{
	char			*symbols;
	int				counter;
	unsigned int	un;

	un = (unsigned int)n;
	symbols = "0123456789abcdef";
	counter = 0;
	if (un == 16)
	{
		counter = 2;
		write(1, "10", 2);
	}
	else if (un > 16)
	{
		counter += ft_hex_putnbr_lower(un / 16);
		counter += ft_hex_putnbr_lower(un % 16);
	}
	else
		counter += ft_putchar(symbols[un % 16]);
	return (counter);
}

int	ft_hex_putnbr_upper(int n)
{
	char			*symbols;
	int				counter;
	unsigned int	un;

	un = (unsigned int)n;
	symbols = "0123456789ABCDEF";
	counter = 0;
	if (un == 16)
	{
		counter = 2;
		write(1, "10", 2);
	}
	else if (un > 16)
	{
		counter += ft_hex_putnbr_upper(un / 16);
		counter += ft_hex_putnbr_upper(un % 16);
	}
	else
		counter += ft_putchar(symbols[un % 16]);
	return (counter);
}

static int	print_address(unsigned long n)
{
	char	*symbols;
	int		counter;

	symbols = "0123456789abcdef";
	counter = 0;
	if (n == 16)
	{
		counter = 2;
		write(1, "10", 2);
	}
	else if (n > 16)
	{
		counter += print_address(n / 16);
		counter += print_address(n % 16);
	}
	else
		counter += ft_putchar(symbols[n % 16]);
	return (counter);
}

int	print_pointer(unsigned long n)
{
	int	counter;

	if (!n)
		return (ft_putstr("(nil)"));
	write(1, "0x", 2);
	counter = print_address(n);
	return (counter + 2);
}
