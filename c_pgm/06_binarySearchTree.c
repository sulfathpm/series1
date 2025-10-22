#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////
// STRUCTURE OF A BST NODE
/////////////////////////////////////
struct Node {
    int data;              // Data value of the node
    struct Node* left;     // Pointer to the left child
    struct Node* right;    // Pointer to the right child
};

/////////////////////////////////////
// FUNCTION TO CREATE A NEW NODE
/////////////////////////////////////
struct Node* createNode(int value) {
    // Allocate memory for a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    // Assign the given value to the node
    newNode->data = value;

    // Initialize left and right pointers to NULL
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode; // Return the created node
}

/////////////////////////////////////
// INSERT A NODE INTO THE BST
/////////////////////////////////////
// This function inserts a new node into the correct position
// according to BST rules: 
// (Left subtree < Root < Right subtree)
struct Node* insertNode(struct Node* root, int value) {
    // If tree is empty, create a new node
    if (root == NULL)
        return createNode(value);

    // If the value is smaller, go to the left subtree
    if (value < root->data)
        root->left = insertNode(root->left, value);

    // If the value is larger, go to the right subtree
    else if (value > root->data)
        root->right = insertNode(root->right, value);

    // If the value already exists, do not insert (BSTs do not allow duplicates)
    else
        printf("Duplicate value! Ignored.\n");

    // Return the unchanged root pointer
    return root;
}

/////////////////////////////////////
// FIND THE NODE WITH MINIMUM VALUE
/////////////////////////////////////
// This is used while deleting a node with two children.
struct Node* findMin(struct Node* root) {
    // Move to the leftmost node (smallest value in BST)
    while (root && root->left != NULL)
        root = root->left;

    return root; // Return the node with the minimum value
}

/////////////////////////////////////
// DELETE A NODE FROM THE BST
/////////////////////////////////////
struct Node* deleteNode(struct Node* root, int value) {
    // If the tree is empty
    if (root == NULL) {
        printf("Value not found.\n");
        return NULL;
    }

    // If the value to delete is smaller than root's value → go left
    if (value < root->data)
        root->left = deleteNode(root->left, value);

    // If the value to delete is greater than root's value → go right
    else if (value > root->data)
        root->right = deleteNode(root->right, value);

    // Node to be deleted found
    else {
        // CASE 1: Node has no children (leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);   // Free memory
            return NULL;  // Return NULL to parent
        }

        // CASE 2: Node has only one child (right)
        else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);   // Delete current node
            return temp;  // Replace with right child
        }

        // CASE 3: Node has only one child (left)
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);   // Delete current node
            return temp;  // Replace with left child
        }

        // CASE 4: Node has two children
        else {
            // Find the smallest node in the right subtree (inorder successor)
            struct Node* temp = findMin(root->right);

            // Copy that value into current node
            root->data = temp->data;

            // Delete the inorder successor from the right subtree
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root; // Return the (possibly new) root
}

/////////////////////////////////////
// SEARCH FOR A VALUE IN BST
/////////////////////////////////////
struct Node* searchNode(struct Node* root, int value) {
    // Base case: root is NULL or value found
    if (root == NULL || root->data == value)
        return root;

    // If value is smaller, search in left subtree
    if (value < root->data)
        return searchNode(root->left, value);
    else // Otherwise, search in right subtree
        return searchNode(root->right, value);
}

/////////////////////////////////////
// INORDER TRAVERSAL (Left → Root → Right)
/////////////////////////////////////
// Gives sorted order of BST values
void inorder(struct Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

/////////////////////////////////////
// PREORDER TRAVERSAL (Root → Left → Right)
/////////////////////////////////////
void preorder(struct Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

/////////////////////////////////////
// POSTORDER TRAVERSAL (Left → Right → Root)
/////////////////////////////////////
void postorder(struct Node* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

/////////////////////////////////////
// MAIN FUNCTION — MENU DRIVEN PROGRAM
/////////////////////////////////////
int main() {
    struct Node* root = NULL; // Start with an empty tree
    int choice, value;
    struct Node* found; // Used for search results

    while (1) {
        printf("\n--- BINARY SEARCH TREE OPERATIONS ---\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Search Node\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            // Insert a new node
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;

            // Delete an existing node
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;

            // Search for a node
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                found = searchNode(root, value);
                if (found != NULL)
                    printf("Value %d found in BST.\n", value);
                else
                    printf("Value %d not found.\n", value);
                break;

            // Display inorder traversal
            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            // Display preorder traversal
            case 5:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            // Display postorder traversal
            case 6:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;

            // Exit the program
            case 7:
                printf("Exiting program...\n");
                exit(0);

            // Handle invalid input
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
