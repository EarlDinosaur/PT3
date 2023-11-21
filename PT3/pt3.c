#include <stdio.h>
#include <stdlib.h>

struct additionlist {
    int data;
    struct additionlist *nextpointer;
};

typedef struct additionlist liststruct;
typedef liststruct *linkedliststruct;

void create(linkedliststruct *current, linkedliststruct *head, linkedliststruct *tail, int data) {
    *current = malloc(sizeof(liststruct));
    (*current)->data = data;
    (*current)->nextpointer = *head;

    if (*head == NULL) {
        *head = *current;
        *tail = *current;
    } else {
        (*tail)->nextpointer = *current;
        *tail = *current;
    }
}

int dequeue(linkedliststruct *head, linkedliststruct *tail) {
    if (*head == NULL) {
        printf("Queue is empty.\n");
        return -1; // Return a value indicating an error (assuming -1 is not a valid element)
    }

    int dequeuedValue;
    linkedliststruct temp = *head;

    if (*head == *tail) {
        // Only one element in the queue
        dequeuedValue = temp->data;
        *head = NULL;
        *tail = NULL;
    } else {
        // Move head to the next element
        *head = temp->nextpointer;
        dequeuedValue = temp->data;
        // Do not free the dequeued node to keep the circular structure
        // free(temp);
    }

    // Update tail's next pointer to maintain the circular structure
    *tail = temp->nextpointer;

    return dequeuedValue;
}


int findStartingAdvisor(linkedliststruct *head, int data) {
    linkedliststruct temp = *head;
    int position = 1;

    while (temp->data != data) {
        temp = temp->nextpointer;
        position++;
    }

    printf("Starting position of advisor %d: %d\n", data, position);

    // Set the head to the starting advisor
    *head = temp;

    return position;
}

void displayList(linkedliststruct start) {
    if (start == NULL) {
        printf("List is empty.\n");
        return;
    }

    linkedliststruct temp = start;
    do {
        printf("%d ", temp->data);
        temp = temp->nextpointer;
    } while (temp != start);
    printf("\n");
}

int main() {
    int advisor, interval;
    linkedliststruct head = NULL, tail = NULL, current = NULL;

    while (1) {
        // Enqueue elements
        for (int i = 1; i < 14; i++) {
            create(&current, &head, &tail, i);
        }

        printf("Enter the starting position of the advisor: ");
        scanf("%d", &advisor);

        if(advisor == 0){
            printf("Exiting the program...");
            break;
        }

        int startingPosition = findStartingAdvisor(&head, advisor);

        // Display the circular linked list
        printf("Circular Linked List: ");
        displayList(head);

        // Dequeue elements
        int dequeuedValue = dequeue(&head, &tail);
        if (dequeuedValue != -1) {
            printf("Dequeued Value: %d\n", dequeuedValue);
        }

        // Display the updated circular linked list starting from the new head
        printf("Updated Circular Linked List: ");
        displayList(head);

        // Clean up the allocated memory
        current = head;
        linkedliststruct next;
        do {
            next = current->nextpointer;
            free(current);
            current = next;
        } while (current != head);
    }
    return 0;
}
