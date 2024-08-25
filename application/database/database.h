//
// Created by kareem on 17/08/24.
//

#pragma once

#include <memory>
#include <soci/soci.h>



enum class ER_STATUS { SUCCESS, FAILURE };

enum class ID_STATUS { AUTHORISED, NOT_AUTHORISED, NON_EXISTANT };

struct VERIFY_RESULT {
    ID_STATUS id_status;
    ER_STATUS er_status;
};


class Database {
public:

    Database(std::string connection_string, int door_id);


    ER_STATUS connect();


    VERIFY_RESULT verify_id(int employee_id);

    ER_STATUS log_entry(int employee_id, bool access_granted);

    int get_door_id() const;


    ER_STATUS send_query(const std::string &query);

    ~Database() = default;

private:
    std::string connection_string;
    const int door_id;
    std::unique_ptr<soci::session> sql;
};

