#include <iostream>
#include <string>
#include <csignal>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "udp.h"
#include "connection.h"

using namespace std;

#define BUFFER_SIZE 1000

extern int client_socket;

void udp_sigint_handler(int signal){
    cerr << "SIGINT signal received, closing socket and exiting script...\n";
    close(client_socket);
    exit(0);
}

void close_udp_socket_on_error(){
    close(client_socket);
    exit(1);
}

void udp_print_received_message(char *received_message){

    char status_code = received_message[1];

    if(status_code == 0){
        cout << "OK:";
    }
    else if(status_code == 1){
        cout << "ERR:";
    }
    else{
        cout << "Unknown status code:";
    }

    char message_size = received_message[2];

    // Prints the message (ignores header - first three characters from input string)
    for(int i = 0; message_size > 0; i++){
        cout << received_message[i + 3];
        message_size--;
    }

    cout << "\n";
}

void communicate_over_udp(string host, unsigned short port){
    int family = AF_INET;

    set_socket(family, SOCK_DGRAM);

    struct sockaddr_in address;
    set_address(&address, family, host, port);

    socklen_t address_size = sizeof(address);
    string input_data, data_to_send;

    // Setting timeout
    struct timeval timeout;
    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    if(setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0){
        cerr << "ERROR: setsockopt\n";
    }

    // Setting function for SIGINT handling
    struct sigaction act;
    act.sa_handler = udp_sigint_handler;
    sigaction(SIGINT, &act, nullptr);
    
    // Processing communication (sending and receiving data in correct format) with server on specific address and printing received_data to standard output
    while(!getline(cin, input_data).eof()){
        data_to_send = '\0' + string(1, char(input_data.size())) + input_data;

        if(sendto(client_socket, data_to_send.c_str(), data_to_send.size(), 0, (struct sockaddr*) &address, address_size) < 0){
           cerr << "ERROR: sendto\n";
           close_udp_socket_on_error();
        }

        char received_data[BUFFER_SIZE] = "";

        if(recvfrom(client_socket, &received_data, BUFFER_SIZE, 0, (struct sockaddr*) &address, &address_size) < 0){
            if(errno == EWOULDBLOCK){
                cerr << "ERROR: recvfrom: Timeout expired\n";
            }
            else{
                cerr << "ERROR: recvfrom\n";
            }
            close_udp_socket_on_error();
        }

        udp_print_received_message(received_data);
    }

    close(client_socket);
}
