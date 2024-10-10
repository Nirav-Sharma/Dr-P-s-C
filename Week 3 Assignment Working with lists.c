#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// Node definition for linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertNode(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to print the linked list in rows of 5
void printList(struct Node* head) {
    struct Node* temp = head;
    int count = 0;
    while (temp != NULL) {
        printf("%d\t", temp->data);
        count++;
        if (count % 5 == 0) {
            printf("\n");
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to sort the linked list using Bubble Sort
void bubbleSort(struct Node* head) {
    int swapped;
    struct Node* ptr1;
    struct Node* lptr = NULL;

    // Check for empty list
    if (head == NULL) {
        return;
    }

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                // Swap the data
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to generate 100 random integers and store them in a linked list
void generateRandomList(struct Node** head) {
    srand(time(NULL));  // Seed the random number generator
    for (int i = 0; i < SIZE; i++) {
        int randomValue = rand() % 1000;  // Generate random number between 0 and 999
        insertNode(head, randomValue);
    }
}

int main() {
    struct Node* head = NULL;

    // Generate 100 random numbers and store them in the linked list
    generateRandomList(&head);

    printf("Original List:\n");
    printList(head);

    // Sort the linked list using Bubble Sort
    bubbleSort(head);

    printf("\nSorted List:\n");
    printList(head);

    return 0;
}
