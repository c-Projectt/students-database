#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

void menu();
int check(int);
void checkrepeat(int, int);
void gotoxy(int, int);
void add();
void delete_record();
void search();
void display();
void modify();
void clear();
//void exit();

struct studentNode {
    int id;
    int totalMarks;
    char firstName[15];
    char lastName[15];
    char course[20];
    struct studentNode* next;
};
struct studentNode* head = NULL;

int main() {
    gotoxy(20, 10);
    printf("<< Students Database Management System >>");
    gotoxy(40, 15);
    printf("Press any key to continue");
    _getch();               // pauses the Output Console untill a key is pressed & is defined in conio.h header file
    menu();
    return 0;
}
void menu() {
    int choice;
    system("cls");          // to clear the output screen & is defined in stdlib.h header file
    gotoxy(5, 3);
    puts("<< MENU >>");
    gotoxy(10, 5);
    puts("Choose a number to perform the task you want");
    gotoxy(15, 7);
    puts("1 : Add Record");
    gotoxy(15, 8);
    puts("2 : Delete Record");
    gotoxy(15, 9);
    puts("3 : Search");
    gotoxy(15, 10);
    puts("4 : Display all students records");
    gotoxy(15, 11);
    puts("5 : Modify Record");
    gotoxy(15, 12);
    puts("6 : Clear");
    gotoxy(15, 13);
    puts("7 : Exit");
    gotoxy(10, 15);
    printf("Enter your choice : ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        add();
        break;
    case 2:
        delete_record();
        break;
    case 3:
        search();
        break;
    case 4:
        display();
        break;
    case 5:
        modify();
        break;
    case 6:
        clear();
        break;
    case 7:
        //exit();
        break;
    default:
        /*gotoxy(25, 17);
        puts("Invalid Choice .. Choose a number from 1 to 7.");*/
        menu();
    }
}
int check(int i) {
    struct studentNode* checkptr = malloc(sizeof(struct studentNode));
    checkptr = head;
    if (head == NULL) {
        return 3;         // does not exist
    }
    while (checkptr != NULL) {
        if (checkptr->id == i) {
            return 2;    // exist
        }
        checkptr = checkptr->next;
    }
    return 3;
}
void checkrepeat(int x, int y) {
    gotoxy(x, y);
    int c;
    printf("Enter 1 to perform another task or 0 to exit: ");
    scanf("%d", &c);
    if (c == 1) menu();
    //else exit();
}
void gotoxy(int x, int y) {                // is defined in windows.h header file
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void add() {
    int id, marks;
    char firstName[15], lastName[15], course[20];
    gotoxy(25, 17);
    printf("Enter the student firstname: ");
    scanf("%14s", firstName);
    gotoxy(25, 18);
    printf("Enter the student lastname: ");
    scanf("%14s", lastName);
    gotoxy(25, 19);
    printf("Enter the Course: ");
    scanf("%19s", course);
    gotoxy(25, 20);
    printf("Enter the student ID: ");
    scanf("%d", &id);
    gotoxy(25, 21);
    printf("Enter the student total marks: ");
    scanf("%d", &marks);

    if (check(id) == 2) {
        gotoxy(10, 23);
        puts("The student with this ID is already exist.");
    }
    else {
        struct studentNode* newNode = malloc(sizeof(struct studentNode));
        newNode->id = id;
        newNode->totalMarks = marks;
        strcpy(newNode->firstName, firstName);
        strcpy(newNode->lastName, lastName);
        strcpy(newNode->course, course);
        newNode->next = NULL;
        if (head == NULL || head->id > newNode->id) {
            newNode->next = head;
            head = newNode;
        }
        else {
            struct studentNode* current = head, * previous = head;
            while (current != NULL && current->id < newNode->id) {
                previous = current;
                current = current->next;
            }
            previous->next = newNode;
            newNode->next = current;
        }
        gotoxy(10, 23);
        puts("The record is added successfully.");
    }
    checkrepeat(25, 25);
}
void delete_record() {
    int id;
    gotoxy(25, 17);
    printf("Enter the ID of the student you want to delete: ");
    scanf("%d", &id);
    if (head == NULL) {
        gotoxy(10, 19);
        puts("Record does not exist.");
    }
    else {
        struct studentNode* current = head;
        struct studentNode* previous = head;
        while (current != NULL && current->id != id) {
            previous = current;
            current = current->next;
        }
        if (current == NULL) {
            gotoxy(10, 19);
            puts("Record does not exist.");
        }
        else {
            previous->next = current->next;
            free(current);
            gotoxy(10, 19);
            puts("Record is deleted successfully.");
        }
    }
    checkrepeat(25, 21);
}
void search() {
    int id;
    gotoxy(25, 17);
    printf("Enter the ID of the student: ");
    scanf("%d", &id);
    if (head == NULL) {
        gotoxy(10, 19);
        puts("Record does not exist.");
        checkrepeat(25, 21);
        return;
    }
    struct studentNode* s = head;
    while (s != NULL && s->id != id) {
        s = s->next;
    }
    if (s == NULL) {
        gotoxy(10, 19);
        puts("Record does not exist.");
        checkrepeat(25, 21);
    }
    else if (s->id == id) {
        gotoxy(10, 19);
        printf("The student firstname: %s\n", s->firstName);
        gotoxy(10, 20);
        printf("The student lastname: %s\n", s->lastName);
        gotoxy(10, 21);
        printf("Course: %s\n", s->course);
        gotoxy(10, 22);
        printf("StudentID: %d\n", s->id);
        gotoxy(10, 23);
        printf("Total marks: %d\n", s->totalMarks);
        checkrepeat(25, 25);
    }
}
void display() {
    gotoxy(20, 17);
    if (head == NULL) {
        puts("The system is empty.");
        checkrepeat(25, 19);
        return;
    }
    struct studentNode* print = head;
    printf("%-10s %-20s %-20s %-20s %-s\n", "ID", "Firstname", "Lastname", "Course", "Total Marks");
    int x = 18;
    while (print != NULL) {
        gotoxy(20, x++);
        printf("%-10d %-20s %-20s %-20s %d\n", print->id, print->firstName, print->lastName, print->course, print->totalMarks);
        print = print->next;
    }
    checkrepeat(25, 25);
}

void modify() {
    gotoxy(25, 17);
    puts("Your choice is 5");
}
void clear() {
    gotoxy(25, 17);
    puts("Your choice is 6");
}
/*
void exit() {
    gotoxy(25, 17);
    puts("Your choice is 7");
}
*/