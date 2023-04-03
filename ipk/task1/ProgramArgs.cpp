#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "ProgramArgs.h"

using namespace std;

void print_help(){
    cout << "This is the client for the IPK Calculator Protocol. The client is\n";
    cout << "able to communicate with any server using IPKCP.\n";
    cout << "The client is started using: ipkcpc -h <host> -p <port> -m <mode>\n";
    cout << "where host is the IPv4 address of the server, port the server port,\n";
    cout << "and mode either tcp or udp (e.g., ipkcpc -h 1.2.3.4 -p 2023 -m udp).\n";
    cout << "--help parameter prints this help\n";

}

void printERR_redundant_arg(string arg){
    cerr << "ERROR: Redundant argument: " << arg << "\n";
    print_help();
    exit(1);
}

void printERR_unknown_arg(string arg){
    cerr << "ERROR: Unknown argument: " << arg << "\n";
    print_help();
    exit(1);
}
void printERR_unknown_mode(string mode){
    cerr << "ERROR: Unknown mode: " << mode << "\n";
    print_help();
    exit(1);
}

ProgramArgs::ProgramArgs(int argc, char **argv){
    if(argc == 2){
        if(strcmp(argv[1], "--help") == 0){
            print_help();
            exit(0);
        }
        else{
            printERR_unknown_arg(argv[1]);
            exit(1);
        }
    }
    
    if(argc != 7){
        cerr << "ERROR: Wrong number of program arguments\n";
        print_help();
        exit(1);
    }

    bool host_entered = false;
    bool port_entered = false;
    bool mode_entered = false;

    for(int i = 1; i < argc; i+=2){
        if(strcmp(argv[i], "-h") == 0){
            if(host_entered){
                printERR_redundant_arg("-h");
            }
            else{
                host_entered = true;
                host = argv[i+1];
            }
        }
        else if(strcmp(argv[i], "-p") == 0){
            if(port_entered){
                printERR_redundant_arg("-p");
            }
            else{
                port_entered = true;
                port = (unsigned short) strtoul(argv[i+1], nullptr, 0);
            }
        }
        else if(strcmp(argv[i], "-m") == 0){
            if(mode_entered){
                printERR_redundant_arg("-m");
            }
            else{
                mode_entered = true;
                mode = argv[i+1];
            }
        }
        else{
            printERR_unknown_arg(argv[i]);
        }
    }
    if(mode != "udp" && mode != "tcp"){
        printERR_unknown_mode(mode);
    }
}
