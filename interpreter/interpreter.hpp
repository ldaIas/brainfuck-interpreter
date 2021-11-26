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
     *  Decrement the cell.
     */
    void decrement_cell();
    
    /**
     *  Increment the cell.
     */
    void increment_cell();

    /**
     *  Decrement the pointer.
     */
    void decrement_ptr();
    
    /**
     *  Increment the pointer.
     */
    void increment_ptr();

    /**
     *  Output the current cell.
     */
    void output();

    /**
     *  Get input for the current cell. Truncates inputs larger than 1 byte to the first number.
     */
    void input();

    /**
     *  Increment tracking variables for a new line.
     */
    void next_line();

    void begin_loop();

    void end_loop();

    void next_col();

    void print_debug(struct Command);

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