//
// Created by kareem on 17/08/24.
//

#include <iostream>
#include <utility>
#include <memory>
#include <soci/soci.h>
#include "database.h"


Database::Database(std::string connection_string, const int door_id) : connection_string(std::move(connection_string)),
                                                                       door_id(door_id) {
}


ERR_STATE Database::connect() {
    try {
        sql = std::make_unique<soci::session>("postgresql", connection_string);
        std::cout << "Connected to database" << std::endl;

        return ERR_STATE::SUCCESS;
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return ERR_STATE::FAILURE;
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
                result = {ID_STATUS::AUTHORISED, ERR_STATE::SUCCESS};
            } else {
                result = {ID_STATUS::NOT_AUTHORISED, ERR_STATE::SUCCESS};
            }
        } else {
            result = {ID_STATUS::NON_EXISTANT, ERR_STATE::SUCCESS};
        }

        return result;
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {ID_STATUS::NOT_AUTHORISED, ERR_STATE::FAILURE};
    }
}


ERR_STATE Database::log_entry(int employee_id, bool access_granted) {
    try {
        std::string access_granted_str = access_granted ? "true" : "false";
        if (employee_id != 0) {
            std::string query = "INSERT INTO AccessLogs (EmployeeID, DoorID, AccessTime, AccessGranted) VALUES (" +
                                std::to_string(employee_id) + ", "
                                + std::to_string(door_id) + ", CURRENT_TIMESTAMP, " + access_granted_str + ")";
            *sql << query;
        } else {
            // If the employee id is 0, then the id does not exist in the database
            std::string query = "INSERT INTO AccessLogs (EmployeeID, DoorID, AccessTime, AccessGranted) VALUES (NULL, "
                                + std::to_string(door_id) + ", CURRENT_TIMESTAMP, " + access_granted_str + ")";
            *sql << query;
        }
        return ERR_STATE::SUCCESS;
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return ERR_STATE::FAILURE;
    }
}

int Database::get_door_id() const {
    return door_id;
}


ERR_STATE Database::send_query(const std::string &query) {
    try {
        *sql << query;
        return ERR_STATE::SUCCESS;
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return ERR_STATE::FAILURE;
    }
}

ERR_STATE Database::retrieve_fname(int employee_id, std::string &name) {
    try {
        *sql << "SELECT EmployeeName FROM Employees WHERE EmployeeID = " << employee_id, soci::into(name);

        //get first name from full name
        name = name.substr(0, name.find(' '));

        return ERR_STATE::SUCCESS;
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return ERR_STATE::FAILURE;
    }
}
