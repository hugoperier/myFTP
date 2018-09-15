/*
** EPITECH PROJECT, 2018
** rfc
** File description:
** 959 ter street
*/

#include "server.h"

void	user(char *line)
{
	char	*arg1 = get_arg(line, 1);

	if (arg1 != NULL && is_logged() == 0) {
		msg("331 User name okay, need password");
		info.username = get_arg(line, 1);
	}
	else if (is_logged())
		msg("530 Already loggin in");
	free(arg1);
}

void	pass(char *line)
{
	if (is_logged() == 1 && get_arg(line, 1) == NULL) {
		msg("230 User logged in, proceed");
		info.password = strdup("ok");
	}
	else if (strcmp(info.username, "Anonymous") != 0 && is_logged() == 0) {
		msg("530 Login incorrect.");
		dprintf(1, ">%s<, islog = %d\n", get_arg(line, 1), is_logged());
	}
	else if (is_logged() == 0) {
		msg("503 Need account for login.");
	}

}

void	cwd(char *line)
{
	char		*path = get_arg(line, 1);

	if (is_logged() == 2) {
		if (path != NULL) {
			info.path = change_path(path);
			msg("250 Requested file action okay, completed.");
		}
		else
			msg("550 file not found");
	}
	else
		msg("530 Not logged in");
	free(path);

}

void	cdup(char *line)
{
	int	i = strlen(info.path);

	(void) line;
	if (is_logged() == 2) {
		while (info.path[i] != '/' && i > 0)
			i--;
		info.path[i] = '\0';
		msg("250 Command okay.");
	}
	else
		msg("530 Not logged in");
}

void	quit(char *line)
{
	(void) line;
	info.status = 0;
	msg("221 Logged out");
}
