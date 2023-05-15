// Declararea structurii user_t.
struct user_t {
        char user_name[50];
        int user_books; 
        int total_nr_books; 
        int acces;
        char book1[50];
        char book2[50];
};

void add_user(int *nr_users, user_t *users);

void show_users(int nr_users, user_t *users);

void remove_user(int *nr_users, user_t *users);
