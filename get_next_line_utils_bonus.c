/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:57:31 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/04 13:33:12 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	lst_add_f(t_list **lst, int fd, char *str)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		free(str);
		return (-1);
	}
	new->fd = fd;
	new->str = str;
	new->next = *lst;
	*lst = new;
	return (0);
}

char	*lst_fd_get_data(const t_list *lst, int fd)
{
	while (lst != NULL)
	{
		if (lst->fd == fd)
			return (lst->str);
		lst = lst->next;
	}
	return (NULL);
}

void	lst_rm_fd(t_list **lst, int fd)
{
	t_list	*tmp;
	t_list	*to_it;

	while (*lst != NULL && (*lst)->fd == fd)
	{
		tmp = (*lst)->next;
		free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	to_it = *lst;
	while (to_it != NULL && to_it->next != NULL)
	{
		if (to_it->next->fd == fd)
		{
			tmp = to_it->next->next;
			free(to_it->next->str);
			free(to_it->next);
			to_it->next = tmp;
		}
		to_it = to_it->next;
	}
}

int	lst_fd_update_data(t_list **lst, int fd, char *str)
{
	t_list	*to_it;

	if (str == NULL)
	{
		lst_rm_fd(lst, fd);
		return (0);
	}
	to_it = *lst;
	while (to_it != NULL)
	{
		if (to_it->fd == fd)
		{
			to_it->str = str;
			return (0);
		}
		to_it = to_it->next;
	}
	if (lst_add_f(lst, fd, str) < 0)
		return (-1);
	return (0);
}
