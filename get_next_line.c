/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:24:47 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/01 16:43:00 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void	empty_buffer_data(t_buffer_data *data)
{
	free(data->buffer);
	data->buffer = NULL;
	data->cursor = 0;
	data->len = 0;
}

char	*get_next_line(int fd)
{
	static t_buffer_data	data;
	size_t					i;
	char					*ret;

	i = 0;
	ret = 0;
	if (data.buffer == NULL)
		data.buffer = malloc(BUFFER_SIZE + 1);
	if (data.buffer == NULL)
		return (NULL);
	if (data.len == 0)
		data.len = read(fd, data.buffer, BUFFER_SIZE);
	while (data.len > 0)
	{
		while (i + data.cursor < data.len)
		{
			i++;
			if (data.buffer[i + data.cursor] == '\n')
			{
				ret = ft_strndup(&data.buffer[data.cursor], i);
				data.cursor += i + 1;
				return (ret);
			}
			else if (i + data.cursor == data.len - 1)
			{
				ret = ft_strndup(&data.buffer[data.cursor], i);
				data.cursor += i + 1;
				return (ret);
			}
		}
		data.cursor = 0;
		data.len = read(fd, data.buffer, BUFFER_SIZE);
	}
	if (data.len == 0)
	{
		printf("datalen == 0");
		ret = ft_strndup(&data.buffer[data.cursor], i);
	}

	return (ret);
}
