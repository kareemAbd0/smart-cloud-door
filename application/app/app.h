//
// Created by kareem on 25/08/24.
//

#pragma once

#include <iostream>
#include <memory>
#include "../database/database.h"
#include "../hw/lcd.h"
#include "../hw/keypad.h"
#include "../hw/led.h"


class App {
public:
    App(Database &database, Lcd &lcd, Keypad &keypad, Led &led);

    void run_loop();


private:

    Database &database;
    Lcd &lcd;
    Keypad &keypad;
    Led &led;



};
