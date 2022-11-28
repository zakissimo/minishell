/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:19:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/15 18:46:50 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	loop(const char *str, t_list *head, va_list ap, t_utils *args)
{
	size_t	len;

	len = 0;
	while (str[args->i])
	{
		if (head && args->flag)
		{
			args->n = ((t_node *)(head->content))->i;
			args->c = ((t_node *)(head->content))->flag;
			head = head->next;
			args->flag = 0;
		}
		if (args->i == args->n && !args->flag)
		{
			args->flag = 1;
			len += type_check(args->c, ap);
			args->i++;
		}
		else
			len += ft_putchar_fd(str[args->i], 1);
		args->i++;
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		ret;
	t_utils	args;
	t_list	*head;

	args.i = 0;
	args.n = 0;
	args.flag = 1;
	head = arg_lst((char *)str, NULL);
	va_start(ap, str);
	ret = (loop((char *)str, head, ap, &args));
	va_end(ap);
	ft_lstclear(&head, free);
	return (ret);
}
