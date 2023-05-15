#include "user.h"

//Declararea structurii book_t.
struct book_t {
    char book_name[50];
    float rating;
    int purchase;
    int available;
};

void add_book(int *nr_books, book_t *library);

void check_book(int *nr_books, book_t *library, user_t *users, int nr_users);

void remove_book(int *nr_books, book_t *library);

void show_books(int nr_books, book_t *library);

void borrow_book(user_t *users, book_t *library, int nr_users, int nr_books);

void return_book(user_t *users, book_t *library, int nr_users, int nr_books);

void lost_book(book_t *library, user_t *users, int *nr_books, int nr_users);