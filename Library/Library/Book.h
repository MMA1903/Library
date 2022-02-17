#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <regex>

#include "Cell.h"
#include "Int_cell.h"
#include "Double_cell.h"
#include "String_cell.h"
#include "Formula_cell.h"

using namespace std;
class Book
{
private:
    string author;
    string title;
    string genre;
    string description;
    int year;
    string keywords;
    double rating;
    int number;

public:
    friend class Library;

    Book();
    Book(const string& _author, const string& _title, const string& _genre, const string& _description, int _year, const string& _keywords, double _rating, int _number);



    const string get_author();

    const string get_title();

    const string get_genre();

    const string get_description();

    int get_year() const;

    const string get_keywords();

    double get_rating() const;

    int get_number() const;


    void print() const;
};
