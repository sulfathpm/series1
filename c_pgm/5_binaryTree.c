#include <stdio.h>
#include <stdlib.h>

// Structure of a node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert node in level order (like a complete binary tree)
struct Node* insertNode(struct Node* root, int value) {
    struct Node* newNode = createNode(value);

    if (root == NULL)
        return newNode;

    // Use a queue for level-order insertion
    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct Node* temp = queue[front++];

        if (temp->left == NULL) {
            temp->left = newNode;
            return root;
        } else
            queue[rear++] = temp->left;

        if (temp->right == NULL) {
            temp->right = newNode;
            return root;
        } else
            queue[rear++] = temp->right;
    }
    return root;
}

// Function to find the deepest (rightmost) node
struct Node* findDeepestNode(struct Node* root) {
    if (root == NULL)
        return NULL;

    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    struct Node* temp = NULL;

    while (front < rear) {
        temp = queue[front++];

        if (temp->left)
            queue[rear++] = temp->left;
        if (temp->right)
            queue[rear++] = temp->right;
    }
    return temp;
}

// Function to delete a node
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL)
        return NULL;

    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    struct Node* temp;
    struct Node* keyNode = NULL;

    // Find the node to delete and last node (deepest node)
    while (front < rear) {
        temp = queue[front++];

        if (temp->data == value)
            keyNode = temp;

        if (temp->left)
            queue[rear++] = temp->left;
        if (temp->right)
            queue[rear++] = temp->right;
    }

    if (keyNode != NULL) {
        struct Node* deepest = findDeepestNode(root);
        int x = deepest->data;
        // Replace key node's data with deepest node's data
        keyNode->data = x;

        // Delete deepest node
        front = 0;
        rear = 0;
        queue[rear++] = root;
        while (front < rear) {
            temp = queue[front++];

            if (temp->left) {
                if (temp->left == deepest) {
                    free(temp->left);
                    temp->left = NULL;
                    break;
                } else
                    queue[rear++] = temp->left;
            }

            if (temp->right) {
                if (temp->right == deepest) {
                    free(temp->right);
                    temp->right = NULL;
                    break;
                } else
                    queue[rear++] = temp->right;
            }
        }
    } else {
        printf("Node with value %d not found.\n", value);
    }
    return root;
}

// Inorder Traversal (Left → Root → Right)
void inorder(struct Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Preorder Traversal (Root → Left → Right)
void preorder(struct Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// Postorder Traversal (Left → Right → Root)
void postorder(struct Node* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// Count total number of nodes
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Main function (menu-driven)
int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n--- BINARY TREE OPERATIONS ---\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Inorder Traversal\n");
        printf("4. Preorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Count Nodes\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 4:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 5:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 6:
                printf("Total number of nodes: %d\n", countNodes(root));
                break;
            case 7:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
