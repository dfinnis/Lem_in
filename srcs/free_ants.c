/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:31:25 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/24 15:14:09 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_free_queue(t_queue *queue)
{
	t_queue *tmp;

	while (queue)
	{
		tmp = queue;
		queue = queue->next;
		free(tmp);
		tmp = NULL;
	}
	free(queue);
	queue = NULL;
}

void	ft_free_ants(t_ant **ant)
{
	int i;

	i = 0;
	while (ant[i])
	{
		free(ant[i]);
		ant[i] = NULL;
		i++;
	}
	if (ant)
		free(ant);
	ant = NULL;
}
