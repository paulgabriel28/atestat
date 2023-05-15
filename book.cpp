/*
 * Fisierul cu comenzile folosite in dreptul cartilor
 * Comenzi:
 *   add_book
 *   check_book
 *   remove_book
 *   edit_book
 *   show_books
 *   borrow
 *   return
 *   lost
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>
#include <windows.h>
#include "book.h"

using namespace std;

/*
 * Functia care adauga o carte in biblioteca.
 * Parametrii:
 *   nr_books (tip int) - numarul total de cartii
 *   library (tip book_t) - vectorul de carti
 */
void add_book(int *nr_books, book_t *library)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(h, 7);
    cout << "Enter the ";
    SetConsoleTextAttribute(h, 10);
    cout << "name of the book ";
    SetConsoleTextAttribute(h, 7);
    cout << "you want to";
    SetConsoleTextAttribute(h, 2);
    cout << " add to the library ";
    SetConsoleTextAttribute(h, 7);
    cout << "and press 'ENTER': ";
    SetConsoleTextAttribute(h, 11);

    char book_title[50];
    cin.getline(book_title, 50);
    book_title[strlen(book_title)] = '\0';

    bool verify = 1;
    char ver_book_title[50], ver_book_name[50];

    for (int i = 0; i < strlen(book_title); i++)
        ver_book_title[i] = tolower(book_title[i]);
    ver_book_title[strlen(book_title)] = '\0';

    // Sistemul care verifica daca cartea este in biblioteca.
    // * verificarea se face prin indexarea in litere mici a titlului intridos din consola si titlurile din biblioteca.
    for (int i = 1; i <= *nr_books; i++)
    {
        for (int j = 0; j < strlen(library[i].book_name); j++)
            ver_book_name[j] = tolower(library[i].book_name[j]);
        ver_book_name[strlen(library[i].book_name)] = '\0';

        if (strcmp(ver_book_title, ver_book_name) == 0)
        {
            verify = 0;
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << "This book already exists in the library!" << endl;
            break;
        }
    }
    if (verify == 0)
        return;

    // Sistemul care adauga o carte stock in biblioteca, cu variabile standard.
    (*nr_books)++;
    strcpy(library[(*nr_books)].book_name, book_title);
    library[(*nr_books)].rating = 0;
    library[(*nr_books)].purchase = 0;
    library[(*nr_books)].available = 1;

    SetConsoleTextAttribute(h, 7);
    cout << "The book '";
    SetConsoleTextAttribute(h, 10);
    cout << library[(*nr_books)].book_name;
    SetConsoleTextAttribute(h, 7);
    cout << "' [";
    SetConsoleTextAttribute(h, 10);
    cout << "#" << (*nr_books);
    SetConsoleTextAttribute(h, 7);
    cout << "] has been ";
    SetConsoleTextAttribute(h, 14);
    cout << "successfully";
    SetConsoleTextAttribute(h, 7);
    cout << " added to the library!";
}

/*
 * Functia care verifica daca o carte se afla in biblioteca.
 * Parametrii:
 *   nr_books (tip int) - numarul total de carti
 *   library (tip book_t) - vectorul de carti
 *   users (tip user_t) - vectorul de utilizatori
 *   nr_users (tip int) - numarul total de utilizatori
 */
