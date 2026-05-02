#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─── Node Structure ─────────────────────────────────────────── */
struct Book {
    int    id;
    char   title[100];
    char   author[100];
    int    year;
    struct Book *next;
};

struct Book *head = NULL;

/* ─── Function Prototypes ────────────────────────────────────── */
void addBook();
void deleteBook();
void searchBook();
void displayAll();
void freeList();

/* ─── Main with Switch Case ──────────────────────────────────── */
int main() {
    int choice;

    printf("\n====================================\n");
    printf("   LIBRARY BOOK MANAGEMENT SYSTEM   \n");
    printf("====================================\n");

    do {
        printf("\n------ MENU ------\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. Display All Books\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); /* flush newline */

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                deleteBook();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                displayAll();
                break;
            case 5:
                freeList();
                printf("\nExiting... Goodbye!\n");
                break;
            default:
                printf("\n[ERROR] Invalid choice. Please enter 1-5.\n");
        }

    } while (choice != 5);

    return 0;
}

/* ─── 1. Add Book ────────────────────────────────────────────── */
void addBook() {
    struct Book *newBook = (struct Book *)malloc(sizeof(struct Book));
    if (newBook == NULL) {
        printf("[ERROR] Memory allocation failed.\n");
        return;
    }

    printf("\n--- Add New Book ---\n");
    printf("Enter Book ID   : ");
    scanf("%d", &newBook->id);
    getchar();

    /* Check for duplicate ID */
    struct Book *temp = head;
    while (temp != NULL) {
        if (temp->id == newBook->id) {
            printf("[ERROR] Book with ID %d already exists.\n", newBook->id);
            free(newBook);
            return;
        }
        temp = temp->next;
    }

    printf("Enter Title     : ");
    fgets(newBook->title, sizeof(newBook->title), stdin);
    newBook->title[strcspn(newBook->title, "\n")] = '\0';

    printf("Enter Author    : ");
    fgets(newBook->author, sizeof(newBook->author), stdin);
    newBook->author[strcspn(newBook->author, "\n")] = '\0';

    printf("Enter Year      : ");
    scanf("%d", &newBook->year);
    getchar();

    newBook->next = NULL;

    /* Insert at tail */
    if (head == NULL) {
        head = newBook;
    } else {
        struct Book *curr = head;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = newBook;
    }

    printf("[SUCCESS] Book \"%s\" added successfully.\n", newBook->title);
}

/* ─── 2. Delete Book ─────────────────────────────────────────── */
void deleteBook() {
    if (head == NULL) {
        printf("\n[INFO] Library is empty. Nothing to delete.\n");
        return;
    }

    int id;
    printf("\n--- Delete Book ---\n");
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);
    getchar();

    struct Book *curr = head;
    struct Book *prev = NULL;

    while (curr != NULL) {
        if (curr->id == id) {
            if (prev == NULL)
                head = curr->next;   /* deleting head node */
            else
                prev->next = curr->next;

            printf("[SUCCESS] Book \"%s\" (ID: %d) deleted.\n", curr->title, curr->id);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("[ERROR] Book with ID %d not found.\n", id);
}

/* ─── 3. Search Book ─────────────────────────────────────────── */
void searchBook() {
    if (head == NULL) {
        printf("\n[INFO] Library is empty.\n");
        return;
    }

    int id;
    printf("\n--- Search Book ---\n");
    printf("Enter Book ID to search: ");
    scanf("%d", &id);
    getchar();

    struct Book *curr = head;
    int pos = 1;

    while (curr != NULL) {
        if (curr->id == id) {
            printf("\n[FOUND] Book at position %d in list:\n", pos);
            printf("  ID     : %d\n",   curr->id);
            printf("  Title  : %s\n",   curr->title);
            printf("  Author : %s\n",   curr->author);
            printf("  Year   : %d\n",   curr->year);
            return;
        }
        curr = curr->next;
        pos++;
    }

    printf("[NOT FOUND] No book with ID %d in the library.\n", id);
}

/* ─── 4. Display All Books ───────────────────────────────────── */
void displayAll() {
    if (head == NULL) {
        printf("\n[INFO] Library is empty. No books to display.\n");
        return;
    }

    printf("\n--- All Books in Library ---\n");
    printf("%-5s %-30s %-25s %-6s\n", "ID", "Title", "Author", "Year");
    printf("%-5s %-30s %-25s %-6s\n", "----", "-----------------------------", "------------------------", "------");

    struct Book *curr = head;
    int count = 1;

    while (curr != NULL) {
        printf("%-5d %-30s %-25s %-6d\n",
               curr->id,
               curr->title,
               curr->author,
               curr->year);
        curr = curr->next;
        count++;
    }

    printf("\nTotal books: %d\n", count - 1);
}

/* ─── Free Linked List ───────────────────────────────────────── */
void freeList() {
    struct Book *curr = head;
    while (curr != NULL) {
        struct Book *temp = curr;
        curr = curr->next;
        free(temp);
    }
    head = NULL;
}
