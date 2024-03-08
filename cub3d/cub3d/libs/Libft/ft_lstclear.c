/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:22:10 by eisikogl          #+#    #+#             */
/*   Updated: 2022/07/28 22:44:28 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*iter;

	iter = *lst;
	while (iter != NULL)
	{
		temp = iter -> next;
		del(iter -> content);
		free(iter);
		iter = temp;
	}
	*lst = NULL;
}
