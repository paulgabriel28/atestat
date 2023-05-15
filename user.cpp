/*
 * Fisierul cu comenzile folosite in dreptul utilizatorior
 * Comenzi:
 *   add_user
 *   show_users
 *   remove_user
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "user.h"

using namespace std;

/*
 * Functia care adauga un nou utilizator in biblioteca
 * Parametrii:
 *   nr_users (tip int) - numarul maxim de utilizatori
 *   users (tip user_t) - vectorul de utilizatori
 */
void add_user(int *nr_users, user_t *users)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    char user_nick[50], ver_user_nick[50], ver_user_name[50];
    SetConsoleTextAttribute(h, 7);
    cout << "Enter the ";
    SetConsoleTextAttribute(h, 10);
    cout << "username";
    SetConsoleTextAttribute(h, 7);
    cout << " you want to add to the library and press ";
    SetConsoleTextAttribute(h, 12);
    cout << "'ENTER'";
    SetConsoleTextAttribute(h, 7);
    cout << ": ";
    SetConsoleTextAttribute(h, 11);

    cin.getline(user_nick, 50);
    user_nick[strlen(user_nick)] = '\0';

    SetConsoleTextAttribute(h, 7);

    for (int i = 0; i < strlen(user_nick); i++)
        ver_user_nick[i] = towlower(user_nick[i]);
    ver_user_nick[strlen(user_nick)] = '\0';

    // Verificare utilizatorul de la tastatura cu userii din biblioteca, verificarea se face in litere mici.
    bool verify = 1;
    for (int i = 1; i <= (*nr_users); i++)
    {
        for (int j = 0; j <= strlen(users[i].user_name); j++)
            ver_user_name[j] = users[i].user_name[j];
        ver_user_name[strlen(users[i].user_name)] = '\0';

        if (strcmp(user_nick, users[i].user_name) == 0)
        {
            verify = 0;
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << "This user already registered on library!" << endl;
            break;
        }
    }

    if (verify == 0)
        return;

    // Adaugarea unui nou utilizator cu informatii default.
    (*nr_users)++;

    strcpy(users[(*nr_users)].user_name, user_nick);
    users[(*nr_users)].user_books = 0;
    users[(*nr_users)].total_nr_books = 0;
    users[(*nr_users)].acces = 2;

    strcpy(users[(*nr_users)].book1, "empty");
    strcpy(users[(*nr_users)].book2, "empty");

    SetConsoleTextAttribute(h, 7);
    cout << "The user ";
    SetConsoleTextAttribute(h, 10);
    cout << users[(*nr_users)].user_name;
    SetConsoleTextAttribute(h, 7);
    cout << " [";
    SetConsoleTextAttribute(h, 10);
    cout << "#" << (*nr_users);
    SetConsoleTextAttribute(h, 7);
    cout << "] has been ";
    SetConsoleTextAttribute(h, 14);
    cout << "successfully";
    SetConsoleTextAttribute(h, 7);
    cout << " registred to the library!";
}

/*
 * Functia pentru afisarea utilizatorilor salvati in biblioteca
 * Parametrii:
 *     nr_users (tip int) - numarul total de utilizatori
 *     users (tip user_t) - vectorul cu utilizatorii
 */
