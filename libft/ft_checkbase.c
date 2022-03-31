/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:17:54 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/16 18:26:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkbase(char *base)
{
	int		i;
	int		j;
	char	element_to_test;

	j = 0;
	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == 42 || base[i] == 45)
			return (0);
		element_to_test = base[i];
		j = 0;
		while (base[j] != '\0')
		{
			if (i != j && base[j] == element_to_test)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
