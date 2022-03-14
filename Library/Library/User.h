#pragma once
#include<iostream>
#include<cstring>
using namespace std;
class User
{
private:
    string name;
    string pass;
    bool admin;

public:
    friend class Library;

    User();
    User(const string& _name, const string& _pass, bool admin);


    void set_name(string name);

    void set_pass(string pass);

    void set_admin(bool admin);



    const string get_name();

    const string get_pass();

    bool get_admin() const;


    void print() const;
};
#pragma once
