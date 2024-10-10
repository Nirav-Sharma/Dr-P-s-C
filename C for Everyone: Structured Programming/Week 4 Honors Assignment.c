#include <stdio.h>
#include <stdlib.h>

// Define a struct for the binary tree node
struct TreeNode {
    int first;
    int second;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new tree node
struct TreeNode* createNode(int first, int second) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->first = first;
    newNode->second = second;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the binary tree
struct TreeNode* insert(struct TreeNode* root, int first, int second) {
    if (root == NULL) {
        // If the tree is empty, create a new node and return it
        return createNode(first, second);
    }

    // Insert based on the value of the first integer of the pair
    if (first < root->first) {
        root->left = insert(root->left, first, second);
    } else if (first > root->first) {
        root->right = insert(root->right, first, second);
    } else {
        // If the first integers are the same, handle insertion based on the second integer
        if (second < root->second) {
            root->left = insert(root->left, first, second);
        } else {
            root->right = insert(root->right, first, second);
        }
    }
    return root;
}

// Function for inorder traversal of the binary tree
void inorder(struct TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("(%d, %d) ", root->first, root->second);
        inorder(root->right);
    }
}

// Function to read integer pairs from the file
void readPairsFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    int size;
    fscanf(file, "%d", &size);  // Read the first integer, which tells how many pairs to read

    // Dynamically allocate memory for the array to store the pairs
    int data[10][2];

    // Read the pairs into the array
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d %d", &data[i][0], &data[i][1]);
    }

    // Close the file after reading
    fclose(file);

    // Insert the pairs into the binary tree
    struct TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert(root, data[i][0], data[i][1]);
    }

    // Print the tree in inorder traversal
    printf("Inorder Traversal of the Tree:\n");
    inorder(root);
    printf("\n");
}

// Main function
int main() {
    // Call the function to read pairs from the file and process them
    readPairsFromFile("input.txt");
    
    return 0;
}