void check_book(int *nr_books, book_t *library, user_t *users, int nr_users)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(h, 7);
    // Verificare daca exista carti in biblioteca.
    if (*nr_books == 0)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "The library is empty!" << endl;
        return;
    }

    SetConsoleTextAttribute(h, 7);
    cout << "Enter the ";
    SetConsoleTextAttribute(h, 10);
    cout << "name of the book";
    SetConsoleTextAttribute(h, 7);
    cout << " you want to ";
    SetConsoleTextAttribute(h, 10);
    cout << " check in the library";
    SetConsoleTextAttribute(h, 7);
    cout << " and press ";
    SetConsoleTextAttribute(h, 10);
    cout << "'ENTER': ";
    SetConsoleTextAttribute(h, 11);

    char book_title[50];
    cin.getline(book_title, 50);
    book_title[strlen(book_title)] = '\0';

    bool verify_book = 0;
    int book_id = 0;

    char ver_book_name[50], ver_book_title[50];

    // Formatarea cartii in litere mici.
    for (int i = 0; i < strlen(book_title); i++)
        ver_book_title[i] = tolower(book_title[i]);
    ver_book_title[strlen(book_title)] = '\0';

    // Verificarea cartii in bibilioteca, in indexarea cartilor in litere mici.
    for (int i = 1; i <= *nr_books; i++)
    {
        for (int j = 0; j < strlen(library[i].book_name); j++)
            ver_book_name[j] = tolower(library[i].book_name[j]);
        ver_book_name[strlen(library[i].book_name)] = '\0';

        if (strcmp(ver_book_title, ver_book_name) == 0)
        {
            verify_book = 1;
            book_id = i;
            break;
        }
    }

    // Afisarea statisticilor despre carte
    if (verify_book == 1)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "[!] ";
        SetConsoleTextAttribute(h, 7);
        cout << "This book exists in the library!" << endl;
        SetConsoleTextAttribute(h, 12);
        cout << "* ";
        SetConsoleTextAttribute(h, 7);
        cout << "Available: ";
        if (library[book_id].available == 1)
        {
            SetConsoleTextAttribute(h, 10);
            cout << "Yes" << endl;
        }
        else
        {
            SetConsoleTextAttribute(h, 12);
            cout << "No" << endl;
        }

        int user_id = -1;
        for (int i = 1; i <= *nr_books; i++)
            if (strcmp(book_title, users[i].book1) == 0)
            {
                user_id = i;
                break;
            }
            else if (strcmp(book_title, users[i].book2) == 0)
            {
                user_id = i;
                break;
            }

        if (user_id != -1)
        {
            SetConsoleTextAttribute(h, 7);
            cout << "* Borrwed by: ";
            SetConsoleTextAttribute(h, 10);
            cout << users[user_id].user_name << endl;
        }

        SetConsoleTextAttribute(h, 7);
        cout << "* Raiting: ";
        SetConsoleTextAttribute(h, 10);
        cout << library[book_id].rating;
    }
    else
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "This book does not exist in the library!" << endl;
        cout << "You can ";
        SetConsoleTextAttribute(h, 12);
        cout << "add this book to library ";
        SetConsoleTextAttribute(h, 7);
        cout << "with the ";
        SetConsoleTextAttribute(h, 11);
        cout << "'add_book'";
        SetConsoleTextAttribute(h, 7);
        cout << " command!" << endl;
    }
}

/*
 * Functia care sterge o carte din biblioteca.
 * Parametrii:
 *   nr_books (tip int) - numarul total de carti
 *   library (tip book_t) - vectorul de carti
 */
void remove_book(int *nr_books, book_t *library)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    // Verificare daca exista carti in biblioteca.
    if ((*nr_books) == 0)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "The library is";
        SetConsoleTextAttribute(h, 12);
        cout << " empty!" << endl;
        return;
    }

    SetConsoleTextAttribute(h, 7);
    cout << "Enter the ";
    SetConsoleTextAttribute(h, 10);
    cout << "name of the book";
    SetConsoleTextAttribute(h, 7);
    cout << " you want to ";
    SetConsoleTextAttribute(h, 10);
    cout << " remove from the library";
    SetConsoleTextAttribute(h, 7);
    cout << " and press ";
    SetConsoleTextAttribute(h, 10);
    cout << "'ENTER': ";
    SetConsoleTextAttribute(h, 11);

    char book_title[50];
    cin.getline(book_title, 50);
    book_title[strlen(book_title)] = '\0';
    bool ver_book = 0;

    char ver_book_title[50], ver_book_name[50];

    for (int i = 0; i < strlen(book_title); i++)
        ver_book_title[i] = tolower(book_title[i]);
    ver_book_title[strlen(book_title)] = '\0';

    int book_id;
    bool verify = 0;

    // Cautarea cartii dorite in biblioteca
    for (int i = 1; i <= *nr_books; i++)
    {
        for (int j = 0; j < strlen(library[i].book_name); j++)
            ver_book_name[j] = tolower(library[i].book_name[j]);
        ver_book_name[strlen(library[i].book_name)] = '\0';

        if (strcmp(ver_book_title, ver_book_name) == 0)
        {
            book_id = i;
            ver_book = 1;
            if (library[book_id].available == 1)
            {
                verify = 1;
                break;
            }
        }
    }

    if (ver_book == 0)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "This book ";
        SetConsoleTextAttribute(h, 12);
        cout << "does not exist";
        SetConsoleTextAttribute(h, 7);
        cout << " in the library!" << endl;
        return;
    }

    if (verify == 1)
    {
        // Rescrierea vectorului cu cartea stearsa.
        for (int i = book_id; i <= (*nr_books); i++)
            library[i] = library[i + 1];

        (*nr_books)--;
        SetConsoleTextAttribute(h, 7);
        cout << "The book '";
        SetConsoleTextAttribute(h, 10);
        cout << book_title;
        SetConsoleTextAttribute(h, 7);
        cout << "' [";
        SetConsoleTextAttribute(h, 10);
        cout << "#" << book_id;
        SetConsoleTextAttribute(h, 7);
        cout << "] has been ";
        SetConsoleTextAttribute(h, 14);
        cout << "successfully removed";
        SetConsoleTextAttribute(h, 7);
        cout << " from the library!" << endl;
    }
    else
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "This book ";
        SetConsoleTextAttribute(h, 12);
        cout << "cannot be removed";
        SetConsoleTextAttribute(h, 7);
        cout << " at this time because ";
        SetConsoleTextAttribute(h, 12);
        cout << "it is on borrowed!" << endl;
        return;
    }
}

