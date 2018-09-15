/*
** EPITECH PROJECT, 2018
** rfc
** File description:
** toujours al
*/

#include "server.h"

void	noop(char *line)
{
	(void) line;
	if (is_logged() == 2) {
		msg("200 NOOP ok.");
	}
	else
		msg("530 Please login with USER and PASS");
}

void	retr(char *line)
{
	char	*path = get_arg(line, 1);

	if (is_logged() == 2 && path != NULL && data.is_active) {
		data_write(path);
	}
	else
		msg("530 Please login with USER and PASS");
}

void	stor(char *line)
{
	char	*path = get_arg(line, 1);

	if (is_logged() == 2 && path != NULL && data.is_active) {
		data_read(path);
	}
	else
		msg("530 Please login with USER and PASS");
}

void	list(char *line)
{
	(void) line;
	if (is_logged() == 2 && data.is_active) {
		msg("150 File status okay; about to open data connection.");
		data_connection();
	}
	else
		msg("530 Please login with USER and PASS");
}
