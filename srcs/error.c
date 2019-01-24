/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:41:28 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/10 14:35:56 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_lem_in_error(t_lem_in *lem_in, char *err_message)
{
	ft_printf("ERROR %s\n", err_message);
	ft_lem_in_free(lem_in);
	exit(1);
}

void	ft_parse_error(t_lem_in *lem_in)
{
	if (!lem_in->start)
		ft_lem_in_error(lem_in, "no start");
	if (!lem_in->end)
		ft_lem_in_error(lem_in, "no end");
}