void show_users(int nr_users, user_t *users)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    // Verificare daca exista utilizatori in biblioteca.
    if (nr_users == 0)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "There are no registered users!";
        return;
    }

    // Afisarea utilizatorilor cu statisticile fiecaruia.
    SetConsoleTextAttribute(h, 12);
    cout << "[!] ";
    SetConsoleTextAttribute(h, 7);
    cout << "Total users: ";
    SetConsoleTextAttribute(h, 11);
    cout << nr_users << endl;
    SetConsoleTextAttribute(h, 7);
    for (int i = 1; i <= nr_users; i++)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "* ";
        SetConsoleTextAttribute(h, 7);
        cout << "Name: ";
        SetConsoleTextAttribute(h, 10);
        cout << users[i].user_name;
        SetConsoleTextAttribute(h, 7);
        cout << "   |   ";
        cout << "Borrowed books (total): ";
        SetConsoleTextAttribute(h, 10);
        cout << users[i].total_nr_books;
        SetConsoleTextAttribute(h, 7);
        cout << "    |   ";
        cout << "Borrwed books: ";
        SetConsoleTextAttribute(h, 10);
        cout << users[i].user_books;

        // Verificare daca unui utilizator i-a fost modificat accesul, daca a pierdut o carte primeste o avertizare.
        if (users[i].acces <= 1)
        {
            SetConsoleTextAttribute(h, 7);
            cout << "    |   Warnings: ";
            SetConsoleTextAttribute(h, 12);
            cout << 2 - users[i].acces << endl;
        }
        else
            cout << endl;

        if (users[i].user_books > 0)
        {
            if (strcmp(users[i].book1, "empty") != 0)
            {
                SetConsoleTextAttribute(h, 12);
                cout << "         -> Book 1: ";
                SetConsoleTextAttribute(h, 11);
                cout << "'" << users[i].book1 << "'" << endl;
            }

            if (strcmp(users[i].book2, "empty") != 0)
            {
                SetConsoleTextAttribute(h, 12);
                cout << "         -> Book 2: ";
                SetConsoleTextAttribute(h, 11);
                cout << "'" << users[i].book2 << "'" << endl;
            }
        }
    }
}

/*
 * Functia pentru stergerea unui utilizator din biblioteca
 * Parametrii:
 *   nr_users (tip int) - numarul toatl de utilizatori
 *   users (tip user_t) - vectorul de utilizatori
 */
void remove_user(int *nr_users, user_t *users)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    // Verificare daca exista utilizatori in biblioteca.
    if (nr_users == 0)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "There are no registered users!";
        return;
    }

    SetConsoleTextAttribute(h, 7);
    cout << "Enter the ";
    SetConsoleTextAttribute(h, 10);
    cout << "username";
    SetConsoleTextAttribute(h, 7);
    cout << " you want to ";
    SetConsoleTextAttribute(h, 12);
    cout << "remove from the library";
    SetConsoleTextAttribute(h, 7);
    cout << " and press ";
    SetConsoleTextAttribute(h, 10);
    cout << "'ENTER'";
    SetConsoleTextAttribute(h, 7);
    cout << ": ";

    char user_name[50];
    cin.getline(user_name, 50);
    user_name[strlen(user_name)] = '\0';
    bool ver_user = 0;
    int user_id;

    // Cautarea utilizatorului in biblioteca.
    for (int i = 1; i <= (*nr_users); i++)
    {
        if (strcmp(user_name, users[i].user_name) == 0)
        {
            user_id = i;
            ver_user = 1;
        }
    }

    if (ver_user == 0)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "This user does not exist in the library" << endl;
        return;
    }
    else
    {
        // Verificare daca utilizatorul nu are carti pentru a-l putea sterge.
        if (strcmp(users[user_id].book1, "empty") == 0 && strcmp(users[user_id].book2, "empty") == 0)
        {
            // Stergerea utilizatorului din biblioteca.
            for (int i = user_id; i <= (*nr_users); i++)
                users[i] = users[i + 1];

            (*nr_users)--;
            SetConsoleTextAttribute(h, 7);
            cout << "The user '";
            SetConsoleTextAttribute(h, 10);
            cout << user_name;
            SetConsoleTextAttribute(h, 7);
            cout << "' [";
            SetConsoleTextAttribute(h, 10);
            cout << "#" << user_id;
            SetConsoleTextAttribute(h, 7);
            cout << "] has been ";
            SetConsoleTextAttribute(h, 14);
            cout << "successfully";
            SetConsoleTextAttribute(h, 12);
            cout << " removed ";
            SetConsoleTextAttribute(h, 7);
            cout << "from the library!";
        }
        else
        {
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << "This user has borrowed books, takes back the books and then you can remove them!";
        }
    }
}