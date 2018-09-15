/*
** EPITECH PROJECT, 2018
** get next line
** File description:
** fdp
*/

#include "server.h"

char *get_next_line(int fd)
{
	char buf;
	char *str = malloc(sizeof(char) * 2048);
	int res;
	int i = 0;

	res = read(fd, &buf, 1);
	if (res <= 0)
		return (NULL);
	while (i < 2048 && buf != '\n') {
		str[i] = buf;
		read(fd, &buf, 1);
		i = i + 1;
	}
	str[i] = '\0';
	return (str);
}
