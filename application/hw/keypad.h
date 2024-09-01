//
// Created by kareem on 22/08/24.
//


#pragma once
#include "err.h"
#include <fstream>
#include <iostream>

class Keypad {
public:
    explicit Keypad(int num);

    ERR_STATUS get_id(int length, std::string &result);


    ERR_STATUS get_char(char &result);

    int keypad_num;

private:
    ERR_STATUS set_polling(char value);

    ERR_STATUS get_status(char &result);

    ERR_STATUS set_status(char value);

    const std::string PATH_KEYPAD = "/sys/class/keypad_4x3/keypad";

    std::string path_char = PATH_KEYPAD + "/keypadChar";
    std::ifstream file_char;

    std::string path_polling = PATH_KEYPAD + "/keypadPolling";
    std::ofstream file_polling;

    std::string path_status = PATH_KEYPAD + "/keypadState";
    std::fstream file_status;
};
