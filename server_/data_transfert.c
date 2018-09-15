/*
** EPITECH PROJECT, 2018
** data
** File description:
** oui
*/

#include "server.h"
#include <errno.h>

void	data_connection(void)
{
	char *cmd = "ls";
	char *argv[3] = {
		"ls", "-l", NULL
	};
	int p[2];
	int pid;

	if (pipe(p) == -1)
		pexit("pipe failed");
	if ((pid = fork()) == -1)
		pexit("fork failed");
	if (pid == 0) {
		dup2(data.fd, 1);
		execvp(cmd, argv);
		exit(84);
	}
	if (close(data.fd) == -1)
		pexit("close fail");
	data.is_active = 0;
}

void	data_read(char *path)
{
	char	*buf = malloc(50);
	int	tr = 1;
	int	size;
	int	fd;

	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd == -1)
		pexit(strerror(errno));
	while (tr) {
		if ((size = read(data.fd, buf, 50)) == 0)
			tr = 0;
		buf[size] = '\0';
		write(fd , buf, size);
	}
	if (close(data.fd) == -1)
		pexit(strerror(errno));
	if (close(fd) == -1)
		pexit(strerror(errno));
	data.is_active = 0;
}

void	data_write(char *path)
{
	struct stat	st;
	void		*buf;
	int		fd;

	if (access(path, F_OK) == 0 && stat(path, &st) == 0) {
		msg("150 opening ASCII mode data");
		buf = malloc(st.st_size + 1);
		fd = open(path, O_RDONLY);
		read(fd, buf, st.st_size);
		write(data.fd, buf, st.st_size);
		if (close(data.fd) == -1 || close(fd) == -1)
			pexit("close failed");
		data.is_active = 0;
		msg("226 transfer complete");
	}
}

void	set_data_transfert(void)
{
	int		port = 65281;

	while (port < 65535) {
		if (check_for_server(port) == 1)
			break;
		port++;
	}
	if (port == 65535)
		pexit("La je comprend vraiment pas...");
	dprintf(info.fd, "227 Entering Passive Mode (%s,255,%d).\n",
		data.ip_addr, ((65281 - port) * -1));
	data.fd = accept(data.fd, (struct sockaddr *)
			 &data.s_in_client, &data.s_in_size);
	data.is_active = 1;
}

int	check_for_server(int port)
{
	data.s_in_size = sizeof(data.s_in_client);
	if (!(data.pe = getprotobyname("TCP")))
		pexit("getprotobyname failed");
	data.s_in.sin_family = AF_INET;
	data.s_in.sin_port = htons(port);
	data.s_in.sin_addr.s_addr = INADDR_ANY;
	data.fd = socket(AF_INET, SOCK_STREAM, data.pe->p_proto);
	if (data.fd == -1)
		return (0);
	if (bind(data.fd, (const struct sockaddr *)&data.s_in,
		 sizeof(data.s_in)) == -1)
		return (0);
	if (listen(data.fd, 42) == -1)
		closefdandquit(data.fd, "close socket failed");
	data.ip_addr = get_ip_addr();
	return (1);
}
