#include"User.h"
User::User()
{
    this->name = "Unknown";

    this->pass = "Unknown";

    this->admin = 0;
}

User::User(const string& _name, const string& _pass, bool admin)
{
    this->name = _name;

    this->pass = _pass;

    this->admin = admin;
}

void User::set_name(string name)
{
    this->name = name;
}

void User::set_pass(string pass)
{
    this->pass = pass;
}

void User::set_admin(bool admin)
{
    this->admin = admin;
}

const string User::get_name()
{
    return this->name;
}

const string User::get_pass()
{
    return this->pass;
}

bool User::get_admin() const
{
    return this->admin;
}

void User::print() const
{
    cout << "Name : " << this->name << endl
        << "Pass : " << this->pass << endl
        << "Admin : " << this->admin << endl;
}
