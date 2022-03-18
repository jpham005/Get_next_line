/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:59:58 by jaham             #+#    #+#             */
/*   Updated: 2022/03/18 15:29:42 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

static char	*lst_del(t_buffer *buffer)
{
	if (buffer->prev)
		buffer->prev->next = buffer->next;
	if (buffer->next)
		buffer->next->prev = buffer->prev;
	free(buffer);
	return (NULL);
}

static char	*del_all(t_buffer *buffer, t_string *string)
{
	lst_del(buffer);
	free(string->str);
	return (NULL);
}

static char	get_char(t_buffer *buf, t_eof *eof)
{
	if (buf->curr == buf->end)
	{
		if (buf->end < buf->buf + BUFFER_SIZE && buf->end > buf->buf)
		{
			*eof = IS_END;
			return (0);
		}
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

static t_stat	get_line(t_buffer *curr_buf, t_string *string)
{
	char	c;
	t_eof	eof;

	while (1)
	{
		c = get_char(curr_buf, &eof);
		if (eof == READ_ERROR)
		{
			del_all(curr_buf, string);
			return (ERROR);
		}
		if (eof == IS_END)
		{
			lst_del(curr_buf);
			break ;
		}
		if (append_string(string, c) == ERROR)
		{
			del_all(curr_buf, string);
			return (ERROR);
		}
		if (c == '\n')
			break ;
	}
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	static	t_buffer	*buffer;
	t_buffer			*curr_buf;
	t_string			string;
	char				*ret;

	curr_buf = find_buffer_list(&buffer, fd);
	if (!curr_buf)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
		return (lst_del(curr_buf));
	if (init_string(&string) == ERROR)
		return (lst_del(curr_buf));
	if (get_line(curr_buf, &string) == ERROR)
		return (del_all(curr_buf, &string));
	ret = copy_string(&string);
	free(string.str);
	return (ret);
}
