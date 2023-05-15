void exit_app(int nr_users, int nr_books, book_t *library, user_t *users);

void start_app(int *nr_books, int *nr_users, book_t *library, user_t *users);

void commands();

unsigned int hasing(char *a);

int login(char *pass);

void edit_book(int *nr_books, book_t *library);

const char* current_time();