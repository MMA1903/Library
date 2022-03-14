#pragma once
#include"User.h"
#include"Book.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <regex>
using namespace std;
class Library
{
    static vector<User*> Users;
    static vector<Book*> Books;

    User* consumer;

    bool login;
    bool open_lib;

    string file_user_name;
    string file_book_name;

public:
    Library();

    void make_Library();

    ~Library();

    void print_user() const;

    void print_book() const;

    ///////////////////////////////

    void load_command();

    void close_command();

    void save_as_command();

    void save_command();

    ///////////////////////////////

    void add_user();//da

    void add_book();//da

    void user_remove();

    void books_remove();

    ///////////////////////////////

    void login_command();//da

    void logout_command();//da

    ///////////////////////////////

    void books_all();

    void books_info();

    void books_find();

    void books_sort();

    ///////////////////////////////

    void activate();
};
