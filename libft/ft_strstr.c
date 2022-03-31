/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:24:07 by estarck           #+#    #+#             */
/*   Updated: 2022/03/16 18:08:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	istr;
	int	ifind;
	int	xfind;

	istr = 0;
	ifind = 0;
	if ((to_find[ifind]) == '\0')
		return (&str[istr]);
	while (str[istr] != '\0')
	{
		if (str[istr] == to_find[ifind])
		{
			xfind = istr;
			while (str[istr++] == to_find[ifind++])
			{
				if (to_find[ifind] == '\0')
					return (&str[xfind]);
			}
			istr = xfind;
			ifind = 0;
		}
		istr++;
	}
	return (0x0);
}
