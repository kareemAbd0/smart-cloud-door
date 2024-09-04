// Led.h

#pragma once

#include <string>
#include <fstream>
#include "err.h"


class Led {
public:
    explicit Led(int num);

    ERR_STATUS init();

    ERR_STATUS turn_on();

    ERR_STATUS turn_off();

    ~Led();

    int led_num;

private:
    const std::string PATH_LED = "/sys/class/gpio-led";


    std::string path_direction = PATH_LED + "/led" + std::to_string(led_num) + "/direction";
    std::ofstream file_direction;

    std::string path_value = PATH_LED + "/led" + std::to_string(led_num) + "/value";
    std::ofstream file_value;
};
