#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "connection.h"

using namespace std;

int client_socket;

void set_socket(int family, int type){
    client_socket = socket(family, type, 0);

    if(client_socket <= 0){
        cerr << "ERROR: socket\n";
        exit(1);
    }
}

void set_address(struct sockaddr_in *address, int family, string host, unsigned short port){
    address->sin_family = family;
    address->sin_port = htons(port);

    if(inet_pton(family, host.c_str(), &address->sin_addr) <= 0){
        cerr << "ERROR: inet_pton: Invalid address\n";
        exit(1);
    }
}