/*
 * Functia care afiseaza cartile din biblioteca.
 * Parametrii:
 *   nr_books (tip int) - numarul total de carti
 *   library (tip book_t) - vectorul de carti
 */
void show_books(int nr_books, book_t *library)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    // Verificare daca exista carti in biblioteca.
    if (nr_books == 0)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "No books found in the library!" << endl;
        return;
    }
    SetConsoleTextAttribute(h, 12);
    cout << "[!] ";
    SetConsoleTextAttribute(h, 7);
    cout << "Total books: ";
    SetConsoleTextAttribute(h, 11);
    cout << nr_books << endl;
    // Afisarea cartilor cu statisticile fiecareia
    for (int i = 1; i <= nr_books; i++)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "* ";
        SetConsoleTextAttribute(h, 7);
        cout << "Name: '";
        SetConsoleTextAttribute(h, 10);
        cout << library[i].book_name;
        SetConsoleTextAttribute(h, 7);
        cout << "'   |   ";

        SetConsoleTextAttribute(h, 7);
        cout << "Rating: ";
        SetConsoleTextAttribute(h, 10);
        cout << library[i].rating;
        SetConsoleTextAttribute(h, 7);
        cout << "   |   ";

        SetConsoleTextAttribute(h, 7);
        cout << "Purchase: ";
        SetConsoleTextAttribute(h, 10);
        cout << library[i].purchase;
        SetConsoleTextAttribute(h, 7);
        cout << "   |   ";

        SetConsoleTextAttribute(h, 7);
        cout << "Available: ";
        if (library[i].available == 1)
        {
            SetConsoleTextAttribute(h, 10);
            cout << "Yes";
        }
        else
        {
            SetConsoleTextAttribute(h, 12);
            cout << "No";
        }
        cout << endl;
    }
}

/*
 * Sistemul de imprumutare a unei carti.
 * Parametrii:
 *   users (tip user_t) - vectorul de utilizatori
 *   library (tip book_t) - vectorul de carti
 *   nr_users (tip int) - numarul total de utilizatori
 *   nr_books (tip int) - numarul total de carti
 */
