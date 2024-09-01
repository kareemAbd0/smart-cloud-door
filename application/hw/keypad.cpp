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


Keypad::Keypad(int num): keypad_num(num), file_char(path_char), file_polling(path_polling), file_status(path_status) {
    if (!file_char.is_open()) {
        std::cerr << "Failed to open " << path_char << std::endl;
    }
    if (!file_polling.is_open()) {
        std::cerr << "Failed to open " << path_polling << std::endl;
    }
    if (!file_status.is_open()) {
        std::cerr << "Failed to open " << path_status << std::endl;
    }
}

ERR_STATUS Keypad::get_id(int length, std::string &result) {
    ERR_STATUS err = GOOD;
    set_polling("1");

    std::string id;
    std::string out;

    //status is set to 1 by kernel driver when a key is pressed
    while (id.size() < length) {
        std::string c;
        get_status(out);

        if (out == "1") {
            get_char(c);
            id += c;
            std::cout << "here inside: " << c << std::endl;
            set_status("0");

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    set_status("0");

    set_polling("0");

    result = id;
    return err;
}

ERR_STATUS Keypad::get_char(std::string & result) {
    ERR_STATUS err = GOOD;
    if (file_char.is_open()) {
        file_char.seekg(0);  // Reset file pointer to the beginning
        file_char >> result;
    } else {
        std::cout << "Failed to open " << path_char << std::endl;
        return NO_FILE;
    }

    return err;
}

ERR_STATUS Keypad::get_status( std::string &result) {
    ERR_STATUS err = GOOD;
    if (file_status.is_open()) {
        file_status.seekg(0);  // Reset file pointer to the beginning
        file_status >> result;
    } else {
        std::cout << "Failed to open " << path_status << std::endl;
        return NO_FILE;
    }

    return err;
}

ERR_STATUS Keypad::set_status(const std::string &value) {
    ERR_STATUS err = GOOD;
    if (file_status.is_open()) {
        file_status.seekg(0);  // Reset file pointer to the beginning
        file_status << value;
        file_status.flush();

    } else {
        std::cout << "Failed to open " << path_status << std::endl;
        return NO_FILE;
    }
    return err;
}

ERR_STATUS Keypad::get_polling(std::string &result) {
    ERR_STATUS err = GOOD;
    if (file_polling.is_open()) {
        file_polling.seekg(0);  // Reset file pointer to the beginning
        file_polling >> result;
    } else {
        std::cout << "Failed to open " << path_polling << std::endl;
        return NO_FILE;
    }

    return err;
}


ERR_STATUS Keypad::set_polling(const std::string &value) {
    ERR_STATUS err = GOOD;

    if (file_polling.is_open()) {
        file_polling.seekg(0);  // Reset file pointer to the beginning
        file_polling << value;
        file_polling.flush();
    } else {
        std::cout << "Failed to open " << path_polling << std::endl;
        return NO_FILE;
    }

    return err;
}
