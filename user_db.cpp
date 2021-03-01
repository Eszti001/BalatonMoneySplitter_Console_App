#include <user_db.h>
#include <sqlite/sqlite3.h>
#include <bits/stdc++.h> 
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <numeric>

user::user()
{
}

user::~user()
{
}

bool user::login(){
    sqlite3*db;
    sqlite3_stmt* stmt;
    sqlite3_open("BalatonSplitter.db", &db);
    
    const unsigned char* ans_user_password;
    bool sign_in_status{false};
    std::string user_name{}, user_password{}, calling_string{}; //Typed by the user

    std::cout << std::boolalpha<< "Please sign in with your user name!" << std::endl;
    std::cin >> user_name;
    std::cout << "Please sign in with your password!" << std::endl;
    std::cin >> user_password;
    calling_string =  "SELECT users.password, users.id_user FROM users WHERE users.username = '" + user_name + "';";

    char arr[calling_string.length() + 1]; 
    strcpy(arr, calling_string.c_str());
    sqlite3_prepare_v2(db, arr, -1, &stmt,0);
    while (sqlite3_step(stmt) !=SQLITE_DONE){
    ans_user_password = sqlite3_column_text(stmt,0);
    ans_user_id_db = sqlite3_column_int(stmt,1);
    ans_user_password_db = std::string(reinterpret_cast<const char*>(ans_user_password));
    }
    if (user_password == ans_user_password_db ){
        return sign_in_status=true;
        }
    else{
        std::cout << "The user name or the password is not valid! Please try again.\n"<< std::endl;
        return sign_in_status=false;
    } 
};

void user::print_sums(){
    sqlite3*db;
    sqlite3_stmt* stmt;
    sqlite3_open("BalatonSplitter.db", &db);
    //Display balances with a general call and manipulate through a vector with STL library
    sqlite3_prepare_v2(db, "SELECT history.id_user, history.payment_cost FROM history;", -1, &stmt,0);
    int id, sum_balance;
    std::vector <int> balances_signed_id{};
    std::vector <int> balances_other_id{};
    int sum_signed_id{};
    int sum_other_id{};
    
    while (sqlite3_step(stmt) !=SQLITE_DONE){
        id = sqlite3_column_int(stmt,0);
        sum_balance = sqlite3_column_int(stmt,1);
        if(id == ans_user_id_db){
            balances_signed_id.push_back(sum_balance);
            }
        else{
            balances_other_id.push_back(sum_balance);
            }
    };
    sum_signed_id= accumulate(balances_signed_id.begin(), balances_signed_id.end(),0 );
    sum_other_id= accumulate(balances_other_id.begin(), balances_other_id.end(),0 );
    std::cout << "Summary balance = " << sum_signed_id << std::endl;
    std::cout << "According to the other user's summary balance, yours is = " << std::showpos <<sum_signed_id-sum_other_id << std::endl;
    std::cout << std::endl; 
}; 

void user::show_history(){
    sqlite3*db;
    sqlite3_stmt* stmt;
    sqlite3_open("BalatonSplitter.db", &db);
    //Show all history
    sqlite3_prepare_v2(db, "SELECT history.id_user, history.paid_item, history.payment_cost, history.payment_date FROM history;", -1, &stmt,0);
    int user_id_history{}; 
    int payment_cost_history{};
    const unsigned char* paid_item_history{}; 
    const unsigned char* payment_date_history{};
    std::string paid_user{};

    while (sqlite3_step(stmt) !=SQLITE_DONE){
        user_id_history = sqlite3_column_int(stmt,0);
        paid_item_history = sqlite3_column_text(stmt,1);
        payment_cost_history = sqlite3_column_int(stmt,2);
        payment_date_history = sqlite3_column_text(stmt,3);
        if(ans_user_id_db==user_id_history){
            paid_user = "Paid by me";
        }
        else{
            paid_user = "Paid by other"; 
        }
        std::cout << std::noshowpos << paid_user << " , Paid item = " << paid_item_history <<" , cost = " << payment_cost_history << " payment data= "<< payment_date_history<< std::endl;
    };
    std::cout << std::endl;
}; 

void user::add_new_item(){
    char *err;
    sqlite3*db;
    sqlite3_open("BalatonSplitter.db", &db);
    std::string paid_item{};
    std::string payment_date{};
    int payment_cost{};
    std::string calling_string{};
    
    //new item form
    std::cin.sync();
    std::cout<<"Please tell me when did the payment made?(YYYY-MM-DD)" << std::endl;
    std::getline(std::cin,payment_date);

    std::cout<<"Please tell me the name of the item(s)?" << std::endl;;
    std::getline(std::cin, paid_item);

    std::cout<<"Please tell me how much was this item(s)?" << std::endl;
    std::cin >> payment_cost;

    //Create new history item
    calling_string =  "BEGIN TRANSACTION; INSERT INTO history ( id_user, paid_item, payment_date, payment_cost ) VALUES ( " + std::to_string(ans_user_id_db) + ", '" + paid_item + "', '" + payment_date + "', " + std::to_string(payment_cost)  + " ); END TRANSACTION;";
    char arr[calling_string.length() + 1]; 
    strcpy(arr, calling_string.c_str());
    sqlite3_exec(db,  arr, NULL, NULL, &err);  
};