void borrow_book(user_t *users, book_t *library, int nr_users, int nr_books)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    int book_id, user_id;
    char user_nick[50], book_title[50];

    // Verificare daca exista utilizatori in biblioteca.
    if (nr_users == 0)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "There are";
        SetConsoleTextAttribute(h, 12);
        cout << " no registered users";
        SetConsoleTextAttribute(h, 7);
        cout << "!" << endl;
        return;
    }
    // Verificare daca exista carti in biblioteca.
    else if (nr_books == 0)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 12);
        cout << "No books found";
        SetConsoleTextAttribute(h, 7);
        cout << "in the library!" << endl;
        return;
    }

    SetConsoleTextAttribute(h, 7);
    cout << "Enter the ";
    SetConsoleTextAttribute(h, 10);
    cout << "User Name";
    SetConsoleTextAttribute(h, 7);
    cout << ": ";
    SetConsoleTextAttribute(h, 11);

    bool correct_user = 0;
    while (correct_user != 1)
    {
        cin.getline(user_nick, 50);
        user_nick[strlen(user_nick)] = '\0';

        SetConsoleTextAttribute(h, 7);

        bool user_verify = 0;

        // Cautare utilizatori din biblioteca.
        for (int i = 1; i <= nr_users; i++)
            if (strcmp(users[i].user_name, user_nick) == 0)
            {
                user_verify = 1;
                user_id = i;
            }

        // Sistemul de verificare a numelui.
        if (user_verify == 0)
        {
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << "No account was found with this nickname registered in the library!";
            return;
        }
        // Sistemul de verificare daca utilizatorul este banat in biblioteca.
        else if (users[user_id].acces == 0)
        {
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << "You are not allowed to borrow a book, you are banned from this library!";
            return;
        }
        // Sistemul de verificare pentru cartile imprumutate, nu poti avea mai mult de 2 carti imprumutate.
        else if (strcmp(users[user_id].book1, "empty") != 0 && strcmp(users[user_id].book2, "empty") != 0)
        {
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << "You already have 2 books borrowed from the library!";
            return;
        }
        else
        {
            correct_user = 1;
        }
    }

    bool correct_book = 0;

    // Introducerea cartii.
    while (correct_book != 1)
    {
        SetConsoleTextAttribute(h, 7);
        cout << "Enter the ";
        SetConsoleTextAttribute(h, 10);
        cout << "Book Name";
        SetConsoleTextAttribute(h, 7);
        cout << ": ";
        SetConsoleTextAttribute(h, 11);

        cin.getline(book_title, 50);
        book_title[strlen(book_title)] = '\0';

        SetConsoleTextAttribute(h, 7);

        bool book_verify = 0;

        for (int i = 1; i <= nr_books; i++)
            if (strcmp(library[i].book_name, book_title) == 0)
            {
                book_verify = 1;
                book_id = i;
            }

        // Sistemul de verificare a cartii in biblioteca.
        if (book_verify == 0)
        {
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << "This book does not exist in the library!" << endl;
        }
        // Sistemul de verificare pentru disponibilitatea cartii.
        else if (library[book_id].available == 0)
        {
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << "This book is already on borrow!" << endl;
        }
        else
        {
            correct_book = 1;
        }
    }

    if (strcmp(users[user_id].book1, "empty") == 0)
    {
        strcpy(users[user_id].book1, book_title);
    }
    else if (strcmp(users[user_id].book2, "empty") == 0)
    {
        strcpy(users[user_id].book2, book_title);
    }

    // Sistemul de imprumutare a cartii.
    library[book_id].available--;
    users[user_id].user_books++;
    users[user_id].total_nr_books++;
    library[book_id].purchase++;
    SetConsoleTextAttribute(h, 7);
    cout << "User ";
    SetConsoleTextAttribute(h, 10);
    cout << users[user_id].user_name;
    SetConsoleTextAttribute(h, 7);
    cout << " [";
    SetConsoleTextAttribute(h, 10);
    cout << "#" << user_id;
    SetConsoleTextAttribute(h, 7);
    cout << "] borrowed the book '";
    SetConsoleTextAttribute(h, 10);
    cout << book_title;
    SetConsoleTextAttribute(h, 14);
    cout << "' successfully!";
}

/*
 * Functia de returnare a cartii in biblioteca.
 * Parametrii:
 *   users (tip user_t) - vectorul de userii
 *   library (tip book_t) - vectorul de carti
 *   nr_users (tip int) - vectorul de utilizatori
 *   nr_books (tip int) - vectorul de carti
 */
