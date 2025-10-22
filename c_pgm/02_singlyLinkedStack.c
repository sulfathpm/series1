#include <stdio.h>
#include <stdlib.h>

// Structure for a stack node
// Each node contains a 'data' part and a 'next' pointer
// The 'next' pointer links the current node to the node below it in the stack
struct Node {
    int data;              // Data stored in the stack node
    struct Node* next;     // Pointer to the next node (node below the current one)
};

// Function to PUSH (insert) an element onto the stack
void push(struct Node** top, int value) {
    // Step 1: Create a new node dynamically
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    // Step 2: Assign the data value to the new node
    newNode->data = value;

    // Step 3: Make the new node point to the current top node
    // This links the new node with the existing stack
    newNode->next = *top;

    // Step 4: Move the 'top' pointer to point to the new node
    // So the new node becomes the new top of the stack
    *top = newNode;

    printf("%d pushed to stack.\n", value);
}

// Function to POP (remove) an element from the top of the stack
void pop(struct Node** top) {
    // Step 1: Check if stack is empty
    if (*top == NULL) {
        printf("Stack Underflow! Cannot pop.\n");
        return;  // Nothing to remove
    }

    // Step 2: Create a temporary pointer to hold the node to be deleted
    struct Node* temp = *top;

    // Step 3: Display the popped element (for user understanding)
    printf("%d popped from stack.\n", temp->data);

    // Step 4: Move 'top' to the next node (second node becomes new top)
    *top = (*top)->next;

    // Step 5: Free the memory of the popped node
    free(temp);
}

// Function to DISPLAY all elements in the stack
void display(struct Node* top) {
    // Step 1: Check if stack is empty
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    // Step 2: Use a temporary pointer to traverse the stack
    struct Node* temp = top;
    printf("Stack elements (Top to Bottom): ");

    // Step 3: Traverse until we reach the end of the stack (NULL)
    while (temp != NULL) {
        printf("%d ", temp->data);  // Print current node’s data
        temp = temp->next;          // Move to the next node
    }

    printf("\n");  // Move to next line after printing all elements
}

// Function to COUNT how many elements are in the stack
int count(struct Node* top) {
    int count = 0;
    struct Node* temp = top;

    // Traverse the stack and increment count for each node
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    // Return total count
    return count;
}

// MAIN FUNCTION — Menu-driven program
int main() {
    struct Node* top = NULL;  // Initially, stack is empty (top = NULL)
    int choice, value;

    while (1) {
        // Display menu options
        printf("\n--- STACK OPERATIONS USING LINKED LIST ---\n");
        printf("1. Push (Insert)\n");
        printf("2. Pop (Delete)\n");
        printf("3. Display Stack\n");
        printf("4. Count Elements\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform operation based on user's choice
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&top, value);    // Call push function
                break;

            case 2:
                pop(&top);            // Call pop function
                break;

            case 3:
                display(top);         // Call display function
                break;

            case 4:
                printf("Total elements in stack: %d\n", count(top)); // Count and print
                break;

            case 5:
                printf("Exiting program...\n");
                exit(0);              // Terminate program
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
