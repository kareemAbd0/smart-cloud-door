//
// Created by kareem on 4/13/24.
//

#include <fstream>
#include <iostream>
#include "lcd.h"


Lcd::Lcd(int num) : lcd_num(num), file_txt(path_txt), file_xy(path_xy), file_cmd(path_cmd) {
    if (!file_txt.is_open()) {
        std::cerr << "Failed to open " << path_txt << std::endl;
    }
    if (!file_xy.is_open()) {
        std::cerr << "Failed to open " << path_xy << std::endl;
    }
    if (!file_cmd.is_open()) {
        std::cerr << "Failed to open " << path_cmd << std::endl;
    }
};


ERR_STATUS Lcd::display_text(const std::string &message) {
    ERR_STATUS err = GOOD;
    if (file_txt.is_open()) {
        file_txt.seekp(0); // Reset file pointer to the beginning
        file_txt << message;
        file_txt.flush();
    } else {
        std::cout << "Failed to open " << path_txt << std::endl;
        return NO_FILE;
    }
    return err;
}

ERR_STATUS Lcd::change_position(const std::string &message) {
    ERR_STATUS err = GOOD;

    if (message.size() != 2 || !isdigit(message[0]) || !isdigit(message[1]) || message[0] > '2' || message[1] > '5' ||
        message[1] < '0' || message[0] < '1') {
        std::cout << "Invalid postion " << std::endl;
        return FAIL;
    }


    if (file_xy.is_open()) {
        file_xy.seekp(0);
        file_xy << message;
        file_xy.flush();
    } else {
        std::cout << "Failed to open " << path_xy << std::endl;
        return NO_FILE;
    }
    return err;
}


ERR_STATUS Lcd::send_command(const std::string &message) {
    ERR_STATUS err = GOOD;

    if (file_cmd.is_open()) {
        file_cmd.seekp(0);
        file_cmd << message;
        file_cmd.flush();
    } else {
        std::cout << "Failed to open " << path_cmd << std::endl;
        return NO_FILE;
    }
    return err;
}

ERR_STATUS Lcd::clear_display() {
    ERR_STATUS err = GOOD;
    if (file_cmd.is_open()) {
        file_cmd.seekp(0);
        file_cmd << "0x01";
        file_cmd.flush();
    } else {
        std::cout << "Failed to open " << path_cmd << std::endl;
        return NO_FILE;
    }
    return err;
}

Lcd::~Lcd() {
    file_txt.close();
    file_xy.close();
    file_cmd.close();
}
