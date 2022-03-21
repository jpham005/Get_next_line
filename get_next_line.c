/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:59:58 by jaham             #+#    #+#             */
/*   Updated: 2022/03/21 15:43:36 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

static char	*lst_del(t_buffer **head, int fd)
{
	t_buffer	*temp;

	while (*head && (*head)->fd != fd)
		head = &((*head)->next);
	if (*head)
	{
		temp = (*head)->next;
		free(*head);
		*head = temp;
	}
	return (NULL);
}

static char	*del_all(t_buffer **buffer, t_string *string, int fd)
{
	lst_del(buffer, fd);
	free(string->str);
	string->str = NULL;
	return (NULL);
}

static char	get_char(t_buffer *buf, t_eof *eof)
{
	if (buf->curr == buf->end)
	{
		buf->end = buf->buf + read(buf->fd, buf->buf, BUFFER_SIZE);
		buf->curr = buf->buf;
	}
	if (buf->curr > buf->end)
	{
		*eof = READ_ERROR;
		return (0);
	}
	if (buf->curr == buf->end)
	{
		*eof = IS_END;
		return (0);
	}
	*eof = NOT_END;
	return (*(buf->curr++));
}

static t_stat	get_line(t_buffer **head, t_string *string, int fd)
{
	char		c;
	t_eof		eof;
	t_buffer	*curr_buf;

	curr_buf = find_buffer_list(head, fd);
	if (!curr_buf)
		return (ERROR);
	while (1)
	{
		c = get_char(curr_buf, &eof);
		if (eof == READ_ERROR)
			return (ERROR);
		if (eof == IS_END)
		{
			lst_del(head, fd);
			break ;
		}
		if (append_string(string, c) == ERROR)
			return (ERROR);
		if (c == '\n')
			break ;
	}
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	static t_buffer	*buffer;
	t_string		string;
	char			*ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, NULL, 0) < 0))
		return (lst_del(&buffer, fd));
	if (init_string(&string) == ERROR)
		return (lst_del(&buffer, fd));
	if (get_line(&buffer, &string, fd) == ERROR)
		return (del_all(&buffer, &string, fd));
	ret = copy_string(&string);
	free(string.str);
	string.str = NULL;
	return (ret);
}
