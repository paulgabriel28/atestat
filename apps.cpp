#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <string>
#include "book.h"

using namespace std;
using namespace chrono;

// Functia folosita pentru scrierea in timp real in fisierul logs.txt, data si ora exacta.
const char *current_time()
{
    auto now = system_clock::now();
    time_t currentTime = system_clock::to_time_t(now);
    const char *rawTimeString = ctime(&currentTime);
    size_t length = strlen(rawTimeString);
    char *timeString = new char[length];
    strcpy(timeString, rawTimeString);
    timeString[length - 1] = '\0';

    return timeString;
}

// Functia care salveaza in fisierele folosite pentru Baza de Date, toate datele din aplicatie + salvare in logs.
void exit_app(int nr_users, int nr_books, book_t *library, user_t *users)
{
    ofstream foutb("books.txt");
    ofstream foutu("users.txt");
    ofstream flogs("logs.txt", ios::app);
    flogs << "Save data, Date: " << current_time() << endl;
    foutb << nr_books << endl;

    if (nr_books > 0)
    {
        for (int i = 1; i <= nr_books; i++)
        {
            foutb << library[i].book_name << endl;
            foutb << library[i].rating << endl;
            foutb << library[i].purchase << endl;
            foutb << library[i].available << endl;
        }
    }
    foutu << nr_users << endl;
    if (nr_users > 0)
    {
        for (int i = 1; i <= nr_users; i++)
        {
            foutu << users[i].user_name << endl;
            foutu << users[i].user_books << endl;
            foutu << users[i].total_nr_books << endl;
            foutu << users[i].acces << endl;
            foutu << users[i].book1 << endl;
            foutu << users[i].book2 << endl;
        }
    }
    flogs.close();
    foutu.close();
    foutb.close();
}

//Functia care citeste din fisierele folosite pentru Baza de Date, toate informatiile despre carti, utilizatri.
void start_app(int *nr_books, int *nr_users, book_t *library, user_t *users)
{
    ifstream finb("books.txt");
    ifstream finu("users.txt");
    ofstream flogs("logs.txt", ios::app);
    flogs << "Read data, Date: " << current_time() << endl;

    char temp[10];
    finb.getline(temp, 10);
    *nr_books = atoi(temp);
    finu.getline(temp, 10);
    *nr_users = atoi(temp);

    if ((*nr_books) > 0)
    {
        for (int i = 1; i <= (*nr_books); i++)
        {
            finb.getline(library[i].book_name, 50);
            finb.getline(temp, 10);
            library[i].rating = atof(temp);
            finb.getline(temp, 10);
            library[i].purchase = atoi(temp);
            finb.getline(temp, 10);
            library[i].available = atoi(temp);
        }
    }

    if ((*nr_users) > 0)
    {
        for (int i = 1; i <= (*nr_users); i++)
        {
            finu.getline(users[i].user_name, 50);
            finu.getline(temp, 10);
            users[i].user_books = atoi(temp);
            finu.getline(temp, 10);
            users[i].total_nr_books = atoi(temp);
            finu.getline(temp, 10);
            users[i].acces = atoi(temp);
            finu.getline(users[i].book1, 50);
            finu.getline(users[i].book2, 50);
        }
    }
    flogs.close();
    finu.close();
    finb.close();
}

// Functia care afiseaza comenzile.
void commands()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(h, 2);
    cout << "-> Commands: " << endl;

    SetConsoleTextAttribute(h, 11);
    cout << "     Books commands: " << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         * add_book ";
    SetConsoleTextAttribute(h, 10);
    cout << "<book_name>" << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         * check_book ";
    SetConsoleTextAttribute(h, 10);
    cout << "<book_name>" << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         * remove_book ";
    SetConsoleTextAttribute(h, 10);
    cout << "<book_name>" << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         * edit_book ";
    SetConsoleTextAttribute(h, 10);
    cout << "<book_name>" << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         * show_books" << endl;

    SetConsoleTextAttribute(h, 2);
    cout << "-----------------------------------------------------" << endl;

    SetConsoleTextAttribute(h, 11);
    cout << "     Users commands:" << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         * add_user ";
    SetConsoleTextAttribute(h, 10);
    cout << "<user_name>" << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         * borrow ";
    SetConsoleTextAttribute(h, 10);
    cout << "<user_name> <book_name>" << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         * return ";
    SetConsoleTextAttribute(h, 10);
    cout << "<user_name> <book_name> <rating>" << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         * lost ";
    SetConsoleTextAttribute(h, 10);
    cout << "<user_name> <book_name>" << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         * remove_user ";
    SetConsoleTextAttribute(h, 10);
    cout << "<user_name>" << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         * show_users" << endl;

    SetConsoleTextAttribute(h, 2);
    cout << "-----------------------------------------------------" << endl;

    SetConsoleTextAttribute(h, 7);
    cout << "         contact" << endl;
    cout << "         exit" << endl;
}

// Functia care cripteaza PIN-ul.
unsigned int hashing(char *a)
{
    ofstream flogs("logs.txt", ios::app);
    flogs << "Hashing, Date: " << current_time() << endl;
    unsigned char *puchar_a = (unsigned char *)a;
    int32_t hash = 538;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c;
    flogs.close();
    return hash;
}

// Functia care verifica daca PIN-ul este corect.
int login(char *pass)
{
    ofstream flogs("logs.txt", ios::app);
    flogs << "Read data, Date: " << current_time() << endl;
    flogs.close();
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    ifstream finp("password.txt");
    int pass_crypt[66];

    finp >> *pass_crypt;

    if (*pass_crypt == hashing(pass))
    {
        cout << endl;
        SetConsoleTextAttribute(h, 7);
        cout << "You have ";
        SetConsoleTextAttribute(h, 10);
        cout << "successfully connected";
        SetConsoleTextAttribute(h, 7);
        cout << "!" << endl;
        return 1;
    }
    return 0;
}