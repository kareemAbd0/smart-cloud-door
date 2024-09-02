#include <iostream>
#include <fstream>
#include "hw/keypad.h"
#include "hw/lcd.h"
#include "hw/led.h"
#include "database/database.h"
#include "app/app.h"
int main() {

    std::ifstream file_con("connection_string.txt");

    std::string connection_string;


    if (file_con.is_open()) {
         std::getline(file_con, connection_string);
        file_con.close();
    }else {
        std::cerr << "Failed to open connection_string.txt" << std::endl;
    }

    std::cout << connection_string << std::endl;
    Database db(connection_string, 2);
    Lcd lcd(1);
    Keypad keypad(1,lcd);
    Led led(1);
    App app(db, lcd, keypad, led);
    app.tester();
    std::cout << "finished testing" << std::endl;
    app.run_loop();

    return 0;
}