void return_book(user_t *users, book_t *library, int nr_users, int nr_books)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    // Verificare daca exista carti in biblioteca.
    if (nr_users == 0)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "There are no registered users!";
        return;
    }

    // Sistemul care verifica daca exista carti imprumutate
    int verify_available = 0;
    for (int i = 1; i <= nr_books; i++)
        if (library[i].available == 1)
            verify_available++;

    if (verify_available == nr_books)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "There are no borrowed books!";
        return;
    }

    SetConsoleTextAttribute(h, 7);
    cout << "Enter the ";
    SetConsoleTextAttribute(h, 10);
    cout << "User Name";
    SetConsoleTextAttribute(h, 7);
    cout << ": ";
    SetConsoleTextAttribute(h, 11);

    char user_nick[50];
    cin.getline(user_nick, 50);
    user_nick[strlen(user_nick)] = '\0';

    int user_id = -1, nr_users_ver = 0;
    // Sistemul de cautare a utiizatorului in biblioteca
    for (int i = 1; i <= nr_users; i++)
        if (strcmp(users[i].user_name, user_nick) == 0)
        {
            user_id = i;
            break;
        }
        else
        {
            nr_users_ver++;
        }

    if (nr_users_ver == nr_users && user_id == -1)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "This name was not registered in the library!";
        return;
    }

    if (strcmp(users[user_id].book1, "empty") == 0 && strcmp(users[user_id].book2, "empty") == 0)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "You didn't borrow a book from the library!";
        return;
    }

    SetConsoleTextAttribute(h, 7);
    cout << "Enter the ";
    SetConsoleTextAttribute(h, 10);
    cout << "Book Name";
    SetConsoleTextAttribute(h, 7);
    cout << ": ";
    SetConsoleTextAttribute(h, 11);

    char book_title[50];
    cin.getline(book_title, 50);
    book_title[strlen(book_title)] = '\0';

    int book_id = -1, nr_books_ver = 0;
    // Sistemul de cautare a cartii citite de la tastatura in biblioteca
    for (int i = 1; i <= nr_books; i++)
        if (strcmp(library[i].book_name, book_title) == 0)
        {
            book_id = i;
            break;
        }
        else
        {
            nr_books_ver++;
        }

    if (nr_books_ver == nr_books && book_id == -1)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "This book does not exist in the library!";
        return;
    }

    if (library[book_id].available == 1)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "This book is already in the library, has not been borrowed!";
        return;
    }

    SetConsoleTextAttribute(h, 7);
    cout << "Enter the ";
    SetConsoleTextAttribute(h, 11);
    cout << "Book Rating [x / 10]: ." << endl;
    SetConsoleTextAttribute(h, 12);
    cout << "+ 1 = do not recommend the book";
    SetConsoleTextAttribute(h, 7);
    cout << "    |    ";
    SetConsoleTextAttribute(h, 10);
    cout << "10 = recommend the book" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "* enter ";
    SetConsoleTextAttribute(h, 12);
    cout << "0";
    SetConsoleTextAttribute(h, 7);
    cout << " if you do not want to rate this book!" << endl;

    bool succes_rating = 0;
    float book_rating;
    // Adaugarea ratining-ului la cartea returnata (de la 1 la 10).
    while (succes_rating != 1)
    {
        cout << "Rating: ";
        cin >> book_rating;
        cin.get();
        if (book_rating == 0)
        {
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << endl
                 << "You have not set a rating.";
            succes_rating = 1;
        }
        else if (book_rating < 0 || book_rating > 10)
        {
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << endl
                 << "This rating is invalid, try again!";
        }
        else
        {
            SetConsoleTextAttribute(h, 7);
            cout << endl
                 << "The ";
            SetConsoleTextAttribute(h, 10);
            cout << book_rating;
            SetConsoleTextAttribute(h, 7);
            cout << " rating was saved";
            SetConsoleTextAttribute(h, 14);
            cout << " successfully!";
            succes_rating = 1;
        }
    }

    int purchase_rating;
    // Verificare la utilizator pentru a vedea care dintre cele 2 carti trebuie returnata.
    if (strcmp(users[user_id].book1, "empty") != 0)
    {
        strcpy(users[user_id].book1, "empty");
        library[book_id].available++;
        users[user_id].user_books--;
        if (book_rating == 0)
        {
            purchase_rating = library[book_id].purchase - 1;
            library[book_id].rating = (library[book_id].rating + book_rating) / purchase_rating;
        }
        else if (book_rating != 0)
        {
            library[book_id].rating = (library[book_id].rating + book_rating) / library[book_id].purchase;
        }
    }

    else if (strcmp(users[user_id].book2, "empty") != 0)
    {
        strcpy(users[user_id].book2, "empty");
        library[book_id].available++;
        users[user_id].user_books--;
        if (book_rating == 0)
        {
            purchase_rating = library[book_id].purchase - 1;
            library[book_id].rating = (library[book_id].rating + book_rating) / purchase_rating;
        }
        else if (book_rating != 0)
        {
            library[book_id].rating = (library[book_id].rating + book_rating) / library[book_id].purchase;
        }
    }
    cout << endl
         << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "Book '";
    SetConsoleTextAttribute(h, 10);
    cout << book_title;
    SetConsoleTextAttribute(h, 7);
    cout << "'";
    SetConsoleTextAttribute(h, 14);
    cout << " successfully";
    SetConsoleTextAttribute(h, 7);
    cout << " returned by ";
    SetConsoleTextAttribute(h, 10);
    cout << user_nick;
    SetConsoleTextAttribute(h, 7);
    cout << "[";
    SetConsoleTextAttribute(h, 10);
    cout << "#" << user_id;
    SetConsoleTextAttribute(h, 7);
    cout << "]!" << endl;

    cout << "Now the book has an ";
    SetConsoleTextAttribute(h, 10);
    cout << library[book_id].rating;
    SetConsoleTextAttribute(h, 7);
    cout << "/10 rating!";
}

