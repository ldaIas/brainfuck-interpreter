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

#include <iostream>
#include "flags.hpp"

void print_usage() {
    std::cout <<
        "\nThe Brainfuck Interpreter!\n"
        "You have access to 30,000 memory locations, and each location is bound from\n"
        "0 to 255, as they are meant to represent ASCII characters.\n"
        "\nUsage: bfi [options] filename\n"
        "\n"
        "Options\n"
        "   -h, --help:\n"
        "       Print this help message and exit.\n"
        "\n"
        "   -e, --explicit:\n"
        "       Print both the number and the character whenever output (.) is called.\n"
        "\n"
        "   -d, --debug:\n"
        "       Run in debug mode, printing information about the pointer every operation.\n"
        "       Displayed in the following manner:\n"
        "       |[integral cell value]|\t[pointer]\t[<-]\n"
        "       Displayed for the the cell before the current pointer, the current pointer,\n"
        "       and the cell after the current pointer, if available.\n";
}


int parse_flags(int argc, char* const argv[], Flags& flags) {
    flags.explicit_output = false;
    flags.debug_mode = false;


    // Command-line flags accepted by this program.
    static struct option flag_options[] = {
        {"explicit",            no_argument,        0, 'e'},
        {"debug",               no_argument,        0, 'd'},
        {"help",                no_argument,        0, 'h'},
        {0, 0, 0, 0}
    };

    int option_index;
    char flag_char;

    // Parse flags entered by the user.
    while (true) {
        flag_char = getopt_long(argc, argv, "-e:dh:", flag_options, &option_index);

        // Detect the end of the options.
        if (flag_char == -1) {
            break;
        }

        switch (flag_char) {
            case 'e':
                flags.explicit_output = true;
                break;

            case 'd':
                flags.debug_mode = true;
                break;

            case 'h':
                return 1;
                break;

            case 1:
                flags.filename = optarg;
                break;

            default:
                return 1;
        }
    }

    if (flags.filename == "") {
        return 1;
    }

    return 0;
}