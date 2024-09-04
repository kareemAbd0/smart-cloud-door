//
// Created by kareem on 17/08/24.
//

#pragma once

#include <memory>
#include <soci/soci.h>


enum class ERR_STATE { SUCCESS, FAILURE };

enum class ID_STATUS { AUTHORISED, NOT_AUTHORISED, NON_EXISTANT };

struct VERIFY_RESULT {
    ID_STATUS id_status;
    ERR_STATE er_status;
};


class Database {
public:
    Database(std::string connection_string, int door_id);


    ERR_STATE connect();


    VERIFY_RESULT verify_id(int employee_id) const;

    ERR_STATE log_entry(int employee_id, bool access_granted) const;

    int get_door_id() const;


    ERR_STATE send_query(const std::string &query) const;

    ERR_STATE retrieve_fname(int employee_id, std::string &name) const;

    ~Database() = default;

private:
    std::string connection_string;
    const int door_id;
    std::unique_ptr<soci::session> sql;
};
