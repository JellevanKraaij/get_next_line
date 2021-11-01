/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:59:24 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/01 16:01:57 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct buffer_data {
	char	*buffer;
	size_t	cursor;
	size_t	len;
}	t_buffer_data;

char	*get_next_line(int fd);
char	*ft_strndup(const char *str, size_t n);
size_t	ft_strnlen(const char *s, size_t maxlen);
void	*ft_memcpy(void *dst, const void *src, size_t n);


#endif