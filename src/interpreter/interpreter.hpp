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

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <fstream>
#include <string>
#include <map>

#include "../flags/flags.hpp"

// Struct for commands
struct Command {
    char c;
    int line;
    int col;
};

class Interpreter {

private:

    // Private variables

    // Define function type for command map
    typedef void (Interpreter::*function)(void);

    // Map for all the commands
    std::map<char, function> command_map = {
        {'+', increment_cell},
        {'-', decrement_cell},
        {'>', increment_ptr},
        {'<', decrement_ptr},
        {'.', output},
        {',', input},
        {'[', begin_loop},
        {']', end_loop},
    };

    /**
     *  char_ptr:           The pointer to the current memory location.
     */
    int char_ptr = 0;

    /**
     *  debug_mode:         Whether or not to run in debugging mode.
     */
    bool debug_mode = false;

    /**
     *  explicit_output:    Whether or not to explicitly output cells.
     */
    bool explicit_output = false;

    /**
     *  filename:           The name of the file to run.
     */
    std::string filename;

    /**
     *  char_array:         The array of characters to be used in the program.
     */
    unsigned char char_array[30000] = {0};

    std::ifstream file;

    /**
     *  comm_array:         The sequential list of commands given from the file.
     */
    std::vector<struct Command> comm_array;

    /**
     *  comm_index:         The current index of the command array.
     */
    unsigned int comm_index = 0;

    std::stack<int> loop_begin_indices;

    // Private methods

    /**
     *  decrement_cell():
     *          Decrement the cell the current pointer points to.
     */
    void decrement_cell();
    
    /**
     *  increment_cell():
     *          Increment the cell the current pointer points to.
     */
    void increment_cell();

    /**
     *  decrement_ptr(): 
     *          Decrement the current pointer.
     */
    void decrement_ptr();
    
    /**
     *  increment_ptr(): 
     *          Increment the current pointer.
     */
    void increment_ptr();

    /**
     *  output():
     *          Output the ASCII value of the cell the current pointer is at.
     */
    void output();

    /**
     *  input(): 
     *          Get input for the current cell. Truncates inputs larger than 1 byte to the first digit.
     */
    void input();

    /**
     *  next_line(): 
     *          Increment member variable line (used for debugging and tracking).
     */
    void next_line();

    /**
     *  begin_loop():
     *          Sets the position for the beginning of a loop.
     */
    void begin_loop();

    /**
     *  end_loop():
     *          Processes the end of a loop decleration.
     *          Has logic for end loop condition, invalid syntax,
     *          and returning to the start of the loop.
     */
    void end_loop();

    /**
     *  next_col():
     *          Increment the member variable column (used for debugging and tracking).
     */
    void next_col();

    /**
     *  print_debug():
     *          Prints current pointer information, along with the 2 adjacent pointers.
     */
    void print_debug();

public:

    Interpreter(Flags);
    // Public methods

    /**
     *  run():
     *          Run the commands sequentially as given by comm_array.
     */
    void run();

    /**
     *  read_from_input():
     *          Read the input file and load the commands into the comm_array.
     */
    void read_from_input();

};



#endif