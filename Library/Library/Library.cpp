#include"Library.h"
#include"Book.h"
#include"User.h"

vector<Book*>Library::Books{};
vector<User*>Library::Users{};

Library::Library()
{
    Library::Users;
    Library::Books;

    User* consumer;

    this->login = 0;
    this->open_lib = 0;

    this->file_user_name = "user.txt";
    this->file_book_name = "book.txt";
}

void Library::make_Library()
{
    this->open_lib = 1;
    string line_book = "";
    string value_book = "";

    string line_user = "";
    string value_user = "";

    ifstream my_user_file(this->file_user_name);
    ifstream my_book_file(this->file_book_name);

    if (my_user_file.is_open() && my_book_file.is_open())
    {
        while (getline(my_book_file, line_book))
        {
            string value_book = "";
            string _author = "";
            string _title = "";
            string _genre = "";
            string _description = "";
            int _year = 0;
            string _keywords = "";
            double _rating = 0;
            int _number = 0;
            int j = 0;

            for (auto x : line_book)
            {
                if (x == '/')
                {
                    if (j == 0)
                    {
                        _author = value_book;
                        j++;
                    }
                    else if (j == 1)
                    {
                        _title = value_book;
                        j++;
                    }
                    else if (j == 2)
                    {
                        _genre = value_book;
                        j++;
                    }
                    else if (j == 3)
                    {
                        _description = value_book;
                        j++;
                    }
                    else if (j == 4)
                    {
                        _year = stod(value_book);
                        j++;
                    }
                    else if (j == 5)
                    {
                        _keywords = value_book;
                        j++;
                    }
                    else if (j == 6)
                    {
                        _rating = stod(value_book);
                        j++;
                    }
                    else if (j == 7)
                    {
                        _number = stod(value_book);
                        j++;
                    }
                    value_book = "";
                }
                else
                {
                    value_book = value_book + x;
                }
            }
            Library::Books.push_back(new Book(_author, _title, _genre, _description, _year, _keywords, _rating, _number));
        }

        while (getline(my_user_file, line_user))
        {
            string value_user = "";
            string _name = "";
            string _pass = "";
            bool _admin = 0;
            int j = 0;

            for (auto x : line_user)
            {
                if (x == '/')
                {
                    if (j == 0)
                    {
                        _name = value_user;
                        j++;
                    }
                    else if (j == 1)
                    {
                        _pass = value_user;
                        j++;
                    }
                    else if (j == 2)
                    {
                        _admin = stod(value_user);
                        j++;
                    }
                    value_user = "";
                }
                else
                {
                    value_user = value_user + x;
                }
            }
            Library::Users.push_back(new User(_name, _pass, _admin));
        }
        my_user_file.close();
        my_book_file.close();
        cout << "Successfully opened : " << this->file_user_name << endl;
        cout << "Successfully opened : " << this->file_book_name << endl;
    }
    else
    {
        ofstream outfile_user(file_user_name);
        ofstream outfile_book(file_book_name);
        cout << "You create new Users " << this->file_user_name << endl;
        cout << "You create new Books " << this->file_book_name << endl;
        outfile_user.close();
        outfile_book.close();
    }
}

Library::~Library()
{
    this->login = 0;
    this->open_lib = 0;

    for (int i = 0; i < Library::Users.size(); i++)
    {
        delete Users[i];
    }
    Library::Users.clear();

    for (int i = 0; i < Library::Books.size(); i++)
    {
        delete Books[i];
    }
    Library::Books.clear();
}

void Library::print_user() const
{
    for (int i = 0; i < Library::Users.size(); i++)
    {
        cout << endl;
        this->Library::Users[i]->print();
    }
}

void Library::print_book() const
{
    for (int i = 0; i < Library::Books.size(); i++)
    {
        cout << endl;
        this->Library::Books[i]->print();
    }
}

///////////////////////////////

