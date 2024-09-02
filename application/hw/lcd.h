//
// Created by kareem on 4/13/24.
//

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "err.h"


class Lcd {
public:
    explicit Lcd(int num);

    //init is done in the kernel module
    ERR_STATUS display_text(const std::string &message);

    ERR_STATUS change_position(const std::string &message);

    ERR_STATUS send_command(const std::string &message);

    ERR_STATUS clear_display();

    int lcd_num;

    ~Lcd();

private:
    const std::string PATH_LCD = "/sys/class/lcd_16x2/lcd";

    std::string path_txt = PATH_LCD + "/lcdtxt";
    std::ofstream file_txt;

    std::string path_xy = PATH_LCD + "/lcdpxy";
    std::ofstream file_xy;

    std::string path_cmd = PATH_LCD + "/lcdcmd";
    std::ofstream file_cmd;
};
