/*
** EPITECH PROJECT, 2018
** wrapper
** File description:
** wrap but no trap
*/

#include "server.h"

void    wrapper(char *line)
{
	char	*arg[] = {"USER", "PASS", "CWD", "CDUP", "QUIT", "DELE", "PWD",
			  "PASV", "PORT", "HELP", "NOOP", "RETR", "STOR", "LIST"};
	void	(**fnct[14])(char *);
	int	i = 0;

	fnct[0] = fpts();
	while (i < 14) {
		if (line != NULL && strcmp(line, "") != 0 &&
		    strcmp(arg[i], get_arg(line, 0)) == 0) {
			(*fnct[0][i])(line);
			break;
		}
		i++;
	}
	if (i == 14)
		dprintf(info.fd, "500 Unknow command.\n");
}

void	(**fpts(void))(char *)
{
	void	(**fnct)(char *);

	fnct = malloc(sizeof(*fnct) * 14);
	fnct[0] = &user;
	fnct[1] = &pass;
	fnct[2] = &cwd;
	fnct[3] = &cdup;
	fnct[4] = &quit;
	fnct[5] = &dele;
	fnct[6] = &pwd;
	fnct[7] = &pasv;
	fnct[8] = &port;
	fnct[9] = &help;
	fnct[10] = &noop;
	fnct[11] = &retr;
	fnct[12] = &stor;
	fnct[13] = &list;
	return (fnct);
}

char    *get_arg(char *line, int nb)
{
	char    *newline;
	int	i = 0;
	int	count = 0;

	if (line == NULL)
		return (NULL);
	newline = malloc(sizeof(char) * (strlen(line) + 1));
	while (count != nb && line[i] != '\0') {
		if (line[i] == ' ')
			count++;
		i++;
	}
	if (line[i] == '\0')
		return (NULL);
	newline = parse_arg(line, i, newline);
	return (newline);
}

char	*parse_arg(char *line, int i, char *newline)
{
	int	o = 0;

	while (line[i] != ' ' && line[i] != '\0') {
		newline[o] = line[i];
		i++;
		o++;
	}
	newline[o] = '\0';
	return (newline);
}
