//
// Created by kareem on 22/08/24.
//

#include <string>
#include <iostream>
#include <fstream>
#include "err.h"
#include "thread"
#include "chrono"
#include "keypad.h"


Keypad::Keypad(int num): keypad_num(num) {
}

ERR_STATUS Keypad::get_id(int length, int &result) {
    ERR_STATUS err = GOOD;
    set_polling(1);
    std::string id;
    char out = 0;

    //status is set to 1 by kernel driver when a key is pressed
    while (id.size() < length) {
        char c;
        get_status(out);

        if (out == '1') {
            get_char(c);
            if (c != '0') {
                id += c;
            }
            set_status('0');
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2));

    }

    set_status('0');

    result = std::stoi(id);
    return err;
}

ERR_STATUS Keypad::get_char(char &result) {
    ERR_STATUS err = GOOD;
    if (file_char.is_open()) {
        file_char >> result;
    } else {
        std::cout << "Failed to open " << path_char << std::endl;
        return NO_FILE;
    }

    return err;
}

ERR_STATUS Keypad::get_status(char &result) {
    ERR_STATUS err = GOOD;
    if (file_status.is_open()) {
        file_status >> result;
    } else {
        std::cout << "Failed to open " << path_status << std::endl;
        return NO_FILE;
    }

    return err;
}

ERR_STATUS Keypad::set_status(char value) {
    ERR_STATUS err = GOOD;
    if (file_status.is_open()) {
        file_status << value;
    } else {
        std::cout << "Failed to open " << path_status << std::endl;
        return NO_FILE;
    }
    return err;
}


ERR_STATUS Keypad::set_polling(char value) {
    ERR_STATUS err = GOOD;

    if (file_polling.is_open()) {
        file_polling << value;
    } else {
        std::cout << "Failed to open " << path_polling << std::endl;
        return NO_FILE;
    }

    return err;
}
