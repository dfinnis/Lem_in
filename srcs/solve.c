#include "lem_in.h"

// void	ft_print_path_short(t_paths *paths)
// {
// 	t_path	*path;

// 	path = paths->highway;
// 	while (path)
// 	{
// 		ft_printf("%s\n", path->room->name);
// 		path = path->next;
// 	}
// 	ft_printf("\n");
// }

// void	ft_print_group_short(t_lem_in *lem_in)
// {
// 	t_groups	*groups;
// 	t_group		*group;
// 	int			j;

// 	groups = lem_in->shortest;
// 	j = 1;
// 	group = groups->group;
// 	ft_printf("\n--SHORTEST --\n");
// 	while (group)
// 	{
// 		ft_printf("--%i path--\n", j++);
// 		ft_print_path_short(group->path);
// 		group = group->next;
// 	}
//     ft_printf("group steps = %i\n", lem_in->length);
//     ft_printf("group depth = %i\n", lem_in->depth);
// }

int     ft_find_length(t_group *path, int depth, int ants)
{
    t_group *tmp;
    int     j;
    int     steps;

    tmp = path;
    j = 1;
    steps = 1;
    while (tmp && j++ <= depth)
    {
        if (steps < tmp->path->length - 2 + (ants / depth))
            steps = tmp->path->length - 2 + (ants / depth);
        tmp = tmp->next;
    }
    return (steps);
}

void    ft_lem_in_solve(t_lem_in *lem_in)
{
    t_group     *path;
    t_groups    *tmp;
    int         i;
    int         steps;

    lem_in->shortest = lem_in->groups;
    lem_in->length = lem_in->shortest->group->path->length - 2 + lem_in->ant_count;
    lem_in->depth = 1;
    if (lem_in->ant_count == 1)
    {
        // ft_print_group_short(lem_in);
        return ;
    }
    tmp = lem_in->groups;
    while (tmp)
    {
        i = 1;
        path = tmp->group;
        while(path && i <= lem_in->ant_count)
        {
            steps = ft_find_length(path, i, lem_in->ant_count);
            if (steps < lem_in->length)
            {
                lem_in->shortest = tmp;
                lem_in->length = steps;
                lem_in->depth = i;
            }
            path = path->next;
            i++;
        }
        tmp = tmp->next;
    }
    // ft_print_group_short(lem_in);
}