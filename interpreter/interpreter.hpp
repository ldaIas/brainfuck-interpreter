#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

#include "../flags/flags.hpp"

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
        {' ', next_col},
        {'\n', next_line}
    };


    /**
     *  line:               For debugging. The current line the program is on.
     */
    int line = 1;

    /**
     *  column:             For debugging. The current column the program is on.
     */
    int column = 0;

    /**
     *  loop_begin:         The position in the file a loop begins.
     */
    std::streampos loop_begin_pointer;

    std::streampos temp_pos;

    int loop_begin_line;

    int loop_begin_col;

    /**
     *  loop_end:           The position in the file a loop ends.
     */
    std::streampos loop_end_pointer;

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
    std::vector<unsigned char> char_array;

    std::ifstream file;
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

public:

    Interpreter(Flags);
    // Public methods

    /**
     * run():
     *          Run the input program.
     */
    void run();

};



#endif