/*
 * Sistemul pentru cartile pierdute.
 * Parametrii:
 *   library (tip book_t) - vectorul de carti
 *   users (tip user_t) - vectorul de utilizatori
 *   nr_books (tip int) - numarurl maxim de carti
 *   nr_users (tip nr_users) - numarul maxim de useri
 */
void lost_book(book_t *library, user_t *users, int *nr_books, int nr_users)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(h, 7);
    cout << "Enter the ";
    SetConsoleTextAttribute(h, 10);
    cout << "User Name";
    SetConsoleTextAttribute(h, 7);
    cout << ": ";
    SetConsoleTextAttribute(h, 11);

    char user_nick[50];
    int nr_users_ver = 0, user_id = -1;
    cin.getline(user_nick, 50);
    user_nick[strlen(user_nick)] = '\0';

    // Cautarea utilizatorului citit de la tastatura.
    for (int i = 1; i <= nr_users; i++)
    {
        if (strcmp(users[i].user_name, user_nick) == 0)
        {
            user_id = i;
            break;
        }
        else
        {
            nr_users_ver++;
        }
    }

    if (nr_users_ver == nr_users && user_id == -1)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "This name was not registered in the library!";
        return;
    }

    SetConsoleTextAttribute(h, 7);
    cout << "Enter the ";
    SetConsoleTextAttribute(h, 10);
    cout << "Book Name";
    SetConsoleTextAttribute(h, 7);
    cout << ": ";
    SetConsoleTextAttribute(h, 11);

    char book_title[50];
    cin.getline(book_title, 50);
    int nr_books_ver = 0, book_id = -1;

    // Cautarea cartii citite de la tastatura.
    for (int i = 1; i <= (*nr_books); i++)
    {
        if (strcmp(library[i].book_name, book_title) == 0)
        {
            book_id = i;
            break;
        }
        else
        {
            nr_books_ver++;
        }
    }
    SetConsoleTextAttribute(h, 7);

    if (nr_books_ver == (*nr_books) && book_id == -1)
    {
        SetConsoleTextAttribute(h, 12);
        cout << "ERROR: ";
        SetConsoleTextAttribute(h, 7);
        cout << "This book does not exist in the library!";
        return;
    }
    // Rescrierea vectorului de carti fara cartea stearsa si sanctionarea persoanei care a pierdut cartea
    for (int i = book_id; i <= (*nr_books); i++)
        library[i] = library[i + 1];

    (*nr_books)--;
    users[user_id].acces--;
    users[user_id].user_books--;

    if (strcmp(users[user_id].book1, book_title) == 0)
        strcpy(users[user_id].book1, "empty");
    else if (strcmp(users[user_id].book2, book_title) == 0)
        strcpy(users[user_id].book2, "empty");

    SetConsoleTextAttribute(h, 7);
    cout << "The book has been ";
    SetConsoleTextAttribute(h, 12);
    cout << "deleted from library";
    SetConsoleTextAttribute(h, 7);
    cout << " and the ";
    SetConsoleTextAttribute(h, 12);
    cout << "person has been warned";
    SetConsoleTextAttribute(h, 7);
    cout << " [";
    SetConsoleTextAttribute(h, 12);
    cout << users[user_id].acces << "/2 ";
    SetConsoleTextAttribute(h, 7);
    cout << "warnings].";
}

/*
 * Functia de editare a unei carti
 * Parametrii:
 *   nr_books (tip int) - numarul total de carti
 *   library (tip book_t) - vectorul de carti
 */
