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
    Database db(connection_string, 1);

    db.connect();

    Keypad keypad(1);
    int id = 0;

    keypad.get_id(4,id);

    std::cout << "ID: " << id << std::endl;






    // int id = 1365;
    //
    // VERIFY_RESULT out_result = db.verify_id(id);
    //
    //
    // if (out_result.id_status == ID_STATUS::AUTHORISED) {
    //     std::cout << "Authorised" << std::endl;
    //     db.log_entry(id, true);
    // } else if (out_result.id_status == ID_STATUS::NOT_AUTHORISED) {
    //     std::cout << "Not Authorised" << std::endl;
    //     db.log_entry(id, false);
    // } else if (out_result.id_status == ID_STATUS::NON_EXISTANT) {
    //     db.log_entry(0, false);
    //     std::cout << "This id does not exist" << std::endl;
    // }
    //

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
