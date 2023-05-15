//   Bibliotecile si fisierele folosite pentru main.cpp.
#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <winuser.h>
#include <conio.h>
#include "book.h"
#include "apps.h"

using namespace std;


// Programu principal.
int main()
{
    // Declararea fisierului logs.txt in care sunt salvate niste log-uri despre program
    ofstream flogs("logs.txt", ios::app);
    flogs << "-> START Program, Date " << current_time() << endl;

    // Functia care coloreaza textul in consola, coloreaza doar textul care este urmat de functia "SetConsoleTextAttribute(<var>, <id_culoare>);", nu coloreaza textul din consola intreaga.
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 7);

    book_t library[100];
    user_t users[100];
    int nr_books;
    int nr_users;

    // Sistem de conectare cu PIN, criptat, la care ai 3 incercari
    // PIN-ul este format din cifre, iar la introducerea unei cifre, se afiseaza o steluta, nu o cifra, dar cifra este salvata.
    cout << "Enter PIN ";
    SetConsoleTextAttribute(h, 2);
    cout << "(8 digits)";
    SetConsoleTextAttribute(h, 7);
    cout << ": ";
    SetConsoleTextAttribute(h, 12);
    char pass[66], ch;
    int nr_ch = 0;
    bool check_login = 1;
    int wrong = 1;
    while (check_login == 1 || wrong >= 3)
    {
        nr_ch = 0;
        for (int i = 0; i < 8; i++)
            pass[i] = ' ';
        int i = 0;
        while (i < 8)
        {
            ch = getch();
            if ((ch >= 48 && ch <= 57 || ch == 27 || ch == 8))
            {
                // Daca apasam pe BackSpace, se sterge cate o steluta.
                if (ch == 8)
                {
                    system("cls");
                    SetConsoleTextAttribute(h, 7);
                    cout << "Enter PIN ";
                    SetConsoleTextAttribute(h, 2);
                    cout << "(8 digits)";
                    SetConsoleTextAttribute(h, 7);
                    cout << ": ";
                    SetConsoleTextAttribute(h, 12);

                    if (nr_ch >= 1)
                    {
                        nr_ch--;
                        i--;
                        for (int j = 0; j < nr_ch; j++)
                            cout << "*";
                    }
                }
                else
                {
                    // Daca pe tasta ESC, programul se inchide.
                    if (ch == 27)
                        return 0;

                    // La introducerea unei cifre, se afiseaza steluta.
                    nr_ch++;
                    pass[i] = ch;
                    cout << "*";
                    i++;
                }
            }
        }

        // Verificarea parolei criptate.
        if (login(pass) == 1)
            check_login = 0;
        else
        {
            cout << endl;
            wrong++;
            if (wrong <= 3)
            {
                SetConsoleTextAttribute(h, 7);
                cout << "Wrong password ";
                SetConsoleTextAttribute(h, 12);
                cout << "[" << wrong << " / 3]";
                SetConsoleTextAttribute(h, 7);
                cout << ", please try again: " << endl;
                cout << "PIN: ";
                SetConsoleTextAttribute(h, 12);
            }
        }

        if (wrong == 3)
            check_login = 0;

        if (wrong > 3)
        {
            SetConsoleTextAttribute(h, 7);
            cout << "You have the wrong password too many times, contact the ";
            SetConsoleTextAttribute(h, 12);
            cout << "administration";
            SetConsoleTextAttribute(h, 7);
            cout << " on " << endl
                 << "'";
            SetConsoleTextAttribute(h, 11);
            cout << "contact@paulgabriel.ro";
            SetConsoleTextAttribute(h, 7);
            cout << "' to solve this problem.";
            Sleep(10000);
            return 0;
        }
    }

    cout << endl
         << endl;
    SetConsoleTextAttribute(h, 7);

    // Se apeleaza functia care citeste din Baza de Date informatiile despre biblioteca.
    start_app(&nr_books, &nr_users, library, users);

    cout << "Welcome to ";
    SetConsoleTextAttribute(h, 10);
    cout << "Virtual Library - Vibry" << endl;

    // Functia cu lista comenzilor.
    commands();

    // Sistemul de comenzi, se opreste doar cand a fost introdusa o comanda corecta.
    char command[50];
    bool ok_ok = 1;
    while (ok_ok != 0)
    {
        cout << endl;
        SetConsoleTextAttribute(h, 7);
        cout << "Type the ";
        SetConsoleTextAttribute(h, 10);
        cout << "command ";
        SetConsoleTextAttribute(h, 7);
        cout << "and press ";
        SetConsoleTextAttribute(h, 10);
        cout << "'ENTER'";
        SetConsoleTextAttribute(h, 7);
        cout << ": ";

        SetConsoleTextAttribute(h, 11);

        cin.getline(command, 50);
        command[strlen(command)] = '\0';
        cout << endl;

        bool verify = 1;
        char ver_command[50];

        // Verificarea comenzilor se face cu caractere mici.
        for (int i = 0; i < strlen(command); i++)
            ver_command[i] = tolower(command[i]);
        ver_command[strlen(command)] = '\0';
        SetConsoleTextAttribute(h, 7);

        // Lista comenzilor si verificarea acestora.
        // La fiecare comanda se apeleaza functia corespunzatoare iar apoi se salveaza in fisierele folosite pentru Baza de Date.
        // 'flogs' este folosit pentru fisierul log-urilor.
        if (strcmp(ver_command, "add_book") == 0 || strcmp(ver_command, "addbook") == 0)
        {
            add_book(&nr_books, library);
            exit_app(nr_users, nr_books, library, users);
            flogs << "Command: add_book, Date " << current_time() << endl;
        }

        else if (strcmp(ver_command, "check_book") == 0 || strcmp(ver_command, "checkbook") == 0)
        {
            check_book(&nr_books, library, users, nr_users);
            flogs << "Command: check_book, Date " << current_time() << endl;
        }

        else if (strcmp(ver_command, "remove_book") == 0 || strcmp(ver_command, "removebook") == 0)
        {
            remove_book(&nr_books, library);
            exit_app(nr_users, nr_books, library, users);
            flogs << "Command: remove_book, Date " << current_time() << endl;
        }

        else if (strcmp(ver_command, "edit_book") == 0 || strcmp(ver_command, "editbook") == 0)
        {
            edit_book(&nr_books, library);
            exit_app(nr_users, nr_books, library, users);
            flogs << "Command: edit_book, Date " << current_time() << endl;
        }

        else if (strcmp(ver_command, "show_books") == 0 || strcmp(ver_command, "showbooks") == 0)
        {
            show_books(nr_books, library);
            flogs << "Command: show_books, Date " << current_time() << endl;
            flogs << "Command: show_books, Date " << current_time() << endl;
        }

        else if (strcmp(ver_command, "add_user") == 0 || strcmp(ver_command, "adduser") == 0)
        {
            add_user(&nr_users, users);
            exit_app(nr_users, nr_books, library, users);
            flogs << "Command: add_user, Date " << current_time() << endl;
        }

        else if (strcmp(ver_command, "borrow") == 0)
        {
            borrow_book(users, library, nr_users, nr_books);
            exit_app(nr_users, nr_books, library, users);
            flogs << "Command: borrow, Date " << current_time() << endl;
        }

        else if (strcmp(ver_command, "return") == 0)
        {
            return_book(users, library, nr_users, nr_books);
            exit_app(nr_users, nr_books, library, users);
            flogs << "Command: return, Date " << current_time() << endl;
        }

        else if (strcmp(ver_command, "lost") == 0)
        {
            lost_book(library, users, &nr_books, nr_users);
            exit_app(nr_users, nr_books, library, users);
            flogs << "Command: lost, Date " << current_time() << endl;
        }

        else if (strcmp(ver_command, "show_users") == 0 || strcmp(ver_command, "showusers") == 0)
        {
            show_users(nr_users, users);
            flogs << "Command: show_users, Date " << current_time() << endl;
        }

        else if (strcmp(ver_command, "remove_user") == 0 || strcmp(ver_command, "removeuser") == 0)
        {
            remove_user(&nr_users, users);
            exit_app(nr_users, nr_books, library, users);
            flogs << "Command: remove_users, Date " << current_time() << endl;
        }

        else if (strcmp(ver_command, "exit") == 0)
        {
            SetConsoleTextAttribute(h, 12);
            cout << "SAVE: ";
            SetConsoleTextAttribute(h, 7);
            cout << "The application has been closed and the data has been saved successfully!";
            exit_app(nr_users, nr_books, library, users);
            ok_ok = 0;
            flogs << "Command: exit, Date " << current_time() << endl;
        }
        else if (strcmp(ver_command, "commands") == 0)
        {
            commands();
            flogs << "Command: commands, Date " << current_time() << endl;
        }
        else
        {
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << "Order entered does not exist, please try again!" << endl;
        }
    }

    return 0;
}
