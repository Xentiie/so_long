/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:23:29 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/16 18:55:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(char *nbr, char *base)
{
	int	i;
	int	base_l;
	int	value;
	int	p;

	p = 0;
	i = 0;
	value = 0;
	base_l = ft_strlen(base);
	if (!ft_checkbase(base))
		return (0);
	while (ft_getindex(base, nbr[p + 1]) != -1)
		p++;
	while (ft_getindex(base, nbr[i]) != -1)
	{
		if (ft_getindex(base, nbr[i]) == -1)
			return (value);
		value += ft_getindex(base, nbr[i]) * ft_pow(base_l, p);
		i++;
		p--;
	}
	return (value);
}
