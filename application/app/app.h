//
// Created by kareem on 25/08/24.
//

#pragma once

#include "../database/database.h"
#include "../hw/lcd.h"
#include "../hw/keypad.h"
#include "../hw/led.h"


class App {
public:
    App(Database &database, Lcd &lcd, Keypad &keypad, Led &led);

   [[noreturn]] void run_loop() const;


private:

    Database &database;
    Lcd &lcd;
    Keypad &keypad;
    Led &led;



};
