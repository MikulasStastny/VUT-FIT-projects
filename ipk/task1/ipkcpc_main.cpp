#include "ProgramArgs.h"
#include "tcp.h"
#include "udp.h"

int main(int argc, char **argv){

    ProgramArgs program_args(argc, argv);

    if(program_args.mode == "tcp"){        
        communicate_over_tcp(program_args.host, program_args.port);
    }
    else{
        communicate_over_udp(program_args.host, program_args.port);
    }

    return 0;
}
