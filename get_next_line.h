/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:52:14 by jaham             #+#    #+#             */
/*   Updated: 2022/03/19 12:33:09 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 252
# endif

typedef enum e_stat
{
	SUCCESS = 0,
	ERROR
}	t_stat;

typedef enum e_eof
{
	IS_END = 0,
	NOT_END,
	READ_ERROR
}	t_eof;

typedef struct s_buffer
{
	int				fd;
	char			buf[BUFFER_SIZE];
	char			*curr;
	char			*end;
	struct s_buffer	*next;
}	t_buffer;

typedef struct s_string
{
	char	*str;
	size_t	len;
	size_t	size;
}	t_string;

t_stat		init_string(t_string *string);
t_stat		append_string(t_string *string, char c);
char		*copy_string(t_string *string);
t_buffer	*find_buffer_list(t_buffer **head, int fd);
char		*get_next_line(int fd);

#endif