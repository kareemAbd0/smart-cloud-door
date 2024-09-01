#include <iostream>
#include <fstream>
#include "hw/keypad.h"
#include "database/database.h"

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

    db.connect();

    VERIFY_RESULT result = db.verify_id(1365);
    if (result.id_status == ID_STATUS::AUTHORISED) {
        std::cout << "Authorised" << std::endl;
    } else if (result.id_status == ID_STATUS::NOT_AUTHORISED) {
        std::cout << "Not Authorised" << std::endl;
    } else if (result.id_status == ID_STATUS::NON_EXISTANT) {
        std::cout << "This id does not exist" << std::endl;
    }

    std::string name;
    db.retrieve_fname(1365, name);
    std::cout << "Name: " << name << std::endl;

    Keypad keypad(1);
    std::string id;

    keypad.get_id(4,id);

    std::cout << "ID: " << id << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
