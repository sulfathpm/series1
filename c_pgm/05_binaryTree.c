#include <stdio.h>
#include <stdlib.h>

// Structure definition for a node in the binary tree
struct Node {
    int data;               // Value of the node
    struct Node* left;      // Pointer to the left child
    struct Node* right;     // Pointer to the right child
};

// Function to create a new node with given value
struct Node* createNode(int value) {
    // Dynamically allocate memory for a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;   // Assign the given value to the node
    newNode->left = NULL;    // Initialize left child as NULL
    newNode->right = NULL;   // Initialize right child as NULL
    return newNode;
}

/* ---------------------- INSERTION -----------------------
   Inserts a node in *level-order* (like a complete binary tree)
   Meaning: Fill each level from left to right before moving to the next.
------------------------------------------------------------*/
struct Node* insertNode(struct Node* root, int value) {
    struct Node* newNode = createNode(value);

    // If tree is empty, the new node becomes the root
    if (root == NULL)
        return newNode;

    // Use a queue for level-order traversal
    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;  // Enqueue root node

    // Perform level-order traversal until an empty position is found
    while (front < rear) {
        struct Node* temp = queue[front++];  // Dequeue node

        // Check if left child is empty → insert there
        if (temp->left == NULL) {
            temp->left = newNode;
            return root;
        } else {
            queue[rear++] = temp->left;  // Enqueue left child
        }

        // Check if right child is empty → insert there
        if (temp->right == NULL) {
            temp->right = newNode;
            return root;
        } else {
            queue[rear++] = temp->right;  // Enqueue right child
        }
    }
    return root;
}

/* ---------------- FIND DEEPEST NODE -------------------
   Finds the last node in level order traversal,
   i.e., the deepest and rightmost node.
----------------------------------------------------------*/
struct Node* findDeepestNode(struct Node* root) {
    if (root == NULL)
        return NULL;

    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    struct Node* temp = NULL;

    // Level order traversal till the last node
    while (front < rear) {
        temp = queue[front++];
        if (temp->left)
            queue[rear++] = temp->left;
        if (temp->right)
            queue[rear++] = temp->right;
    }

    // 'temp' now points to the deepest (rightmost) node
    return temp;
}

/* ----------------- DELETE NODE -------------------------
   Deletes a node by:
   1. Finding the node to delete (keyNode).
   2. Finding the deepest node.
   3. Copying deepest node's data to keyNode.
   4. Deleting the deepest node.
----------------------------------------------------------*/
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL)
        return NULL;

    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    struct Node* temp;
    struct Node* keyNode = NULL;  // Node to delete

    // Step 1: Find node to delete (keyNode) and the last node
    while (front < rear) {
        temp = queue[front++];

        if (temp->data == value)
            keyNode = temp;  // Found node to delete

        if (temp->left)
            queue[rear++] = temp->left;
        if (temp->right)
            queue[rear++] = temp->right;
    }

    // Step 2: If node to delete found
    if (keyNode != NULL) {
        struct Node* deepest = findDeepestNode(root); // Find last node
        int x = deepest->data; // Copy its data
        keyNode->data = x;     // Replace data in node to delete

        // Step 3: Delete the deepest node
        front = rear = 0;
        queue[rear++] = root;
        while (front < rear) {
            temp = queue[front++];

            // Check left child
            if (temp->left) {
                if (temp->left == deepest) {
                    free(temp->left);      // Free memory
                    temp->left = NULL;     // Remove link
                    break;
                } else
                    queue[rear++] = temp->left;
            }

            // Check right child
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

/* ------------------- TREE TRAVERSALS ------------------- */

// Inorder Traversal: Left → Root → Right
void inorder(struct Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);            // Visit left subtree
    printf("%d ", root->data);      // Visit root
    inorder(root->right);           // Visit right subtree
}

// Preorder Traversal: Root → Left → Right
void preorder(struct Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);      // Visit root
    preorder(root->left);           // Visit left subtree
    preorder(root->right);          // Visit right subtree
}

// Postorder Traversal: Left → Right → Root
void postorder(struct Node* root) {
    if (root == NULL)
        return;
    postorder(root->left);          // Visit left subtree
    postorder(root->right);         // Visit right subtree
    printf("%d ", root->data);      // Visit root last
}

/* ------------------- COUNT NODES ------------------------
   Counts total number of nodes in the tree recursively
----------------------------------------------------------*/
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    // Count = 1 (current node) + left subtree + right subtree
    return 1 + countNodes(root->left) + countNodes(root->right);
}

/* -------------------- MAIN FUNCTION ---------------------
   Menu-driven program to test all operations on Binary Tree
-----------------------------------------------------------*/
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
