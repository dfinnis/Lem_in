/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:40:50 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/09 13:40:52 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_lem_in_usage(void)
{
	ft_putstr("usage:	./lem-in < map.map\n");
	exit(1);
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		ft_lem_in_usage();
//	ft_lem_in_initialize(/*struct*/);
//	ft_lem_in_parse();
//	ft_lem_in_free(/*struct*/);
	return (0);
}
