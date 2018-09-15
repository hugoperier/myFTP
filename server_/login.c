/*
** EPITECH PROJECT, 2018
** log
** File description:
** file
*/

#include "server.h"

int	is_logged(void)
{
	int	i = 0;

	if (info.username != NULL && strcmp(info.username, "Anonymous") == 0)
		i++;
	if (info.password != NULL && strcmp(info.password, "ok") == 0)
		i++;
	return (i);
}

void	msg(char *msg)
{
	dprintf(info.fd, "%s\n", msg);
}

char	*clean_str(char *str)
{
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == '\r') {
			str[i] = '\0';
			printf("les corrections sont faites.\n");
			return (str);
		}
	}
	return (str);
}
