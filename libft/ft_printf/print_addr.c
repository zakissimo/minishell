/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_addr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:16:20 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/15 18:45:59 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_addr(unsigned long c)
{
	int	len;

	len = 0;
	if (!c)
		len += ft_putstr_fd("(nil)", 1);
	else
	{
		len += ft_putstr_fd("0x", 1);
		len += ft_uputnbr_base(c, "0123456789abcdef");
	}
	return (len);
}
