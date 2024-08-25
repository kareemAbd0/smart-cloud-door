//
// Created by kareem on 17/08/24.
//

#include <iostream>
#include <utility>
#include <memory>
#include <soci/soci.h>
#include <soci/odbc/soci-odbc.h>
#include "database.h"


Database::Database(std::string connection_string, const int door_id) : connection_string(std::move(connection_string)),
                                                                       door_id(door_id) {
}


ER_STATUS Database::connect() {
    try {
        sql = std::make_unique<soci::session>(soci::session(soci::odbc, connection_string));
        std::cout << "Connected to database" << std::endl;

        return ER_STATUS::SUCCESS;
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return ER_STATUS::FAILURE;
    }
}


VERIFY_RESULT Database::verify_id(int employee_id) {
    try {
        VERIFY_RESULT result{};
        int count, employee_department_id, door_department_id;

        *sql << "SELECT COUNT(*) FROM Employees WHERE EmployeeID =  " << employee_id, soci::into(count);

        if (count > 0) {
            *sql << "SELECT DepartmentID FROM Employees WHERE EmployeeID = " << employee_id, soci::into(
                employee_department_id);
            *sql << "SELECT DepartmentID FROM Doors WHERE DoorID = " << door_id, soci::into(door_department_id);

            if (employee_department_id == door_department_id) {
                result = {ID_STATUS::AUTHORISED, ER_STATUS::SUCCESS};
            } else {
                result = {ID_STATUS::NOT_AUTHORISED, ER_STATUS::SUCCESS};
            }
        } else {
            result = {ID_STATUS::NON_EXISTANT, ER_STATUS::SUCCESS};
        }

        return result;
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {ID_STATUS::NOT_AUTHORISED, ER_STATUS::FAILURE};
    }
}


ER_STATUS Database::log_entry(int employee_id, bool access_granted) {

    try {
        if (employee_id != 0) {
            std::string query = "INSERT INTO AccessLogs (EmployeeID, DoorID, AccessTime, AccessGranted) VALUES (" +
                                std::to_string(employee_id) + ", "
                                + std::to_string(door_id) + ", GETDATE(), " + std::to_string(access_granted) + ")";
            *sql << query;
        } else {


            // If the employee id is 0, then the id does not exist in the database
            std::string query = "INSERT INTO AccessLogs (EmployeeID, DoorID, AccessTime, AccessGranted) VALUES (NULL, "
                                + std::to_string(door_id) + ", GETDATE(), " + std::to_string(access_granted) + ")";
            *sql << query;
        }
        return ER_STATUS::SUCCESS;
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return ER_STATUS::FAILURE;
    }
}

int Database::get_door_id() const {
    return door_id;
}


ER_STATUS Database::send_query(const std::string &query) {
    try {
        *sql << query;
        return ER_STATUS::SUCCESS;
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return ER_STATUS::FAILURE;
    }
}






