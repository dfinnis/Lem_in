/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lem_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 17:09:47 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/09 17:09:48 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_parse_ants(t_lem_in *lem_in);
{

}

void	ft_parse_comment(t_lem_in *lem_in);
{
	
}

void	ft_parse_room(t_lem_in *lem_in);
{
	
}

void	ft_parse_link(t_lem_in *lem_in);
{
	
}

void	ft_lem_in_parse(t_lem_in *lem_in);
{
	while (get_next_line(0, &lem_in->line) == 1)
	{
		if ()
			ft_parse_ants(lem_in->line);
		else if ()
			ft_parse_comment(lem_in->line);
		else if ()
			ft_parse_room(lem_in->line);
		else if ()
			ft_parse_link(lem_in->line);
		else
			ft_lem_in_error(/*lem_in*/);
		ft_freestr(lem_in->line);
	}
}
