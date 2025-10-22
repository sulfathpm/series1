#include <stdio.h>
#include <stdlib.h>

// Structure for a doubly linked list node
// Each node has three parts:
// 1. 'data' - stores the value
// 2. 'prev' - pointer to the previous node
// 3. 'next' - pointer to the next node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node with a given value
struct Node* createNode(int value) {
    // Dynamically allocate memory for a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    // Assign data and initialize pointers to NULL
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    // Return pointer to the newly created node
    return newNode;
}

// Function to insert a node at the beginning of the list
void insertAtBeginning(struct Node** head, int value) {
    // Create a new node
    struct Node* newNode = createNode(value);

    // If list is empty, new node becomes the head
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Link the new node with the existing head
        newNode->next = *head;

        // Update the previous pointer of the current head
        (*head)->prev = newNode;

        // Move head pointer to the new node
        *head = newNode;
    }

    printf("Node inserted at beginning.\n");
}

// Function to insert a node at the end of the list
void insertAtEnd(struct Node** head, int value) {
    // Create a new node
    struct Node* newNode = createNode(value);

    // If list is empty, new node becomes the head
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Traverse to the last node
        struct Node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;

        // Link last node to the new node
        temp->next = newNode;
        newNode->prev = temp;  // Link back to the previous node
    }

    printf("Node inserted at end.\n");
}

// Function to delete a node from the beginning
void deleteFromBeginning(struct Node** head) {
    // Check if list is empty
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    // Temporary pointer to the node being deleted
    struct Node* temp = *head;

    // Move head pointer to the next node
    *head = (*head)->next;

    // If list is not empty after deletion, set prev of new head to NULL
    if (*head != NULL)
        (*head)->prev = NULL;

    printf("Node with value %d deleted from beginning.\n", temp->data);

    // Free the memory of deleted node
    free(temp);
}

// Function to delete a node from the end
void deleteFromEnd(struct Node** head) {
    // If list is empty
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    struct Node* temp = *head;

    // Traverse to the last node
    while (temp->next != NULL)
        temp = temp->next;

    // If there is only one node
    if (temp->prev == NULL) {
        *head = NULL;
    } else {
        // Remove the link from the previous node
        temp->prev->next = NULL;
    }

    printf("Node with value %d deleted from end.\n", temp->data);

    // Free the deleted node
    free(temp);
}

// Function to traverse and display the list from beginning to end
void traverseFromBeginning(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Traversal from beginning: ");
    struct Node* temp = head;

    // Move forward until end of list
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

// Function to traverse and display the list from end to beginning
void traverseFromEnd(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;

    // Move to the last node
    while (temp->next != NULL)
        temp = temp->next;

    printf("Traversal from end: ");

    // Move backward using 'prev' pointers
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }

    printf("\n");
}

// Function to display both traversals
void displayBothSides(struct Node* head) {
    traverseFromBeginning(head);
    traverseFromEnd(head);
}

// Function to count how many nodes are in the list
int countNodes(struct Node* head) {
    int count = 0;
    struct Node* temp = head;

    // Traverse through the list and count each node
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

// MAIN FUNCTION — Menu-driven program
int main() {
    struct Node* head = NULL;  // Initially, list is empty
    int choice, value;

    while (1) {
        printf("\n--- DOUBLY LINKED LIST OPERATIONS ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Delete from Beginning\n");
        printf("4. Delete from End\n");
        printf("5. Traverse from Beginning\n");
        printf("6. Traverse from End\n");
        printf("7. Display from Both Sides\n");
        printf("8. Count Number of Nodes\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertAtBeginning(&head, value);
                break;

            case 2:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertAtEnd(&head, value);
                break;

            case 3:
                deleteFromBeginning(&head);
                break;

            case 4:
                deleteFromEnd(&head);
                break;

            case 5:
                traverseFromBeginning(head);
                break;

            case 6:
                traverseFromEnd(head);
                break;

            case 7:
                displayBothSides(head);
                break;

            case 8:
                printf("Total number of nodes: %d\n", countNodes(head));
                break;

            case 9:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
