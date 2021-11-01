/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:24:47 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/01 22:48:11 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	size_t		len;
	char		*ret;

	ret = NULL;
	if (leftover == NULL)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		buffer[len] = '\0';
	}
	else
	{
		len = ft_strlen(leftover);
		ft_memcpy(buffer, leftover, len + 1);
		free(leftover);
		leftover = NULL;
	}
	if (len <= 0)
	{
		free(leftover);
		return (NULL);
	}
	while (len > 0 && ft_strchr(buffer, '\n') == NULL)
	{
		ret = ft_append_buff(ret, buffer, len);
		len = read(fd, buffer, BUFFER_SIZE);
		if (len < 0)
		{
			free(ret);
			free(leftover);
			leftover = NULL;
			return (NULL);
		}
		buffer[len] = '\0';
	}
	if (len == 0)
	{
		free(leftover);
		leftover = NULL;
		return (ret);
	}
	tmp = ft_strchr(buffer, '\n');
	ret = ft_append_buff(ret, buffer, tmp - buffer);
	leftover = ft_append_buff(leftover, tmp + 1, ft_strlen(tmp + 1));
	return (ret);
}
