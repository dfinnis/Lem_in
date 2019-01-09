/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:08:57 by dfinnis           #+#    #+#             */
/*   Updated: 2018/11/06 13:08:59 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*fresh;
	t_list	*ptr;

	tmp = f(lst);
	if (!(fresh = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	ptr = fresh;
	lst = lst->next;
	while (lst)
	{
		tmp = f(lst);
		if (!(fresh->next = ft_lstnew(tmp->content, tmp->content_size)))
			return (NULL);
		lst = lst->next;
		fresh = fresh->next;
	}
	return (ptr);
}
