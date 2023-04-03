#include <iostream>
#include <string>
#include <csignal>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "tcp.h"
#include "connection.h"

using namespace std;

#define BUFFER_SIZE 1000

extern int client_socket;

// Handler for received SIGINT signal
// Sends BYE to the server and terminates the connection
void tcp_sigint_handler(int signal){
    char bye_message[] = "BYE\n";

    cerr << "SIGINT signal received, sending BYE, waiting for response, terminating connection and exiting script...\n";

    if(send(client_socket, bye_message, sizeof(bye_message), 0) < 0){
        cerr << "ERROR: send\n";
    }

    char received_data[BUFFER_SIZE] = "";

    if(recv(client_socket, &received_data, BUFFER_SIZE, 0) < 0){
        cerr << "ERROR: recv\n";
    }

    cout << received_data;

    shutdown(client_socket, SHUT_RDWR);
    close(client_socket);
    exit(0);
}

void close_tcp_connection_on_error(){
    shutdown(client_socket, SHUT_RDWR);
    close(client_socket);
    exit(1);
}

void communicate_over_tcp(string host, unsigned short port){
    int family = AF_INET;
    
    set_socket(family, SOCK_STREAM);

    struct sockaddr_in address;
    set_address(&address, family, host, port);

    // Setting function for SIGINT handling
    struct sigaction act;
    act.sa_handler = tcp_sigint_handler;
    sigaction(SIGINT, &act, nullptr);

    // Setting connection to server with specific address
    if(connect(client_socket, (struct sockaddr*) &address, sizeof(address)) != 0){
        cerr << "ERROR: connect\n";
        close(client_socket);
        exit(1);
    }

    string input_data;
    
    // Processing communication (sending and receiving data in correct format) with already connected server and printing received_data to standard output
    while(!getline(cin, input_data).eof()){
        input_data += "\n";

        if(send(client_socket, input_data.c_str(), input_data.size(), 0) < 0){
           cerr << "ERROR: send\n";
           close_tcp_connection_on_error();
        }

        char received_data[BUFFER_SIZE] = "";

        if(recv(client_socket, &received_data, BUFFER_SIZE, 0) < 0){
            cerr << "ERROR: recv\n";
            close_tcp_connection_on_error();
        }

        cout << received_data;
    }

    // Properly closing connection to server
    shutdown(client_socket, SHUT_RDWR);
    close(client_socket);
}
