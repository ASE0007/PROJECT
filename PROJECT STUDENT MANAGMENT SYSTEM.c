 #include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student {
    int rollNumber;
    char name[50];
    float marks;
    struct Student* next;
};


struct Student* createStudent(int rollNumber, const char* name, float marks) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newStudent->rollNumber = rollNumber;
    strcpy(newStudent->name, name);
    newStudent->marks = marks;
    newStudent->next = NULL;

    return newStudent;
}


void insertStudent(struct Student** head, struct Student* newStudent) {
    if (*head == NULL) {
        *head = newStudent;
    } else {
        struct Student* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }
}


void deleteStudent(struct Student** head, int rollNumber) {
    if (*head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct Student* current = *head;
    struct Student* prev = NULL;

    while (current != NULL && current->rollNumber != rollNumber) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student with Roll Number %d not found.\n", rollNumber);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Student with Roll Number %d deleted successfully.\n", rollNumber);
}


void searchStudent(struct Student* head, int rollNumber) {
    struct Student* current = head;
    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            printf("Roll Number: %d\n", current->rollNumber);
            printf("Name: %s\n", current->name);
            printf("Marks: %.2f\n", current->marks);
            return;
        }
        current = current->next;
    }
    printf("Student with Roll Number %d not found.\n", rollNumber);
}


void displayStudents(struct Student* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct Student* current = head;
    while (current != NULL) {
        printf("Roll Number: %d\n", current->rollNumber);
        printf("Name: %s\n", current->name);
        printf("Marks: %.2f\n\n", current->marks);
        current = current->next;
    }
}


void freeLinkedList(struct Student* head) {
    struct Student* current = head;
    while (current != NULL) {
        struct Student* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Student* head = NULL;
    int choice;
    int rollNumber;
    char name[50];
    float marks;

    while (1) {
        printf("\nStudent Record Management System\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Search Student\n");
        printf("4. Display Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Roll Number: ");
                scanf("%d", &rollNumber);
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Marks: ");
                scanf("%f", &marks);
                insertStudent(&head, createStudent(rollNumber, name, marks));
                break;
            case 2:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &rollNumber);
                deleteStudent(&head, rollNumber);
                break;
            case 3:
                printf("Enter Roll Number to search: ");
                scanf("%d", &rollNumber);
                searchStudent(head, rollNumber);
                break;
            case 4:
                displayStudents(head);
                break;
            case 5:
                freeLinkedList(head);
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

