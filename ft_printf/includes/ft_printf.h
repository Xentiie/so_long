/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:55:27 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 17:02:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"
# include <stdint.h>
# ifndef UINT_MAX
#  define UINT_MAX   4294967295U
# endif

int	ft_printf(const char *str, ...);

int	handle_c(unsigned int c);
int	handle_d(int i);
int	handle_i(int i);
int	handle_p(uintptr_t p);
int	handle_s(char *str);
int	handle_u(unsigned int i);
int	handle_uX(unsigned int i);
int	handle_x(unsigned int i);
int	parse(char c, va_list args);

#endif