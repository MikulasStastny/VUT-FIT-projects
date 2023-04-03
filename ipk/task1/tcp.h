#ifndef TCP_H
#define TCP_H

void tcp_sigint_handler(int signal);
void close_tcp_connection_on_error();
void communicate_over_tcp(std::string host, unsigned short port);

#endif
