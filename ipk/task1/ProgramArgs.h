#include <string>

using namespace std;

#ifndef PROGRAM_ARGS_H
#define PROGRAM_ARGS_H

void print_help();

void printERR_redundant_arg(string arg);
void printERR_unknown_arg(string arg);
void printERR_unknown_mode(string mode);

class ProgramArgs{
    public:
        string host;
        unsigned short port;
        string mode;

    public:
        ProgramArgs(int argc, char **argv);
};

#endif
