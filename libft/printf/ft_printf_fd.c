/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:05:56 by josepedr          #+#    #+#             */
/*   Updated: 2025/05/19 16:57:43 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	fill_placeholder_fd(int fd, char c, va_list args)
{
	int	counter;

	counter = 0;
	if (c == 'c')
		counter += ft_putcharfd(fd, va_arg(args, int));
	if (c == 's')
		counter += ft_putstrfd(fd, va_arg(args, char *));
	if (c == 'p')
		counter += print_pointer(va_arg(args, unsigned long));
	if (c == 'd' || c == 'i')
		counter += ft_putnbrfd(fd, va_arg(args, int));
	if (c == 'u')
		counter += ft_unsigned_putnbrfd(fd, va_arg(args, unsigned int));
	if (c == 'x')
		counter += ft_hex_putnbr_lower(va_arg(args, long));
	if (c == 'X')
		counter += ft_hex_putnbr_upper(va_arg(args, long));
	if (c == '%')
		counter += ft_putcharfd(fd, '%');
	return (counter);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	if (!format)
		return (-1);
	if (!*format)
		return (0);
	va_start (args, format);
	while (format[i])
	{
		if (format[i] == '%')
			counter += fill_placeholder_fd(fd, format[++i], args);
		else
			counter += ft_putcharfd(fd, format[i]);
		i++;
	}
	va_end (args);
	return (counter);
}
/*

#include <stdio.h>
int	main(void)
{
	char			*str = "Hello";
	char			c = 'b';
	int				i = 2147483647;
	int				x = -1;
	unsigned int	u = 4294967295;
	char			*p = NULL;
	int	a = ft_printf("the string is: %s, char is: %c, int is: %i, %% test, 
	unsigned max: %u, hex test: %x, ptr adrress: %p\n", str, c, i, u, x, p);
	printf("%d\n", a);
	int	b = printf("the string is: %s, char is: %c, int is: %i, %% test, 
	unsigned max: %u, hex test: %x, ptr address: %p\n", str, c, i, u, x, p);
	printf("%d\n", b);
	return (0);
}
*/
