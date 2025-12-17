/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lundaevv <lundaevv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:34:51 by vlundaev          #+#    #+#             */
/*   Updated: 2025/12/17 22:07:45 by lundaevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_putchar(char ch)
{
	return (write(1, &ch, 1));
}

int	printf_putstr(char *str)
{
	int	len;

	len = 0;
	if (!str)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	while (*str)
	{
		if (write(1, str, 1) == -1)
			return (-1);
		len++;
		str++;
	}
	return (len);
}

int	printf_putnbr(long nb)
{
	long	res;
	int		len;
	int		count;

	len = 0;
	if (nb < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		len++;
		nb *= -1;
	}
	res = nb % 10 + '0';
	if (nb > 9)
	{
		count = printf_putnbr(nb / 10);
		if (count == -1)
			return (-1);
		len += count;
	}
	if (write(1, &res, 1) == -1)
		return (-1);
	len++;
	return (len);
}

int	printf_putnbr_hexa(unsigned long nb, char up)
{
	int		len;
	int		mod;
	int		count;
	char	*base;

	len = 0;
	if (up == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (nb > 15)
	{
		count = printf_putnbr_hexa((nb / 16), up);
		if (count == -1)
			return (-1);
		len += count;
	}
	mod = nb % 16;
	if (write(1, &base[mod], 1) == -1)
		return (-1);
	len++;
	return (len);
}

int	printf_putptr(void *ptr)
{
	int	len;
	int	count;

	len = 0;
	if (ptr == NULL)
		return (printf_putstr("(nil)"));
	if (printf_putstr("0x") == -1)
		return (-1);
	len += 2;
	count = printf_putnbr_hexa((unsigned long)ptr, 'x');
	if (count == -1)
		return (-1);
	len += count;
	return (len);
}
