/*
** EPITECH PROJECT, 2018
** main
** File description:
** oui
*/

#include "server.h"

info_t		info;
connect_t	data;

int main(int ac, char **av)
{
	struct stat sb;

	if (ac == 2 && strcmp(av[1], "-help") == 0)
		help_arg();
	if (ac != 3)
		exit(84);
	if (atoi(av[1]) == 0)
		pexit("bad port");
	if (!(stat(av[2], &sb) == 0 && S_ISDIR(sb.st_mode)))
		pexit("bad path");
	info.path = strdup(av[2]);
	start_server(atoi(av[1]));
	return (0);
}

void	help_arg(void)
{
	printf("USAGE: ./server port path\n");
	printf("\tport\tis the port number on which the server socket listens\n");
	printf("\tpath\tis the path to the home directory for the Anonymous user");
	printf("\n");
	exit(0);
}

void    pexit(char *msg)
{
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	exit(84);
}
