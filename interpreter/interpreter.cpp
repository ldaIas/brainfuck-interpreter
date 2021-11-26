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

    for(int i = 0; i < 10; i++){
        std::cout << (int)this->char_array[i] << std::endl;
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

        if(this->debug_mode) {
            print_debug(curr_command);
        }

        (this->*(command_map[curr_command.c]))();

        this->comm_index++;
    }
    
}

void Interpreter::print_debug(struct Command command) {

    // Display current command info
    std::cout << this->filename << ":" << command.line << ":" << command.col << ": " << command.c << "\n" << std::endl;
    // Print the pointer positions around the current one
    /*
    std::cout << std::setw(5);
    if(this->char_ptr-2 >= 0){
        std::cout << "...";
    }
    if(this->char_ptr-1 >= 0){
        std::cout << this->char_ptr-1;
    }

    std::cout << this->char_ptr;

    if(this->char_ptr+1 < 30000){
        std::cout << this->char_ptr+1;
    }
    if(this->char_ptr+2 < 30000){
        std::cout << "...";
    }
    std::cout << std::endl;
    */

    // Print the cell contents at each location
    if(this->char_ptr-2 >= 0){
        std::cout << "...";
    }
    if(this->char_ptr-1 >= 0){
        std::cout << "|" << (int)this->char_array[char_ptr-1] << "|";
    }

    std::cout << "|" << (int)this->char_array[char_ptr] << "|";

    if(this->char_ptr+1 < 30000){
        std::cout << "|" << (int)this->char_array[char_ptr+1] << "|";
    }
    if(this->char_ptr+2 < 30000){
        std::cout << "...";
    }
    std::cout << "\n" << std::endl;
   // std::cout << std::setw(0);

}

void Interpreter::begin_loop() {
    this->loop_begin_indices.push(this->comm_index+1);
}

void Interpreter::end_loop() {
    if(this->char_array[this->char_ptr] == 0){
        this->comm_index = this->loop_begin_indices.top();
    }
    else if(this->loop_begin_indices.size() == 0){
        std::cout << "Invalid syntax" << std::endl;
    }
    else{
        this->loop_begin_indices.pop();
    }
}

void Interpreter::increment_cell() {

    // If the cell value is already 255, return
    if(this->char_array[this->char_ptr] == 255){
        if(this->debug_mode) {
            std::cout << "Tried to increment cell " << this->char_ptr << " with value 255; cell value unchanged." << std::endl;
        }
        return;
    }

    this->char_array[this->char_ptr]++;
    if(this->debug_mode) {
        std::cout << "Incremented cell " << this->char_ptr << "; new value: " << (int)this->char_array[this->char_ptr] << std::endl;
    }
}

void Interpreter::decrement_cell() {

    // If the cell value is already 0, return
    if(this->char_array[this->char_ptr] == 0){
        if(this->debug_mode) {
            std::cout << "Tried to decrement cell " << this->char_ptr << " with value 0; cell value unchanged." << std::endl;
        }
        return;
    }

    this->char_array[this->char_ptr]--;
    if(this->debug_mode) {
        std::cout << "Decremented cell " << this->char_ptr << "; new value: " << (int)this->char_array[this->char_ptr] << std::endl;
    }
}

void Interpreter::increment_ptr() {
    if(this->char_ptr == 29999) {
        std::cout << "error: pointer exceeded memory bounds. Aborted." << std::endl;
        exit(1);
    }

    this->char_ptr++;
    if(this->debug_mode) {
        std::cout << "Pointer incremented to " << this->char_ptr << std::endl;
    }
}

void Interpreter::decrement_ptr() {
    if(this->char_ptr == 0) {
        std::cout << "error: pointer exceeded memory bounds. Aborted." << std::endl;
        exit(1);
    }

    this->char_ptr--;
    if(this->debug_mode) {
        std::cout << "Pointer decremented to " << this->char_ptr << std::endl;
    }
}

void Interpreter::output() {
    if(this->debug_mode) {
        std::cout << (int)this->char_array[this->char_ptr] << " @ [" << this->char_ptr << "]" << std::endl;
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