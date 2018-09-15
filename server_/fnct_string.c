/*
** EPITECH PROJECT, 2018
** fnc
** File description:
** string
*/

#include "server.h"

char	*change_path(char *cmd)
{
	struct stat     sb;
	int	i = strlen(info.path);

	if (strcmp(cmd, "..") == 0) {
		while (info.path[i] != '/' && i > 0)
			i--;
		info.path[i] = '\0';
	}
	else if (!(stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))) {
		info.path = strdup(cmd);
	}
	else if (!(stat(strcat(info.path, cmd), &sb) == 0 && S_ISDIR(sb.st_mode))) {
		info.path = strcat(info.path, cmd);
	}
	return (info.path);
}

void    my_puterr(char *str)
{
	write(2, &str, 100);
}

char    *get_ip_addr(void)
{
	struct hostent *hp = gethostbyname("localhost");
	int             i = 0;
	char            *buf;
	char            *str = malloc(sizeof(char) * 50);
	unsigned int    p = 0;
	unsigned int    cont = 0;

	while (hp -> h_addr_list[i] != NULL) {
		buf = inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i]));
		while (p < strlen(buf)) {
			str[cont] = buf[p];
			p++;
			cont++;
		}
		p = 0;
		i++;
	}
	str[cont] = '\0';
	return (str);
}
