#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  // Maximum size of the queue

// Structure for circular queue
struct CircularQueue {
    int items[SIZE];
    int front;
    int rear;
};

// Function to initialize the queue (Creation)
void createQueue(struct CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is full
int isFull(struct CircularQueue *q) {
    if ((q->front == 0 && q->rear == SIZE - 1) || (q->rear + 1 == q->front))
        return 1;
    return 0;
}

// Check if queue is empty
int isEmpty(struct CircularQueue *q) {
    if (q->front == -1)
        return 1;
    return 0;
}

// Insert element (Enqueue)
void enqueue(struct CircularQueue *q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow! Cannot insert %d\n", value);
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % SIZE;
    }
    q->items[q->rear] = value;
    printf("%d inserted into the queue.\n", value);
}

// Delete element (Dequeue)
void dequeue(struct CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Cannot delete.\n");
        return;
    }
    int value = q->items[q->front];
    if (q->front == q->rear) {
        // Only one element left
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % SIZE;
    }
    printf("%d deleted from the queue.\n", value);
}

// Display queue elements
void display(struct CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->items[i]);
        if (i == q->rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

// Count number of elements
int count(struct CircularQueue *q) {
    if (isEmpty(q))
        return 0;
    if (q->rear >= q->front)
        return q->rear - q->front + 1;
    else
        return SIZE - (q->front - q->rear - 1);
}

// Main function (menu-driven)
int main() {
    struct CircularQueue q;
    createQueue(&q);

    int choice, value;

    while (1) {
        printf("\n--- CIRCULAR QUEUE OPERATIONS ---\n");
        printf("1. Insert (Enqueue)\n");
        printf("2. Delete (Dequeue)\n");
        printf("3. Display Queue\n");
        printf("4. Count Elements\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                display(&q);
                break;
            case 4:
                printf("Total elements in queue: %d\n", count(&q));
                break;
            case 5:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
