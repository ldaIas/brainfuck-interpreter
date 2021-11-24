#ifndef FLAGS_HPP
#define FLAGS_HPP

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <string>

class Flags {

public:
    // Command line paramaters

    /**
     *  explicit_output:        Outputs explicitly both the number and character of the cell.
     */
    bool explicit_output = false;

    /**
     *  debug_mode:             Run in debugging mode.
     */
    bool debug_mode = false;

    /**
     *  filename:               The name of the file to interpret.
     */
    std::string filename = "";

};


/**
    parse_flags(arc, argv, flags):
        Parses any provided flags, populating the passed in flags
        object with the required information.
*/
int parse_flags(int argc, char* const argv[], Flags& flags);

/*
    print_usage():
        Prints information about how to use this program.
*/
void print_usage();

#endif