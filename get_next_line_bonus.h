/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:59:24 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/11/02 21:25:41 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_gnl {
	char	buf[BUFFER_SIZE + 1];
	char	*ret;
	ssize_t	len;
	size_t	nl;
}	t_gnl;

typedef struct s_list
{
	int				fd;
	char			*str;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);

void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);

int		lst_add_f(t_list **lst, int fd, char *str);
void	lst_rm_fd(t_list **lst, int fd);
int		lst_fd_get_data(const t_list *lst, int fd, char **str);
void	lst_fd_update_data(t_list *lst, int fd, char *str);
size_t	ft_strlen(const char *s);

#endif