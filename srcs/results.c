#include "lem_in.h"

void    ft_populate_array(t_lem_in *lem_in)
{
    t_paths **array;
    int     i;
    int     j;
    t_paths *tmp;

    array = (t_paths **)malloc(sizeof(t_paths *) * (lem_in->ant_count + 1));
    i = 0;
    while (i < lem_in->ant_count)
    {
        tmp = lem_in->shortest->group->path;
        j = 0;
        while (tmp && j < lem_in->depth && i < lem_in->ant_count)
        {
//           array[i + j] = (t_paths *)malloc(sizeof(t_paths));
            array[i + j] = tmp;
            tmp = tmp->next;
            j++;
        }
        i++;
    }
    array[i] = NULL;
    lem_in->array = array;
}

char    *ft_build_ant(int i, char *name)
{
    char *line;

    line = ft_strjoin("L", ft_itoa(i));
    line = ft_strjoin(line, "-");
    line = ft_strjoin(line, name);
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
    while (lem_in->array[lem_in->ant_count - 1]->highway)
    {
        i = 1;
        j++;
        line = ft_strdup("");
        while (i <= lem_in->ant_count)
        {
            if (lem_in->array[i - 1]->highway)
            {
                ant = ft_build_ant(i, lem_in->array[i - 1]->highway->room->name);
                line = ft_strjoin(line, ant);
            }
            lem_in->array[i - 1]->highway = lem_in->array[i - 1]->highway->next;
            i++;
            if (i == j * lem_in->depth)
                break ;
        }
        ft_printf("%s\n", line);
        free (line);
        line = NULL;
    }
}