void Library::load_command()
{
    if (this->open_lib == 0)
    {
        string file_user_name_new = "";
        string file_book_name_new = "";

        cout << ">User file name : ";
        getline(cin, file_user_name_new);

        cout << ">Book file name : ";
        getline(cin, file_book_name_new);

        this->file_user_name = file_user_name_new;
        this->file_book_name = file_book_name_new;

        this->make_Library();
        bool have_admin = 0;

        for (int i = 0; i < Library::Users.size(); i++)
        {
            if (Library::Users[i]->get_name() == "admin")
            {
                if (Library::Users[i]->get_pass() == "i<3c++")
                {
                    have_admin = 1;
                }
            }
        }

        if (have_admin == 0)
        {
            Library::Users.push_back(new User("admin", "i<3c++", 1));
        }

    }
    else
    {
        cout << "Error : You have open file " << endl;
    }
}

void Library::close_command()
{
    if (this->open_lib == 1)
    {
        this->~Library();
    }
    else
    {
        cout << "Error : You don't have open file " << endl;
    }
}

void Library::save_as_command()
{
    if (this->login == 1)
    {
        string file_user_name_new = "";
        string file_book_name_new = "";

        cout << ">User file name : ";
        getline(cin, file_user_name_new);

        cout << ">Book file name : ";
        getline(cin, file_book_name_new);

        ofstream my_user_file(file_user_name_new);
        if (my_user_file.good())
        {
            for (int i = 0; i < Library::Users.size(); i++)
            {
                my_user_file << Library::Users[i]->get_name();
                my_user_file << "/";
                my_user_file << Library::Users[i]->get_pass();
                my_user_file << "/";
                my_user_file << Library::Users[i]->get_admin();
                my_user_file << "/";
                my_user_file << "\n";
            }
            cout << "Users \"" << file_user_name_new << "\" successfully saved." << endl;
        }
        my_user_file.close();

        ofstream my_book_file(file_book_name_new);
        if (my_book_file.good())
        {
            for (int i = 0; i < Library::Books.size(); i++)
            {
                my_book_file << Library::Books[i]->get_author();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_title();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_genre();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_description();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_year();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_keywords();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_rating();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_number();
                my_book_file << "/";
                my_book_file << "\n";
            }
            cout << "Books \"" << file_book_name_new << "\" successfully saved." << endl;
        }
        my_book_file.close();
    }
    else
    {
        cout << "Error : You are not login " << endl;
    }
}

void Library::save_command()
{
    if (this->login == 1)
    {
        ofstream my_user_file(this->file_user_name);
        if (my_user_file.good())
        {
            for (int i = 0; i < Library::Users.size(); i++)
            {
                my_user_file << Library::Users[i]->get_name();
                my_user_file << "/";
                my_user_file << Library::Users[i]->get_pass();
                my_user_file << "/";
                my_user_file << Library::Users[i]->get_admin();
                my_user_file << "/";
                my_user_file << "\n";
            }
            cout << "Users \"" << this->file_user_name << "\" successfully saved." << endl;
        }
        my_user_file.close();

        ofstream my_book_file(this->file_book_name);
        if (my_book_file.good())
        {
            for (int i = 0; i < Library::Books.size(); i++)
            {
                my_book_file << Library::Books[i]->get_author();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_title();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_genre();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_description();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_year();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_keywords();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_rating();
                my_book_file << "/";
                my_book_file << Library::Books[i]->get_number();
                my_book_file << "/";
                my_book_file << "\n";
            }
            cout << "Books \"" << this->file_book_name << "\" successfully saved." << endl;
        }
        my_book_file.close();
    }
    else
    {
        cout << "Error : You are not login " << endl;
    }
}

///////////////////////////////

void Library::add_user()
{
    if (this->login)
    {
        if (this->consumer->get_admin() == 1)
        {


            string name;
            string pass;
            string admin;

            cout << ">Name : ";
            getline(cin, name);

            cout << ">Pass : ";
            getline(cin, pass);

            cout << ">Admin : ";
            getline(cin, admin);
            if (name == "")
            {
                cout << "Registration failed" << endl;
                cout << "You are not enter a name" << endl;
            }
            else
            {
                Library::Users.push_back(new User(name, pass, stod(admin)));
            }
        }
        else
        {
            cout << "Error : You are not ADMIN " << endl;
        }
    }
    else
    {
        cout << "Error : You are not login " << endl;
    }
}

