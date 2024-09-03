//
// Created by kareem on 25/08/24.
//


#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "app.h"

App::App(Database &database, Lcd &lcd, Keypad &keypad, Led &led): database(database), lcd(lcd), keypad(keypad),
                                                                  led(led) {
}

[[noreturn]] void App::run_loop() const {
    while (true) {
        std::string id;
        std::string name;
        if (database.connect() == ERR_STATE::SUCCESS) {
            std::cout << "Connected to database" << std::endl;
        } else {
            std::cout << "Failed to connect to database" << std::endl;
        }

        lcd.clear_display();

        if (keypad.get_id(4, id) == GOOD) {
            std::cout << "ID: " << id << std::endl;
        } else {
            std::cout << "Failed to get id" << std::endl;
        }

        lcd.clear_display();


        VERIFY_RESULT result = database.verify_id(std::stoi(id));


        if (result.id_status == ID_STATUS::AUTHORISED) {
            database.retrieve_fname(std::stoi(id), name);
            lcd.display_text("Authorised");
            std::this_thread::sleep_for(std::chrono::seconds(2));
            lcd.clear_display();

            lcd.display_text("cloud logging..");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            lcd.clear_display();

            lcd.display_text("Welcome " + name);
            led.turn_on();
            database.log_entry(std::stoi(id), true);
            std::cout << "Authorised" << std::endl;
        } else if (result.id_status == ID_STATUS::NOT_AUTHORISED) {
            lcd.display_text("Not Authorised");
            std::this_thread::sleep_for(std::chrono::seconds(2));
            lcd.clear_display();

            lcd.display_text("cloud logging..");
            database.log_entry(std::stoi(id), false);
            std::cout << "Not Authorised" << std::endl;
        } else if (result.id_status == ID_STATUS::NON_EXISTANT) {
            lcd.display_text("This ID does");
            lcd.change_position("20");
            lcd.display_text("not exist");
            std::this_thread::sleep_for(std::chrono::seconds(2));
            lcd.clear_display();

            lcd.display_text("cloud logging..");
            database.log_entry(0, false);
            std::cout << "This id does not exist" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
        led.turn_off();
    }
}
