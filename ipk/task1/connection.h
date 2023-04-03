#include <sys/socket.h>

#ifndef CONNECTION_H
#define CONNECTION_H

void set_socket(int family, int type);
void set_address(struct sockaddr_in *address, int family, std::string host, unsigned short port);

#endif