void Library::add_book()
{
    if (this->login)
    {
        if (this->consumer->get_admin() == 1)
        {

            string author;
            string title;
            string genre;
            string description;
            string year;
            string keywords;
            string rating;
            string number;

            cout << ">Author : ";
            getline(cin, author);
            cout << ">Title : ";
            getline(cin, title);
            cout << ">Genre : ";
            getline(cin, genre);
            cout << ">Description : ";
            getline(cin, description);
            cout << ">Year : ";
            getline(cin, year);
            cout << ">Keywords : ";
            getline(cin, keywords);
            cout << ">Rating : ";
            getline(cin, rating);
            cout << ">Number : ";
            getline(cin, number);


            if (author == "")
            {
                cout << "Registration failed" << endl;
                cout << "You are not enter a author" << endl;
            }
            else
            {
                Library::Books.push_back(new Book(author, title, genre, description, stod(year), keywords, stod(rating), stod(number)));
            }
        }
        else
        {
            cout << "Error : You are not ADMIN " << endl;
        }
    }
    else
    {
        cout << "Error : You are not login " << endl;
    }
}

void Library::user_remove()
{
    if (this->login)
    {
        if (this->consumer->get_admin() == 1)
        {
            string name = "";
            cout << ">User Name : ";
            getline(cin, name);

            int index = -1;

            for (int i = 0; i < Library::Users.size(); i++)
            {
                if (Library::Users[i]->get_name() == name)
                {
                    index = i;
                }
            }

            if (index == -1)
            {
                cout << endl;
                cout << ">No User with Name : " << name;
            }
            else
            {
                if (index == Library::Users.size() - 1)
                {
                    delete Library::Users[index];
                    Library::Users.resize(index);
                }
                else
                {
                    Library::Users.erase(Library::Users.begin() + index);
                }
            }

        }
        else
        {
            cout << "Error : You are not ADMIN " << endl;
        }
    }
    else
    {
        cout << "Error : You are not login " << endl;
    }
}

void Library::books_remove()
{
    if (this->login)
    {
        if (this->consumer->get_admin() == 1)
        {
            string number = "";
            cout << ">Number : ";
            getline(cin, number);

            int index = -1;

            for (int i = 0; i < Library::Books.size(); i++)
            {
                if (Library::Books[i]->get_number() == stod(number))
                {
                    index = i;
                }
            }

            if (index == -1)
            {
                cout << endl;
                cout << ">No Book with Number : " << number;
            }
            else
            {
                if (index == Library::Books.size() - 1)
                {
                    delete Library::Books[index];
                    Library::Books.resize(index);
                }
                else
                {
                    Library::Books.erase(Library::Books.begin() + index);
                }
            }

        }
        else
        {
            cout << "Error : You are not ADMIN " << endl;
        }
    }
    else
    {
        cout << "Error : You are not login " << endl;
    }
}

///////////////////////////////

void Library::login_command()
{
    string user_name = "";
    string user_pass = "";
    int index = -1;

    cout << ">User name : ";
    getline(cin, user_name);
    cout << ">Password : ";
    getline(cin, user_pass);
    cout << endl;

    for (int i = 0; i < Library::Users.size(); i++)
    {
        if (Library::Users[i]->get_name() == user_name)
        {
            if (Library::Users[i]->get_pass() == user_pass)
            {
                consumer = Library::Users[i];
                index = i;
            }
        }
    }

    if (index == -1)
    {
        cout << "Something went wrong" << endl;
        cout << "Try again !!!" << endl;
    }
    else
    {
        this->login = 1;
        cout << "Welcome, " << this->consumer->get_name() << "!" << endl;
    }
}

void Library::logout_command()
{
    if (this->login == 1)
    {
        consumer = new User();
        this->login = 0;
        cout << "You logout !!!" << endl;
    }
    else
    {
        cout << "Error : You are not login " << endl;
    }
}

///////////////////////////////

void Library::books_all()
{
    if (this->login)
    {
        for (int i = 0; i < Library::Books.size(); i++)
        {
            cout << this->Library::Books[i]->get_title() << " "
                << this->Library::Books[i]->get_author() << " "
                << this->Library::Books[i]->get_genre() << " "
                << this->Library::Books[i]->get_number() << endl;
        }

    }
    else
    {
        cout << "Error : You are not login " << endl;
    }
}

