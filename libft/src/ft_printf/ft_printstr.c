/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:12:24 by adavila-          #+#    #+#             */
/*   Updated: 2024/02/13 11:12:24 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		str_formatter(t_format format, const char *s);

int	ft_printstr(const char *s, t_format format)
{
	ignore_flags(&format, " +#0");
	return (str_formatter(format, s));
}

int	min_str_width(const char *s, t_format *format)
{
	size_t	i;

	i = 0;
	if (!format->precision_dot)
		format->precision = ft_strlen(s);
	while (*s && i < format->precision)
	{
		i++;
		s++;
	}
	return (i);
}

int	str_formatter(t_format format, const char *s)
{
	size_t	min_w;
	size_t	printed;
	size_t	i;

	i = 0;
	printed = 0;
	if (!s)
	{
		if (format.precision_dot && format.precision < ft_strlen("(null)"))
			format.precision = 0;
		return (ft_printstr("(null)", format));
	}
	min_w = min_str_width(s, &format);
	while (min_w < format.l_offset--)
		printed += ft_putchar_f(' ');
	while (i < format.precision && *s)
	{
		printed += ft_putchar_f(*s++);
		i++;
	}
	while (min_w < format.r_offset--)
		printed += ft_putchar_f(' ');
	return (printed);
}
