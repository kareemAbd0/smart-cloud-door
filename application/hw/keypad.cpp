//
// Created by kareem on 22/08/24.
//

#include <string>
#include <iostream>
#include "keypad.h"



Keypad::Keypad(int num): keypad_num(num) {
}

ERR_STATUS Keypad::get_id(int length, int &result) {



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
