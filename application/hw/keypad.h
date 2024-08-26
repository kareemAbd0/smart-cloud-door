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

    ERR_STATUS get_id(int length, int &result);


    ERR_STATUS get_char(char &result);



private:
    int keypad_num;

    //const std::string PATH_KEYPAD = "/sys/class/keypad/";
    const std::string PATH_KEYPAD = "/sys/class/keypad_4x3/keypad";

    std::string path_char = PATH_KEYPAD + "/keypadChar";
    std::ifstream file_char;

    std::string path_polling = PATH_KEYPAD + "/keypadPolling";
    std::ofstream file_polling;

    std::string path_status = PATH_KEYPAD + "/keypadStatus";
    std::fstream file_status;



    ERR_STATUS set_polling(char value);

    ERR_STATUS get_status(char &result);

    ERR_STATUS set_status(char value);

};
