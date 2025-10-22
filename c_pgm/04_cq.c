#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  // Maximum size of the circular queue

// Structure definition for the Circular Queue
struct CircularQueue {
    int items[SIZE];  // Array to store elements in the queue
    int front;        // Points to the front (first) element
    int rear;         // Points to the rear (last) element
};

// Function to initialize the queue (Creation)
void createQueue(struct CircularQueue *q) {
    // Initially, both front and rear are set to -1 (queue is empty)
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is full
int isFull(struct CircularQueue *q) {
    // Queue is full if:
    // 1. Front is at index 0 and rear is at the last index (SIZE - 1), OR
    // 2. Rear is just before front in a circular manner
    if ((q->front == 0 && q->rear == SIZE - 1) || (q->rear + 1 == q->front))
        return 1;
    return 0;
}

// Function to check if the queue is empty
int isEmpty(struct CircularQueue *q) {
    // Queue is empty if front is -1
    if (q->front == -1)
        return 1;
    return 0;
}

// Function to insert (enqueue) an element into the queue
void enqueue(struct CircularQueue *q, int value) {
    // If queue is full, no insertion possible
    if (isFull(q)) {
        printf("Queue Overflow! Cannot insert %d\n", value);
        return;
    }

    // If queue is empty (first element to insert)
    if (isEmpty(q)) {
        q->front = 0;  // Front starts at index 0
        q->rear = 0;   // Rear also starts at index 0
    } else {
        // Move rear forward in circular manner
        q->rear = (q->rear + 1) % SIZE;
    }

    // Place the new value at the rear position
    q->items[q->rear] = value;
    printf("%d inserted into the queue.\n", value);
}

// Function to delete (dequeue) an element from the queue
void dequeue(struct CircularQueue *q) {
    // If queue is empty, no deletion possible
    if (isEmpty(q)) {
        printf("Queue Underflow! Cannot delete.\n");
        return;
    }

    // Get the value at the front before deleting
    int value = q->items[q->front];

    // If there is only one element left
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1; // Reset queue to empty state
    } else {
        // Move front forward in circular manner
        q->front = (q->front + 1) % SIZE;
    }

    printf("%d deleted from the queue.\n", value);
}

// Function to display all elements in the queue
void display(struct CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");
    int i = q->front;

    // Loop until we reach the rear element
    while (1) {
        printf("%d ", q->items[i]);
        if (i == q->rear)
            break;  // Stop when we reach the rear
        i = (i + 1) % SIZE;  // Move circularly
    }
    printf("\n");
}

// Function to count total elements in the queue
int count(struct CircularQueue *q) {
    if (isEmpty(q))
        return 0;

    // If rear >= front, simple difference + 1 gives count
    if (q->rear >= q->front)
        return q->rear - q->front + 1;
    else
        // If rear has wrapped around before front
        return SIZE - (q->front - q->rear - 1);
}

// Main function (menu-driven)
int main() {
    struct CircularQueue q;  // Create a CircularQueue structure variable
    createQueue(&q);         // Initialize the queue

    int choice, value;

    // Infinite loop for menu-driven program
    while (1) {
        printf("\n--- CIRCULAR QUEUE OPERATIONS ---\n");
        printf("1. Insert (Enqueue)\n");
        printf("2. Delete (Dequeue)\n");
        printf("3. Display Queue\n");
        printf("4. Count Elements\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform operation based on user choice
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                enqueue(&q, value);  // Insert value
                break;

            case 2:
                dequeue(&q);  // Delete value
                break;

            case 3:
                display(&q);  // Show all elements
                break;

            case 4:
                printf("Total elements in queue: %d\n", count(&q));
                break;

            case 5:
                printf("Exiting program...\n");
                exit(0);  // Exit the program

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
