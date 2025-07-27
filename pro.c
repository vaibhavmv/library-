#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#define MAX_BOOKS 100
#define MAX_TITLE_LEN 50
#define MAX_AUTHOR_LEN 50
#define MAX_ISBN_LEN 20
struct Book {
    int id;
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    char isbn[MAX_ISBN_LEN];
    int available_copies;
    int total_copies;
};
struct Book library[MAX_BOOKS];
int num_books = 0;
int next_id = 1; 
void addBook();
void displayAllBooks();
void searchBookByTitle();
void searchBookByAuthor();
void issueBook();
void returnBook();
void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayAllBooks();
                break;
            case 3:
                searchBookByTitle();
                break;
            case 4:
                searchBookByAuthor();
                break;
            case 5:
                issueBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                printf("Exiting Library Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    } while (choice != 7);

    return 0;
}
void displayMenu() {
    printf("********** Library Management System **********\n");
    printf("1. Add New Book\n");
    printf("2. Display All Books\n");
    printf("3. Search Book by Title\n");
    printf("4. Search Book by Author\n");
    printf("5. Issue Book\n");
    printf("6. Return Book\n");
    printf("7. Exit\n");
    printf("***********************************************\n");
}
void addBook() {
    if (num_books >= MAX_BOOKS) {
        printf("Error: Library is full. Cannot add more books.\n");
        return;
    }

    struct Book newBook;
    newBook.id = next_id++;

    printf("Enter Book Title: ");
    fgets(newBook.title, MAX_TITLE_LEN, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; 

    printf("Enter Author Name: ");
    fgets(newBook.author, MAX_AUTHOR_LEN, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0; 

    printf("Enter ISBN: ");
    fgets(newBook.isbn, MAX_ISBN_LEN, stdin);
    newBook.isbn[strcspn(newBook.isbn, "\n")] = 0; 

    printf("Enter Total Copies: ");
    scanf("%d", &newBook.total_copies);
    while (getchar() != '\n'); 

    newBook.available_copies = newBook.total_copies;

    library[num_books++] = newBook;
    printf("Book '%s' added successfully with ID %d.\n", newBook.title, newBook.id);
}
void displayAllBooks() {
    if (num_books == 0) {
        printf("Library is empty. No books to display.\n");
        return;
    }

    printf("%-5s %-30s %-20s %-15s %-10s %-10s\n", "ID", "Title", "Author", "ISBN", "Available", "Total");
    printf("------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < num_books; i++) {
        printf("%-5d %-30s %-20s %-15s %-10d %-10d\n",
               library[i].id,
               library[i].title,
               library[i].author,
               library[i].isbn,
               library[i].available_copies,
               library[i].total_copies);
    }
}
void searchBookByTitle() {
    char searchTitle[MAX_TITLE_LEN];
    printf("Enter Title to search: ");
    fgets(searchTitle, MAX_TITLE_LEN, stdin);
    searchTitle[strcspn(searchTitle, "\n")] = 0; 
    int found = 0;
    printf("\nSearch Results for Title '%s':\n", searchTitle);
    printf("%-5s %-30s %-20s %-15s %-10s %-10s\n", "ID", "Title", "Author", "ISBN", "Available", "Total");
    printf("------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_books; i++) {
        // Use strstr for partial matching, or strcmp for exact matching
        if (strstr(library[i].title, searchTitle) != NULL) { // strstr for partial match
        // if (strcmp(library[i].title, searchTitle) == 0) { // strcmp for exact match
            printf("%-5d %-30s %-20s %-15s %-10d %-10d\n",
                   library[i].id,
                   library[i].title,
                   library[i].author,
                   library[i].isbn,
                   library[i].available_copies,
                   library[i].total_copies);
            found = 1;
        }
    }

    if (!found) {
        printf("No books found with title '%s'.\n", searchTitle);
    }
}
void searchBookByAuthor() {
    char searchAuthor[MAX_AUTHOR_LEN];
    printf("Enter Author to search: ");
    fgets(searchAuthor, MAX_AUTHOR_LEN, stdin);
    searchAuthor[strcspn(searchAuthor, "\n")] = 0; // Remove trailing newline

    int found = 0;
    printf("\nSearch Results for Author '%s':\n", searchAuthor);
    printf("%-5s %-30s %-20s %-15s %-10s %-10s\n", "ID", "Title", "Author", "ISBN", "Available", "Total");
    printf("------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_books; i++) {
        if (strstr(library[i].author, searchAuthor) != NULL) { // strstr for partial match
        // if (strcmp(library[i].author, searchAuthor) == 0) { // strcmp for exact match
            printf("%-5d %-30s %-20s %-15s %-10d %-10d\n",
                   library[i].id,
                   library[i].title,
                   library[i].author,
                   library[i].isbn,
                   library[i].available_copies,
                   library[i].total_copies);
            found = 1;
        }
    }

    if (!found) {
        printf("No books found by author '%s'.\n", searchAuthor);
    }
}
void issueBook() {
    int bookId;
    printf("Enter the ID of the book to issue: ");
    scanf("%d", &bookId);
    while (getchar() != '\n');

    int found_index = -1;
    for (int i = 0; i < num_books; i++) {
        if (library[i].id == bookId) {
            found_index = i;
            break;
        }
    }

    if (found_index != -1) {
        if (library[found_index].available_copies > 0) {
            library[found_index].available_copies--;
            printf("Book '%s' (ID: %d) successfully issued. %d copies remaining.\n",
                   library[found_index].title, library[found_index].id, library[found_index].available_copies);
        } else {
            printf("Sorry, all copies of '%s' (ID: %d) are currently issued.\n",
                   library[found_index].title, library[found_index].id);
        }
    } else {
        printf("Book with ID %d not found.\n", bookId);
    }
}

void returnBook() {
    int bookId;
    printf("Enter the ID of the book to return: ");
    scanf("%d", &bookId);
    while (getchar() != '\n'); 

    int found_index = -1;
    for (int i = 0; i < num_books; i++) {
        if (library[i].id == bookId) {
            found_index = i;
            break;
        }
    }

    if (found_index != -1) {
        if (library[found_index].available_copies < library[found_index].total_copies) {
            library[found_index].available_copies++;
            printf("Book '%s' (ID: %d) successfully returned. %d copies now available.\n",
                   library[found_index].title, library[found_index].id, library[found_index].available_copies);
        } else {
            printf("All copies of '%s' (ID: %d) are already in the library.\n",
                   library[found_index].title, library[found_index].id);
        }
    } else {
        printf("Book with ID %d not found.\n", bookId);
    }
}
