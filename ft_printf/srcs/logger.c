/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:21:19 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 17:02:56 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.h"
#include "ft_printf.h"
#include <stdint.h>
#include <stdarg.h>

static t_logging	g_logging_level;

void	ft_set_logging(t_logging log_level)
{
	g_logging_level = log_level;
}

int	ft_log(t_logging log_level, char *str, ...)
{
	int			i;
	va_list		args;
	int			c_count;

	va_start(args, str);
	i = 0;
	c_count = 0;
	if (log_level > g_logging_level)
		return (0);
	while (str[i])
	{
		if (str[i] == '%')
		{
			c_count += parse(str[i + 1], args);
			i++;
		}
		else
		{
			c_count++;
			ft_putchar_fd(str[i], 1);
		}
		i++;
	}
	va_end(args);
	return (c_count);
}
