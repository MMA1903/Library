#include"Book.h"

Book::Book()
{
    this->author = "";

    this->title = "";

    this->genre = "";

    this->description = "";

    this->year = 0;

    this->keywords = "";

    this->rating = 0;

    this->number = 0;
}

Book::Book(const string& _author, const string& _title, const string& _genre, const string& _description, int _year, const string& _keywords, double _rating, int _number)
{
    this->author = _author;

    this->title = _title;

    this->genre = _genre;

    this->description = _description;

    this->year = _year;

    this->keywords = _keywords;

    this->rating = _rating;

    this->number = _number;
}

const string Book::get_author()
{
    return this->author;
}

const string Book::get_title()
{
    return this->title;
}

const string Book::get_genre()
{
    return this->genre;
}

const string Book::get_description()
{
    return this->description;
}

int Book::get_year() const
{
    return this->year;
}

const string Book::get_keywords()
{
    return this->keywords;
}

double Book::get_rating() const
{
    return this->rating;
}

int Book::get_number() const
{
    return this->number;
}

void Book::print() const
{
    cout << setw(2) << "|";
    cout << setw(15) << this->author << setw(2) << "|";
    cout << setw(15) << this->title << setw(2) << "|";
    cout << setw(15) << this->genre << setw(2) << "|";
    cout << setw(15) << this->description << setw(2) << "|";
    cout << setw(5) << this->year << setw(2) << "|";
    cout << setw(15) << this->keywords << setw(2) << "|";
    cout << setw(3) << this->rating << setw(2) << "|";
    cout << setw(3) << this->number << setw(2) << "|";
}
