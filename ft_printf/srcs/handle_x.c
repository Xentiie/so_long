/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/17 15:16:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void	convert(unsigned int num, int *i)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (num >= 16)
	{
		convert(num / 16, i);
		convert(num % 16, i);
	}
	else
	{
		if (num >= '0' && num <= '9')
			ft_putchar_fd(hexa[num], 1);
		else
			ft_putchar_fd(hexa[num], 1);
		(*i)++;
	}
}

int	handle_x(unsigned int i)
{
	int	j;

	j = 0;
	if (i == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	else
		convert(i, &j);

	return (j);
}
