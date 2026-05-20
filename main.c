#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define FILE_NAME "students.txt"

// Structure definition
typedef struct {
    int id;
    char name[MAX_NAME];
    float marks;
} Student;

// Function prototypes
void addStudent();
void displayStudents();
void searchStudent();

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

// Function to add student
void addStudent() {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Student s;

    printf("Enter ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, file);
    fclose(file);

    printf("Student added successfully!\n");
}

// Function to display all students
void displayStudents() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No records found.\n");
        return;
    }

    Student s;
    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(Student), 1, file)) {
        printf("ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
    }

    fclose(file);
}

// Function to search student by ID
void searchStudent() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No records found.\n");
        return;
    }

    int searchId, found = 0;
    Student s;

    printf("Enter ID to search: ");
    scanf("%d", &searchId);

    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id == searchId) {
            printf("Record Found: ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }

    fclose(file);
}