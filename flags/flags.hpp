/**     Copyright 2021 Sam Sovereign github: ldaIas
 * 
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
*/

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