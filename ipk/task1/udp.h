#ifndef UDP_H
#define UDP_H

void udp_sigint_handler(int signal);
void close_udp_socket_on_error();
void udp_print_received_message(char *received_message);
void communicate_over_udp(std::string host, unsigned short port);

#endif
