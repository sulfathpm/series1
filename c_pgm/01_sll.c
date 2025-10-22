#include <stdio.h>
#include <stdlib.h>

// Structure definition for a node in the linked list
struct Node {
    int data;              // Data part to store value
    struct Node *next;     // Pointer to the next node
};

// Function to create a new node with given data
struct Node* createNode(int value) {
    // Dynamically allocate memory for a new node
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    // Assign the value to the data field
    newNode->data = value;

    // Initially, the next pointer is set to NULL (no link yet)
    newNode->next = NULL;

    // Return the address of the new node
    return newNode;
}

// Function to insert a new node at the beginning of the list
void insertAtBeginning(struct Node** head, int value) {
    // Create a new node
    struct Node* newNode = createNode(value);

    // Make the new node point to the current head
    newNode->next = *head;

    // Move the head pointer to the new node
    *head = newNode;

    printf("Node inserted at beginning.\n");
}

// Function to insert a new node at the end of the list
void insertAtEnd(struct Node** head, int value) {
    // Create a new node
    struct Node* newNode = createNode(value);

    // If the list is empty, new node becomes the head
    if (*head == NULL) {
        *head = newNode;
    } 
    else {
        // Otherwise, traverse the list until the last node
        struct Node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;

        // Link the last node to the new node
        temp->next = newNode;
    }

    printf("Node inserted at end.\n");
}

// Function to insert a node after a given position
void insertAfterPosition(struct Node* head, int position, int value) {
    // Create a new node
    struct Node* newNode = createNode(value);
    struct Node* temp = head;
    int i;

    // Traverse the list until the given position
    for (i = 1; i < position && temp != NULL; i++)
        temp = temp->next;

    // If the position is invalid (list ended early)
    if (temp == NULL) {
        printf("Position not found.\n");
        free(newNode); // free the unused node memory
        return;
    }

    // Insert the new node after the position
    newNode->next = temp->next;
    temp->next = newNode;

    printf("Node inserted after position %d.\n", position);
}

// Function to delete a node from the beginning
void deleteFromBeginning(struct Node** head) {
    // If list is empty, nothing to delete
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    // Temporary pointer to hold the node to delete
    struct Node* temp = *head;

    // Move head to the next node
    *head = (*head)->next;

    // Free memory of deleted node
    free(temp);

    printf("Node deleted from beginning.\n");
}

// Function to delete a node from the end
void deleteFromEnd(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = *head;
    struct Node* prev = NULL;

    // Traverse till the last node
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    // If there was only one node
    if (prev == NULL)
        *head = NULL;
    else
        prev->next = NULL; // Remove the last node

    // Free the deleted node memory
    free(temp);

    printf("Node deleted from end.\n");
}

// Function to delete a node by its value
void deleteByValue(struct Node** head, int value) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    // Traverse until we find the value or reach end
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    // If value not found in the list
    if (temp == NULL) {
        printf("Value not found.\n");
        return;
    }

    // If node to delete is the first node
    if (prev == NULL)
        *head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("Node with value %d deleted.\n", value);
}

// Function to display all nodes in the linked list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;
    printf("Linked List: ");

    // Traverse through the list and print data
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

// Function to count the number of nodes
int countNodes(struct Node* head) {
    int count = 0;
    struct Node* temp = head;

    // Traverse the list and increase count for each node
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

// Main function to test all operations
int main() {
    struct Node* head = NULL;  // Initially, the list is empty
    int choice, value, position;

    while (1) {
        printf("\n--- SINGLE LINKED LIST OPERATIONS ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert After Position\n");
        printf("4. Delete from Beginning\n");
        printf("5. Delete from End\n");
        printf("6. Delete by Value\n");
        printf("7. Display List\n");
        printf("8. Count Nodes\n");
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
                printf("Enter position: ");
                scanf("%d", &position);
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertAfterPosition(head, position, value);
                break;

            case 4:
                deleteFromBeginning(&head);
                break;

            case 5:
                deleteFromEnd(&head);
                break;

            case 6:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteByValue(&head, value);
                break;

            case 7:
                displayList(head);
                break;

            case 8:
                printf("Total nodes: %d\n", countNodes(head));
                break;

            case 9:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
