/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:50:09 by jaham             #+#    #+#             */
/*   Updated: 2022/03/18 15:43:04 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	// int fd1 = open("get_next_line.c", 0);
	// int fd2 = open("get_next_line_utils.c", 0);
	// char *s1 = get_next_line(fd1);
	// free(s1);
	// s1 = get_next_line(fd2);
	// free(s1);
	// s1 = get_next_line(fd1);
	// free(s1);
	// close(fd1);
	// s1 = get_next_line(fd1);
	// printf("%p\n", s1);
	// s1 = get_next_line(fd2);
	// free(s1);

	// char *str = get_next_line(0);
	
	int fd = open("test", 0);
	char *str = get_next_line(fd);
	get_next_line(fd);
	// printf("%p\n", str);
	// while (str)
	// {
	// 	printf("%s\n", str);
	// 	free(str);
	// 	str = get_next_line(fd);
	// }
	// system("leaks a.out");
}
