#include <iostream>
#include <getopt.h>

#include "interpreter/interpreter.hpp"
#include "flags/flags.hpp"

int main(int argc, char *argv[]) {

    int err = 0;
    Flags flags;

    err = parse_flags(argc, argv, flags);

    if(err != 0){
        print_usage();
        return 1;
    }

    Interpreter interpreter(flags);
    interpreter.run();    

    return err;
}
