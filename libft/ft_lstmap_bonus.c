/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:19:34 by josepedr          #+#    #+#             */
/*   Updated: 2025/04/17 14:26:11 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dup;
	t_list	*temp;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	dup = NULL;
	while (lst)
	{
		content = (*f)(lst->content);
		temp = ft_lstnew(content);
		if (!temp)
		{
			(*del)(content);
			ft_lstclear(&dup, (*del));
			return (NULL);
		}
		ft_lstadd_back(&dup, temp);
		lst = lst->next;
	}
	return (dup);
}