void Library::books_info()
{
    if (this->login)
    {
        string number = "";
        cout << ">Number : ";
        getline(cin, number);
        cout << endl;

        int index = -1;

        for (int i = 0; i < Library::Books.size(); i++)
        {
            if (Library::Books[i]->get_number() == stod(number))
            {
                index = i;
            }
        }

        if (index == -1)
        {
            cout << ">No Book with Number : " << number;
        }
        else
        {
            Library::Books[index]->print();
        }

    }
    else
    {
        cout << "Error : You are not login " << endl;
    }
}

void Library::books_find()
{
    if (this->login)
    {
        string option = "";
        cout << ">Option (title, author, tag) : ";
        getline(cin, option);

        string text = "";
        cout << ">Text : ";
        getline(cin, text);
        cout << endl;

        if (option == "title")
        {
            for (int i = 0; i < Library::Books.size(); i++)
            {
                if (strstr(Library::Books[i]->get_title().c_str(), text.c_str()))
                {
                    Library::Books[i]->print();
                    cout << endl;
                }
            }
        }
        else if (option == "author")
        {
            for (int i = 0; i < Library::Books.size(); i++)
            {
                if (strstr(Library::Books[i]->get_author().c_str(), text.c_str()))
                {
                    Library::Books[i]->print();
                    cout << endl;
                }
            }

        }
        else if (option == "tag")
        {
            for (int i = 0; i < Library::Books.size(); i++)
            {
                if (strstr(Library::Books[i]->get_keywords().c_str(), text.c_str()))
                {
                    Library::Books[i]->print();
                    cout << endl;
                }
            }

        }
        else
        {
            cout << "Error : Wrong Option " << endl;
        }

    }
    else
    {
        cout << "Error : You are not login " << endl;
    }
}

void Library::books_sort()
{
    if (this->login)
    {
        string option = "";
        cout << ">Option (title, author, year, rating) : ";
        getline(cin, option);

        string text = "";
        cout << ">asc or desc : ";
        getline(cin, text);
        cout << endl;

        Book* helper;

        if (option == "title")
        {
            for (int i = 0; i < Library::Books.size(); i++)
            {
                for (int j = i; j < Library::Books.size() - 1; j++)
                {
                    if (Library::Books[j]->get_title() > Library::Books[j + 1]->get_title())
                    {
                        helper = Library::Books[j];
                        Library::Books[j] = Library::Books[j + 1];
                        Library::Books[j + 1] = helper;
                    }
                }
            }
            if (text == "desc")
            {
                for (int i = Library::Books.size() - 1; 0 <= i; i--)
                {
                    cout << endl;
                    Library::Books[i]->print();
                }

            }
            else
            {
                this->print_book();
            }
        }
        else if (option == "author")
        {
            for (int i = 0; i < Library::Books.size(); i++)
            {
                for (int j = i; j < Library::Books.size() - 1; j++)
                {
                    if (Library::Books[j]->get_author() > Library::Books[j + 1]->get_author())
                    {
                        helper = Library::Books[j];
                        Library::Books[j] = Library::Books[j + 1];
                        Library::Books[j + 1] = helper;
                    }
                }
            }
            if (text == "desc")
            {
                for (int i = Library::Books.size() - 1; 0 <= i; i--)
                {
                    cout << endl;
                    Library::Books[i]->print();
                }

            }
            else
            {
                this->print_book();
            }
        }
        else if (option == "year")
        {
            for (int i = 0; i < Library::Books.size(); i++)
            {
                for (int j = i; j < Library::Books.size() - 1; j++)
                {
                    if (Library::Books[j]->get_year() > Library::Books[j + 1]->get_year())
                    {
                        helper = Library::Books[j];
                        Library::Books[j] = Library::Books[j + 1];
                        Library::Books[j + 1] = helper;
                    }
                }
            }
            if (text == "desc")
            {
                for (int i = Library::Books.size() - 1; 0 <= i; i--)
                {
                    cout << endl;
                    Library::Books[i]->print();
                }

            }
            else
            {
                this->print_book();
            }

        }
        else if (option == "rating")
        {
            for (int i = 0; i < Library::Books.size(); i++)
            {
                for (int j = i; j < Library::Books.size() - 1; j++)
                {
                    if (Library::Books[j]->get_rating() > Library::Books[j + 1]->get_rating())
                    {
                        helper = Library::Books[j];
                        Library::Books[j] = Library::Books[j + 1];
                        Library::Books[j + 1] = helper;
                    }
                }
            }
            if (text == "desc")
            {
                for (int i = Library::Books.size() - 1; 0 <= i; i--)
                {
                    cout << endl;
                    Library::Books[i]->print();
                }

            }
            else
            {
                this->print_book();
            }

        }
        else
        {
            cout << "Error : Wrong Option " << endl;
        }

    }
    else
    {
        cout << "Error : You are not login " << endl;
    }
}

