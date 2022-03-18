/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:07:40 by jaham             #+#    #+#             */
/*   Updated: 2022/03/18 15:29:37 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

static void	ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*cp_dest;
	unsigned char	*cp_src;

	cp_dest = (unsigned char *) dest;
	cp_src = (unsigned char *) src;
	while (len--)
		*(cp_dest++) = *(cp_src++);
}

t_stat	init_string(t_string *string)
{
	string->str = malloc(sizeof(char));
	if (!string->str)
		return (ERROR);
	string->len = 0;
	string->size = 1;
	return (SUCCESS);
}

t_stat	append_string(t_string *string, char c)
{
	char	*temp;

	if (string->len >= string->size)
	{
		temp = malloc(sizeof(char) * (string->size << 1));
		if (!temp)
			return (ERROR);
		ft_memcpy(temp, string->str, string->len);
		free(string->str);
		string->str = temp;
		string->size <<= 1;
	}
	string->str[(string->len)++] = c;
	return (SUCCESS);
}

char	*copy_string(t_string *string)
{
	char	*ret;

	if (string->len == 0)
		return (NULL);
	ret = malloc(sizeof(char) * (string->len + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, string->str, string->len);
	ret[string->len] = '\0';
	return (ret);
}

t_buffer	*find_buffer_list(t_buffer **head, int fd)
{
	t_buffer	*new;
	t_buffer	*cp;

	cp = *head;
	while (cp && cp->fd != fd)
		cp = cp->next;
	if (cp)
		return (cp);
	new = malloc(sizeof(t_buffer));
	if (!new)
		return (NULL);
	new->curr = NULL;
	new->end = NULL;
	new->fd = fd;
	new->next = *head;
	new->prev = NULL;
	*head = new;
	return (new);
}
