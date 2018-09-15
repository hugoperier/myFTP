/*
** EPITECH PROJECT, 2018
** serveur
** File description:
** oui
*/

#ifndef SERVER
#define SERVER

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <netdb.h>

typedef struct	connect_s
{
	struct protoent		*pe;
	int			fd;
	struct sockaddr_in	s_in;
	struct sockaddr_in      s_in_client;
	socklen_t               s_in_size;
	char			*ip_addr;
	int			is_active;
}		connect_t;

typedef struct	info_s
{
	int	status;
	int	port;
	char	*username;
	char	*password;
	char	*path;
	int	fd;
}		info_t;

extern info_t		info;
extern connect_t	data;

int		handle_client(int);
void		pexit(char *);
void		start_server(int);
connect_t	init_server(int);
void		closefdandquit(int, char *);
void		help_arg();
char		*get_next_line(const int);
void		my_puterr(char *);
void		wrapper(char *);
void		(**fpts(void))(char *);
char		*get_arg(char *, int);
void		init_info();
int		is_logged();
void		msg(char *);
void		set_data_transfert();
int		check_for_server(int);
void		data_write(char *);
void		data_connection();
void		data_read(char *);
char		*get_ip_addr();
char		*clean_str(char *);
char		*parse_arg(char *, int, char *);
char		*change_path(char *);

/*
** servers RFC959 features
*/

void		user(char *);
void		pass(char *);
void		cwd(char *);
void		cdup(char *);
void		quit(char *);
void		dele(char *);
void		pwd(char *);
void		pasv(char *);
void		port(char *);
void		help(char *);
void		noop(char *);
void		retr(char *);
void		stor(char *);
void		list(char *);

#endif
