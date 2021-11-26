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

#include "interpreter.hpp"

Interpreter::Interpreter(Flags flags) {
    this->debug_mode = flags.debug_mode;
    this->explicit_output = flags.explicit_output;
    this->filename = flags.filename;
    //this->char_array = std::vector<unsigned char>(30000, 0);

    this->file.open(filename);
    if(!this->file.good()) {
        std::cerr << "Unable to find file " << this->filename << std::endl;
        exit(1);
    }
}

void Interpreter::read_from_input() {
    char current_char;
    int line = 1;
    int column = 1;

    while(this->file.get(current_char)) {
        
        if(this->command_map.find(current_char) != this->command_map.end()) {
            struct Command new_command;
            new_command.c = current_char;
            new_command.line = line;
            new_command.col = column;
            this->comm_array.push_back(new_command);
            column++;
        }

        else if (current_char == ' ') {
            column++;
        }

        else if (current_char == '\n') {
            line++;
            column = 1;
        }

        // If it is not a functional command, it is a comment. The rest of the line is ignored
        else{
            std::string temp_line = "";
            std::getline(file, temp_line);
            //std::cout << "temp_line " << temp_line << std::endl;
            line++;
            column = 1;
        }
    }
    file.close();
    this->run();
}


void Interpreter::run() {

    while(this->comm_index < this->comm_array.size()) {
        struct Command curr_command = this->comm_array[this->comm_index];
        (this->*(command_map[curr_command.c]))();

        if(this->debug_mode) {
            print_debug();
        }

        this->comm_index++;
    }
    
}

void Interpreter::print_debug() {

    struct Command command = this->comm_array[this->comm_index];

    // If command is an output, don't print cells.
    // This is because the cell values will not have changed and the display is more clear.
    if(command.c == '.') return;

    // Display current command info
    std::cout << this->filename << ":" << command.line << ":" << command.col << ": " << command.c << "\n" << std::endl;
    
    // Display cell information around the current pointer as integers.
    if(this->char_ptr-2 >= 0){
        std::cout << "|...|\t" << "..." << std::endl;
    }

    if(this->char_ptr-1 >= 0) {
        std::cout << "|" << std::setw(3) << (int)this->char_array[char_ptr-1] << "|\t" << std::setw(0) << this->char_ptr-1 << std::endl;
    }

    std::cout << "|" << std::setw(3) << (int)this->char_array[char_ptr] << "|\t" << std::setw(0) << this->char_ptr << "\t<-" << std::endl;

    if(this->char_ptr+1 < 30000) {
        std::cout << "|" << std::setw(3) << (int)this->char_array[char_ptr+1] << "|\t" << std::setw(0) << this->char_ptr+1 << std::endl;
    }

    if(this->char_ptr+2 < 30000){
        std::cout << "|...|\t" << "...\n" << std::endl;
    }

}

void Interpreter::begin_loop() {
    this->loop_begin_indices.push(this->comm_index);
}

void Interpreter::end_loop() {

    // If the pointer value is not 0, return to the beginning of the loop
    if(this->char_array[this->char_ptr] != 0){
        this->comm_index = this->loop_begin_indices.top();
    }

    // If there is no beginning of this loop, there is invalid syntax
    // I.e ']' came before '['
    else if(this->loop_begin_indices.size() == 0){
        struct Command command = this->comm_array[this->comm_index];
        std::cerr << "Invalid syntax: ']' called before starting '[': \n" << 
        this->filename << ":" << command.line << ":" << command.col << ": " << command.c <<  std::endl;
        exit(1);
    }

    // If the value is 0, end the loop and pop from loop stack
    else{
        this->loop_begin_indices.pop();
    }
}

void Interpreter::increment_cell() {

    // If the cell value is already 255, return
    if(this->char_array[this->char_ptr] == 255){
        std::cerr << "Value Error: Tried to increment cell " << this->char_ptr << " with value 255.\n"
        << "See -h --help for information on cell values." << std::endl;
        
        exit(1);
    }

    this->char_array[this->char_ptr]++;
}

void Interpreter::decrement_cell() {

    std::cout << "decrement called" << std::endl;
    // If the cell value is already 0, return
    if(this->char_array[this->char_ptr] == 0){
        std::cerr << "Value Error: Tried to decrement cell " << this->char_ptr << " with value 0.\n"
        << "See -h --help for information on cell values." << std::endl;
        
        exit(1);
    }

    this->char_array[this->char_ptr]--;
    if(this->debug_mode) {
        std::cout << "Decremented cell " << this->char_ptr << "; new value: " << (int)this->char_array[this->char_ptr] << std::endl;
    }
}

void Interpreter::increment_ptr() {
    if(this->char_ptr == 29999) {
        std::cerr << "Out of Bounds exception: Pointer exceeded memory bounds (>30000). Aborted." << std::endl;
        exit(1);
    }

    this->char_ptr++;
}

void Interpreter::decrement_ptr() {
    if(this->char_ptr == 0) {
        std::cerr << "Out of Bounds exception: Pointer exceeded memory bounds (<0). Aborted." << std::endl;
        exit(1);
    }

    this->char_ptr--;
}

void Interpreter::output() {
    if(this->debug_mode) {
        std::cout << (int)this->char_array[this->char_ptr] << " @ [" << this->char_ptr << "]\n" 
        "OUTPUT:" << std::endl;
    }
    if(this->explicit_output) {
        std::cout << (int)this->char_array[this->char_ptr] << std::endl;
    }
    std::cout << (unsigned char)this->char_array[this->char_ptr] << std::endl;
}

void Interpreter::input() {
    int input = 0;
    std::cin >> input;

    if(input > 255) {
        std::string s_input = std::to_string(input);
        input = (int)s_input[0];
        if(this->debug_mode) {
            std::cout << "User input " << s_input << " greater than 255, truncating to " << input << "." << std::endl;
        }
        this->char_array[this->char_ptr] = input;
        return;        
    }
    if(this->debug_mode) {
        std::cout << "User input " << input << " into cell " << this->char_ptr << "." << std::endl;
    }
    this->char_array[this->char_ptr] = input;
}