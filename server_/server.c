/*
** EPITECH PROJECT, 2018
** server
** File description:
** serv
*/

#include "server.h"

int     handle_client(int client_fd)
{
	char *str;

	info.fd = client_fd;
	dprintf(client_fd, "220 Connexion etablished\n");
	while (info.status) {
		if ((str = get_next_line(client_fd)) == NULL)
			pexit("gnl failed");
		str[strlen(str)] = '\0';
		str = clean_str(str);
		wrapper(str);
	}
	return (1);
}

void	start_server(int port)
{
	connect_t	connect = init_server(port);
	int		c_fd;
	int		pid;

	while (1) {
		c_fd = accept(connect.fd, (struct sockaddr *)
			      &connect.s_in_client, &connect.s_in_size);
		printf("accepted\n");
		if ((pid = fork()) == -1)
			pexit("fork failed");
		if (pid == 0)
			break;
	}
	if (c_fd == -1)
		closefdandquit(connect.fd, "accept failed");
	handle_client(c_fd);
	shutdown(c_fd, SHUT_RDWR);
	if (close(c_fd) == -1 || close(connect.fd) == -1)
		pexit("close failed");
}

connect_t	init_server(int port)
{
	connect_t connect;

	connect.s_in_size = sizeof(connect.s_in_client);
	if (!(connect.pe = getprotobyname("TCP")))
		pexit("getprotobyname failed");
	connect.s_in.sin_family = AF_INET;
	connect.s_in.sin_port = htons(port);
	connect.s_in.sin_addr.s_addr = INADDR_ANY;
	connect.fd = socket(AF_INET, SOCK_STREAM, connect.pe->p_proto);
	if (connect.fd == -1)
		perror("Socket failed");
	if (bind(connect.fd, (const struct sockaddr *)&connect.s_in,
		 sizeof(connect.s_in)) == -1)
		closefdandquit(connect.fd, "bind failed");
	if (listen(connect.fd, 42) == -1)
		closefdandquit(connect.fd, "close socket failed");
	init_info();
	return (connect);
}

void	init_info(void)
{
	info.status = 1;
	info.port = -1;
}

void	closefdandquit(int fd, char *msg)
{
	if (close(fd) == -1)
		perror("close failed");
	pexit(msg);
}
