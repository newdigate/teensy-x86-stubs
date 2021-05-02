//
// Created by Nicholas Newdigate on 30/04/2021.
//

#ifndef TEENSY_X86_STUBS_TEENSY_MAIN_H
#define TEENSY_X86_STUBS_TEENSY_MAIN_H

void setup();

void loop();

int main() {
    initialize_mock_arduino();
    setup();
    while(true){
        loop();
    }
}

#endif //TEENSY_X86_STUBS_TEENSY_MAIN_H
