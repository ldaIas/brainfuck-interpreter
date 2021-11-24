
#include <iostream>
#include "flags.hpp"

void print_usage() {
    std::cout <<
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
        "       Run in debug mode, printing information about the pointer every operation.\n";
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