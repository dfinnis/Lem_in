/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   results_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 10:58:59 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/19 10:59:00 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_initialize_ant(t_ant **array)
{
	*array = (t_ant *)malloc(sizeof(t_ant));
	ft_bzero(*array, sizeof(**array));
	(*array)->traveled = 1;
}

void    ft_populate_array(t_lem_in *lem_in)
{
	t_ant	**array;
	int		i;
	int		j;
	t_group	*tmp;

    array = (t_ant **)malloc(sizeof(t_ant *) * (lem_in->ant_count + 1));
    i = 0;
    // j = 0;//
    while ((i/* + j*/) < lem_in->ant_count)
    {
        tmp = lem_in->shortest->group/*->path*/;
        j = 0;
        while (tmp && j < lem_in->depth && i < lem_in->ant_count)
        {
        	ft_initialize_ant(&array[i]);
            array[i]->path = tmp->path->highway;
            // ft_printf("j: %d, first room in tmp: %s\n", j, tmp->highway->next->room->name);
            // ft_printf("j: %d, first room in tmp->next: %s\n", j, tmp->next->highway->next->room->name);
            // ft_printf("j: %d, first room in array: %s\n", j, array[i]->path->next->room->name);
            tmp = tmp->next;
            j++;
            i++;
        }
//        i++;
    }
    array[i] = NULL;
    lem_in->array = array;
    i = 0;
    while (array[i])
    {
    	ft_printf("i: %d, first room in path: %s\n", (i + 1), array[i]->path->next->room->name);
    	i++;
    }
}

char    *ft_build_ant(int i, t_ant *ant)
{
    char	*line;
    int		count;
    t_path	*tmp;

    count = 0;
    tmp = ant->path;
    if (ant->end)
    	return ("");// can be better
    while (count++ < ant->traveled)
    	tmp = tmp->next;
    line = ft_strjoin("L", ft_itoa(i));
    line = ft_strjoin(line, "-");
    line = ft_strjoin(line, tmp->room->name);
    ant->traveled++;
    if (!tmp->next)
    	ant->end = 1;
    return (line);
}

void    ft_display_results(t_lem_in *lem_in)
{
    int  i;
    int  j;
    char *line;
    char *ant;
    
    ft_populate_array(lem_in);
    j = 0;
    while (!lem_in->array[lem_in->ant_count - 1]->end || !lem_in->array[0]->end)
    {
        i = 1;
        j++;
        line = ft_strdup("");
        while (i <= lem_in->ant_count)
        {
            if (lem_in->array[i - 1]->path)
            {
                ant = ft_build_ant(i, lem_in->array[i - 1]);
                if (ft_strcmp(line, "") == 0)
                    line = ft_strjoin(line, ant);
                else
                {
                    line = ft_strjoin(line, " ");
                    line = ft_strjoin(line, ant);
                }
            }
            i++;
            if (i > j * lem_in->depth/* && j > 1*/)/////////////////////////////////////////////////
                break ;
        }
        ft_printf("%s\n", line);
        free (line);
        line = NULL;
    }
}
