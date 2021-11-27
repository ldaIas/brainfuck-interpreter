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
    interpreter.read_from_input();

    return err;
}