void edit_book(int *nr_books, book_t *library)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    int option;
    char book_title[50], ver_book_title[50], ver_book_name[50];
    bool correct_book = 1, one = 1, ver_book;
    int books = 0, book_id = -1;

    while (correct_book != 0)
    {
        SetConsoleTextAttribute(h, 7);
        cout << "Enter the ";
        SetConsoleTextAttribute(h, 10);
        cout << "Book Name";
        SetConsoleTextAttribute(h, 7);
        cout << ": ";
        SetConsoleTextAttribute(h, 11);

        // Citirea de la tastatura a unei carti pana gaseste cartea in biblioteca.
        cin.getline(book_title, 50);
        book_title[strlen(book_title)] = '\0';
        cout << endl;
        SetConsoleTextAttribute(h, 7);

        // Verificarea cartii cu litere mici
        for (int i = 0; i <= strlen(book_title); i++)
            ver_book_title[i] = tolower(book_title[i]);

        for (int i = 1; i <= *nr_books; i++)
        {
            for (int j = 0; j < strlen(library[i].book_name); j++)
                ver_book_name[j] = tolower(library[i].book_name[j]);
            ver_book_name[strlen(library[i].book_name)] = '\0';

            if (strcmp(ver_book_title, ver_book_name) == 0)
            {
                book_id = i;
                correct_book = 0;
                break;
            }
        }

        // Editarea cartii in functie de optiunea selectata.
        if (book_id >= 0)
        {
            if (books = 1)
            {
                if (one)
                {
                    SetConsoleTextAttribute(h, 12);
                    cout << "[!]";
                    SetConsoleTextAttribute(h, 7);
                    cout << "  Available options:" << endl;

                    SetConsoleTextAttribute(h, 10);
                    cout << " 1";
                    SetConsoleTextAttribute(h, 7);
                    cout << " -> ";
                    SetConsoleTextAttribute(h, 11);
                    cout << "available" << endl;

                    SetConsoleTextAttribute(h, 10);
                    cout << " 2";
                    SetConsoleTextAttribute(h, 7);
                    cout << " -> ";
                    SetConsoleTextAttribute(h, 11);
                    cout << "book_name" << endl;

                    SetConsoleTextAttribute(h, 10);
                    cout << " 3 ";
                    SetConsoleTextAttribute(h, 7);
                    cout << "-> ";
                    SetConsoleTextAttribute(h, 11);
                    cout << "purchase" << endl;

                    SetConsoleTextAttribute(h, 10);
                    cout << " 4 ";
                    SetConsoleTextAttribute(h, 7);
                    cout << "-> ";
                    SetConsoleTextAttribute(h, 11);
                    cout << "rating" << endl;

                    SetConsoleTextAttribute(h, 7);
                    one = 0;
                }

                cout << "Enter option ";
                SetConsoleTextAttribute(h, 10);
                cout << "(ID)";
                SetConsoleTextAttribute(h, 7);
                cout << ": ";
                cin >> option;

                if (option == 1)
                {
                    SetConsoleTextAttribute(h, 7);
                    cout << "You changing value on ";
                    SetConsoleTextAttribute(h, 10);
                    cout << "'Available'";
                    SetConsoleTextAttribute(h, 7);
                    cout << " for book: ";
                    SetConsoleTextAttribute(h, 10);
                    cout << library[book_id].book_name << endl;

                    int value;
                    bool check_value = 1;
                    while (check_value)
                    {
                        SetConsoleTextAttribute(h, 12);
                        cout << "* ";
                        SetConsoleTextAttribute(h, 7);
                        cout << "New value: ";
                        SetConsoleTextAttribute(h, 11);
                        cin >> value;
                        cin.get();

                        SetConsoleTextAttribute(h, 7);

                        if (value == 1 || value == 0)
                        {
                            SetConsoleTextAttribute(h, 7);
                            cout << "The value of ";
                            SetConsoleTextAttribute(h, 10);
                            cout << "'Available'";
                            SetConsoleTextAttribute(h, 7);
                            cout << " has been changed from ";
                            SetConsoleTextAttribute(h, 10);
                            cout << library[book_id].available;
                            SetConsoleTextAttribute(h, 7);
                            cout << " to ";
                            SetConsoleTextAttribute(h, 10);
                            cout << value;

                            library[book_id].available = value;
                            check_value = 0;
                        }
                        else
                        {
                            SetConsoleTextAttribute(h, 12);
                            cout << "ERROR: ";
                            SetConsoleTextAttribute(h, 7);
                            cout << "The value entered is incorrect, please try again." << endl;
                        }
                    }
                }

                else if (option == 2)
                {
                    char new_book_name[50];
                    SetConsoleTextAttribute(h, 7);
                    cout << "You changing ";
                    SetConsoleTextAttribute(h, 10);
                    cout << "'Name'";
                    SetConsoleTextAttribute(h, 7);
                    cout << " for book: ";
                    SetConsoleTextAttribute(h, 10);
                    cout << library[book_id].book_name << endl;

                    SetConsoleTextAttribute(h, 12);
                    cout << "* ";
                    SetConsoleTextAttribute(h, 7);
                    cout << "New name: ";

                    SetConsoleTextAttribute(h, 11);
                    cin.get();
                    cin.getline(new_book_name, 50);
                    new_book_name[strlen(new_book_name)] = '\0';

                    SetConsoleTextAttribute(h, 7);

                    cout << "The name has been changed from ";
                    SetConsoleTextAttribute(h, 10);
                    cout << library[book_id].book_name;
                    SetConsoleTextAttribute(h, 7);
                    cout << " to ";
                    SetConsoleTextAttribute(h, 11);
                    cout << new_book_name;

                    SetConsoleTextAttribute(h, 7);

                    strcpy(library[book_id].book_name, new_book_name);

                    correct_book = 0;
                }

                else if (option == 3)
                {
                    int new_purchase;
                    bool check_purchase = 1;

                    SetConsoleTextAttribute(h, 7);
                    cout << "You changing value on ";
                    SetConsoleTextAttribute(h, 10);
                    cout << "'Purchase'";
                    SetConsoleTextAttribute(h, 7);
                    cout << " for book: ";
                    SetConsoleTextAttribute(h, 10);
                    cout << library[book_id].book_name << endl;

                    while (check_purchase)
                    {
                        SetConsoleTextAttribute(h, 12);
                        cout << "* ";
                        SetConsoleTextAttribute(h, 7);
                        cout << "New value: ";
                        SetConsoleTextAttribute(h, 11);
                        cin >> new_purchase;
                        cin.get();

                        if (new_purchase >= 0)
                        {
                            SetConsoleTextAttribute(h, 7);
                            cout << "The value of ";
                            SetConsoleTextAttribute(h, 10);
                            cout << "'Purchase'";
                            SetConsoleTextAttribute(h, 7);
                            cout << " has been changed from ";
                            SetConsoleTextAttribute(h, 10);
                            cout << library[book_id].purchase;
                            SetConsoleTextAttribute(h, 7);
                            cout << " to ";
                            SetConsoleTextAttribute(h, 10);

                            cout << new_purchase;
                            library[book_id].purchase = new_purchase;
                            check_purchase = 0;
                        }
                        else
                        {
                            SetConsoleTextAttribute(h, 12);
                            cout << "ERROR: ";
                            SetConsoleTextAttribute(h, 7);
                            cout << "The value entered is incorrect, please try again." << endl;
                        }
                    }
                }

                else if (option == 4)
                {
                    int new_rating;
                    bool check_rating = 1;
                    SetConsoleTextAttribute(h, 7);
                    cout << "You changing value on ";
                    SetConsoleTextAttribute(h, 10);
                    cout << "'Rating'";
                    SetConsoleTextAttribute(h, 7);
                    cout << " for book: ";
                    SetConsoleTextAttribute(h, 10);
                    cout << library[book_id].book_name << endl;

                    while (check_rating)
                    {
                        SetConsoleTextAttribute(h, 12);
                        cout << "* ";
                        SetConsoleTextAttribute(h, 7);
                        cout << "New value: ";
                        SetConsoleTextAttribute(h, 11);
                        cin >> new_rating;
                        cin.get();

                        if (new_rating >= 0 && new_rating <= 10)
                        {
                            SetConsoleTextAttribute(h, 7);
                            cout << "The value of ";
                            SetConsoleTextAttribute(h, 10);
                            cout << "'Rating'";
                            SetConsoleTextAttribute(h, 7);
                            cout << " has been changed from ";
                            SetConsoleTextAttribute(h, 10);
                            cout << library[book_id].rating;
                            SetConsoleTextAttribute(h, 7);
                            cout << " to ";
                            SetConsoleTextAttribute(h, 10);
                            cout << new_rating;

                            SetConsoleTextAttribute(h, 7);
                            library[book_id].rating = new_rating;
                            check_rating = 0;
                        }
                        else
                        {
                            SetConsoleTextAttribute(h, 12);
                            cout << "ERROR: ";
                            SetConsoleTextAttribute(h, 7);
                            cout << "The value entered is incorrect, please try again." << endl;
                        }
                    }
                }
            }
        }
        else
        {
            SetConsoleTextAttribute(h, 12);
            cout << "ERROR: ";
            SetConsoleTextAttribute(h, 7);
            cout << "This book does not exist in the library!" << endl;
        }
    }
}