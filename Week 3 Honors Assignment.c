#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 200

// Node definition for the doubly linked list
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
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
        newNode->prev = temp;
    }
}

// Function to print the doubly linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    int count = 0;
    while (temp != NULL) {
        printf("%d\t", temp->data);
        count++;
        if (count % 10 == 0) {
            printf("\n");
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to remove a node from the doubly linked list
void removeNode(struct Node** head, struct Node* node) {
    if (*head == NULL || node == NULL) {
        return;
    }
    
    // If node to be deleted is the head node
    if (*head == node) {
        *head = node->next;
    }
    
    // Change next only if node to be deleted is NOT the last node
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    
    // Change prev only if node to be deleted is NOT the first node
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    
    free(node);  // Free the memory occupied by the node
}

// Function to remove duplicates from the doubly linked list
void removeDuplicates(struct Node* head) {
    struct Node* current = head;
    
    // Traverse through the doubly linked list
    while (current != NULL) {
        struct Node* runner = current->next;
        
        // Compare current node with every other node after it
        while (runner != NULL) {
            if (runner->data == current->data) {
                struct Node* temp = runner;
                runner = runner->next;
                removeNode(&head, temp);  // Remove the duplicate node
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

// Function to generate 200 random integers in the range [0, 49] and store them in the doubly linked list
void generateRandomList(struct Node** head) {
    srand(time(NULL));  // Seed the random number generator
    for (int i = 0; i < SIZE; i++) {
        int randomValue = rand() % 50;  // Generate random number between 0 and 49
        insertNode(head, randomValue);
    }
}

int main() {
    struct Node* head = NULL;

    // Generate 200 random numbers and store them in the doubly linked list
    generateRandomList(&head);

    printf("Original List:\n");
    printList(head);

    // Remove duplicates from the doubly linked list
    removeDuplicates(head);

    printf("\nList after removing duplicates:\n");
    printList(head);

    return 0;
}
