/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:13:59 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/31 16:28:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

typedef enum e_logging
{
	QUIET,
	MAINCALLS,
	VERBOSE
}	t_logging;

void	ft_set_logging(t_logging log_level);
int		ft_log(t_logging log_level, char *str, ...);

#endif