/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:24:07 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/16 09:05:07 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	type_check(char c, va_list ap)
{
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(ap, int), 1));
	if (c == 's')
		return (ft_putstr_fd(va_arg(ap, char *), 1));
	if (c == 'c')
		return (ft_putchar_fd((char)va_arg(ap, int), 1));
	if (c == '%')
		return (ft_putchar_fd('%', 1));
	if (c == 'u')
		return (ft_uputnbr_fd(va_arg(ap, unsigned int), 1));
	if (c == 'x')
		return (ft_uputnbr_base(va_arg(ap, unsigned int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_uputnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF"));
	if (c == 'p')
		return (print_addr(va_arg(ap, unsigned long)));
	if (c == 'b')
		return (ft_uputnbr_base(va_arg(ap, unsigned int), "01"));
	return (0);
}
