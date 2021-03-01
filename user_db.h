#ifndef _USER_DB_H_
#define _USER_DB_H_
#include <string>

class user
{
private: 
    std::string ans_user_password_db{};
    int ans_user_id_db{};
public:
    user();
    ~user();
    bool login();
    void print_sums();
    void show_history(); 
    void add_new_item();
};
#endif // _USER_DB_H_
