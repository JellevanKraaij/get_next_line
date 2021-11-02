/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:57:31 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/02 21:42:32 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	lst_add_f(t_list **lst, int fd, char *str)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (-1);
	new->fd = fd;
	new->str = str;
	new->next = *lst;
	*lst = new;
	return (0);
}

int	lst_fd_get_data(const t_list *lst, int fd, char **str)
{
	while (lst != NULL)
	{
		if (lst->fd == fd)
		{
			*str = lst->str;
			return (0);
		}
		lst = lst->next;
	}
	*str = NULL;
	return (-1);
}

void	lst_rm_fd(t_list **lst, int fd)
{
	t_list	*to_rm;

	if (*lst != NULL && (*lst)->fd == fd)
	{
		free((*lst)->str);
		free(*lst);
		*lst = NULL;
	}
	while (*lst != NULL && (*lst)->next != NULL)
	{
		if ((*lst)->next->fd == fd)
		{
			to_rm = (*lst)->next;
			(*lst)->next = to_rm->next;
			free(to_rm->str);
			free(to_rm);
			return ;
		}
		*lst = (*lst)->next;
	}
}

void	lst_fd_update_data(t_list *lst, int fd, char *str)
{
	while (lst != NULL)
	{
		if (lst->fd == fd)
		{
			lst->str = str;
			return ;
		}
		lst = lst->next;
	}
}
