#include "interpreter.hpp"

Interpreter::Interpreter(Flags flags) {
    this->debug_mode = flags.debug_mode;
    this->explicit_output = flags.explicit_output;
    this->filename = flags.filename;
    this->char_array = std::vector<unsigned char>(30000, 0);
    std::cout << filename << std::endl;
    this->file.open(filename);
}

void Interpreter::run() {
    char current_char;
    if(!this->file.eof() && this->file.good()) {
        
        while(this->file.get(current_char)) {
            //std::cout << "curr char" << current_char << std::endl;

            // Make sure character is functional command (ie not a comment)
            if(this->command_map.find(current_char) != this->command_map.end()) {

                // Print the current command if in debug mode
                if(this->debug_mode && current_char != ' ' && current_char != '\n') {
                    std::cout << this->filename << ":" << this->line << ":" << this->column << ": " << current_char << std::endl;
                }

                // Execute the command
                (this->*(command_map[current_char]))();
            }

            // If it is not a functional command, it is a comment. The rest of the line is ignored
            else{
                std::string temp_line = "";
                std::getline(file, temp_line);
                //std::cout << "temp_line " << temp_line << std::endl;
                this->line++;
                this->column = 0;
            }
            this->temp_pos = file.tellg();
            this->column++;
        }
    }

    else {
        std::cout << "Unable to find file " << this->filename << "." << std::endl;
        exit(1);
    }

    file.close();
}

void Interpreter::begin_loop() {


    //this->file.seekg(-1, std::ios::cur);
    this->loop_begin_pointer = this->temp_pos;
    //std::cout << "loop begin" << this->loop_begin_pointer << std::endl;
    this->loop_begin_line = this->line;
    this->loop_begin_col = this->column;

    this->run();
}

void Interpreter::end_loop() {
    if(this->char_array[this->char_ptr] == 0) {
        this->loop_begin_pointer = -1;
    }

    if(this->loop_begin_pointer > -1){
        this->loop_end_pointer = this->file.tellg();
        this->file.seekg(this->loop_begin_pointer, std::ios::beg);
        //this->file.seekg(-2, std::ios::cur);
        this->line = this->loop_begin_line;
        this->column = this->loop_begin_col;
    }
    else{
        this->loop_end_pointer = -1;
    }
}

void Interpreter::increment_cell() {
    // If the cell value is already 0, return
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

void Interpreter::next_line() {
    this->line++;
    this->column = 0;
}

void Interpreter::next_col() {
    this->column++;
}