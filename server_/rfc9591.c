/*
** EPITECH PROJECT, 2018
** rdc
** File description:
** le meme mais le next
*/

#include "server.h"

void	dele(char *line)
{
	char	*path = get_arg(line, 1);
	char	*concpath = malloc(sizeof(char) *
				   (strlen(info.path) + strlen(path) + 1));

	if (is_logged() == 2 && path != NULL) {
		concpath = strcat(info.path, path);
		if (unlink(concpath) == 0)
			msg("250 Requested file action okay, completed");
		else
			msg("550 File does not exist");
	}
	else
		msg("530 Not connected");
	free(path);
}

void	pwd(char *line)
{
	(void) line;
	if (is_logged() == 2)
		dprintf(info.fd, "257 \"%s\"\n", info.path);
	else
		msg("530 Not logged in");
}

void	pasv(char *line)
{
	(void) line;
	if (is_logged() == 2) {
		set_data_transfert();
	}
	else
		msg("530 Not logged in.");
}

void	port(char *line)
{
	char	*port = get_arg(line, 1);

	if (is_logged() == 2 && port != NULL) {
		info.port = atoi(port);
		msg("200 Command Okay.");;
	}
	else
		msg("530 Not logged in.");

}

void	help(char *line)
{
	(void) line;
	if (is_logged() == 2) {
		dprintf(info.fd, "214 - The followgin commands are recognized: ");
		dprintf(info.fd, "user - pass - cwd - cdup - quit - dele - pwd - ");
		dprintf(info.fd, "pasv - port - help - noop - retr - stor - list\n");
	}
	else
		msg("530 Not logged in");
}
