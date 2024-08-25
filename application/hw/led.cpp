//
// Created by kareem on 4/13/24.
//

#include <string>
#include <fstream>
#include <iostream>
#include "led.h"


Led::Led(int num) : led_num(num), file_direction(path_direction), file_value(path_value) {
    if (!file_direction.is_open()) {
        std::cerr << "Failed to open " << path_direction << std::endl;
    }
    if (!file_value.is_open()) {
        std::cerr << "Failed to open " << path_value << std::endl;
    }

};


ERR_STATUS Led::init() {
    //with error checking
    ERR_STATUS err = GOOD;

    if (file_direction.is_open()) {
        file_direction << "out";
    } else {
        std::cout << "Failed to open " << path_direction << std::endl;
        return NO_FILE;
    }
    return err;
}


ERR_STATUS Led::turn_on() {
    ERR_STATUS err = GOOD;

    if (file_value.is_open()) {
        file_value << "1";
    } else {
        std::cout << "Failed to open " << path_value << std::endl;
        return NO_FILE;
    }
    return err;
}

ERR_STATUS Led::turn_off() {
    ERR_STATUS err = GOOD;
    if (file_value.is_open()) {
        file_value << "0";
    } else {
        std::cout << "Failed to open " << path_value << std::endl;
        return NO_FILE;
    }
    return err;
}

Led::~Led() {

    file_direction.close();
    file_value.close();
}