///////////////////////////////

void Library::activate()
{
    this->make_Library();
    bool have_admin = 0;

    for (int i = 0; i < Library::Users.size(); i++)
    {
        if (Library::Users[i]->get_name() == "admin")
        {
            if (Library::Users[i]->get_pass() == "i<3c++")
            {
                have_admin = 1;
            }
        }
    }

    if (have_admin == 0)
    {
        Library::Users.push_back(new User("admin", "i<3c++", 1));
    }

    const string exit = R"(^exit$)";
    const string load = R"(^load$)";
    const string close = R"(^close$)";
    const string save = R"(^save$)";
    const string help = R"(^help$)";
    const string saveas = R"(^saveas$)";

    const string add_user_command = R"(^adduser$)";
    const string add_book_command = R"(^addbook$)";
    const string remove_user_command = R"(^removeuser$)";
    const string remove_book_command = R"(^removebook$)";

    const string login_com = R"(^login$)";
    const string logout_com = R"(^logout$)";

    const string books_all = R"(^booksall$)";
    const string books_info = R"(^booksinfo$)";
    const string books_find = R"(^booksfind$)";
    const string books_sort = R"(^bookssort$)";

    const sregex_iterator end;

    const regex exit_pattern = regex(exit);
    const regex load_pattern = regex(load);
    const regex close_pattern = regex(close);
    const regex save_pattern = regex(save);
    const regex help_pattern = regex(help);
    const regex saveas_pattern = regex(saveas);

    const regex add_user_command_pattern = regex(add_user_command);
    const regex add_book_command_pattern = regex(add_book_command);
    const regex remove_user_command_pattern = regex(remove_user_command);
    const regex remove_book_command_pattern = regex(remove_book_command);

    const regex login_com_pattern = regex(login_com);
    const regex logout_com_pattern = regex(logout_com);

    const regex books_all_pattern = regex(books_all);
    const regex books_info_pattern = regex(books_info);
    const regex books_find_pattern = regex(books_find);
    const regex books_sort_pattern = regex(books_sort);

    sregex_iterator iter;

    string text;
    while (true)
    {
        cout << ">";
        getline(cin, text);

        if ((iter = sregex_iterator(text.begin(), text.end(), exit_pattern)) != end)
        {
            this->~Library();
            cout << "exiting..." << endl;
            break;
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), load_pattern)) != end)
        {
            this->load_command();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), close_pattern)) != end)
        {
            this->close_command();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), save_pattern)) != end)
        {
            this->save_command();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), help_pattern)) != end)
        {
            cout << " ::: ALL COMMANDS ::: " << endl
                << "load, close, save, saveas, exit, help<--- work with files" << endl
                << "login, logout <--- START commands" << endl
                << "booksall, booksinfo, booksfind, bookssort <--- for all users" << endl
                << "adduser, addbook, removeuser, removebook <--- for ADMINS";
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), saveas_pattern)) != end)
        {
            this->save_as_command();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), add_user_command_pattern)) != end)
        {
            this->add_user();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), add_book_command_pattern)) != end)
        {
            this->add_book();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), remove_user_command_pattern)) != end)
        {
            this->user_remove();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), remove_book_command_pattern)) != end)
        {
            this->books_remove();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), login_com_pattern)) != end)
        {
            this->login_command();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), logout_com_pattern)) != end)
        {
            this->logout_command();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), books_all_pattern)) != end)
        {
            this->books_all();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), books_info_pattern)) != end)
        {
            this->books_info();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), books_find_pattern)) != end)
        {
            this->books_find();
        }
        else if ((iter = sregex_iterator(text.begin(), text.end(), books_sort_pattern)) != end)
        {
            this->books_sort();
        }
        else
        {
            cout << "Error : invalid command syntax." << endl;
        }
        cout << endl;
    }
}
