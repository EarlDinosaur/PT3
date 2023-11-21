#include <stdio.h>
#include <stdlib.h>
#define ADVISORS 13

struct adviser {
    int id;
    struct adviser *next;
};

typedef struct adviser Adviser;
typedef Adviser *AdviserPtr;

AdviserPtr head, tail, current;

AdviserPtr createAdviser(int id) {
    AdviserPtr newAdviser = (AdviserPtr)malloc(sizeof(Adviser));
    if (newAdviser != NULL) {
        newAdviser->id = id;
        newAdviser->next = NULL;
    }
    return newAdviser;
}

AdviserPtr createAdviserCircle(int numAdvisers) {
    head = NULL;
    tail = NULL;
    for (int i = 1; i <= numAdvisers; i++) {
        AdviserPtr newAdviser = createAdviser(i);
        if (newAdviser != NULL) {
            if (head == NULL) {
                head = newAdviser;
                tail = newAdviser;
            } else {
                tail->next = newAdviser;
                tail = newAdviser;
            }
        }
    }

    if (tail != NULL) {
        tail->next = head; // Make it circular
    }

    return head;
}

void selectAdvisers(AdviserPtr *head, int start, int interval, int numToSelect) {
    printf("Chosen Advisers: ");
    current = *head;

    for (int i = 1; i < start; i++) {
        current = current->next; // Move to the starting adviser
    }

    for (int i = 0; i < numToSelect; i++) {
        for (int j = 1; j < interval; j++) {
            current = current->next;
        }

        printf("%d", current->id);

        if (i < numToSelect - 1) {
            printf(", ");
        }

        AdviserPtr temp = current->next;
        // Remove the selected adviser from the circle
        current->id = temp->id;
        current->next = temp->next;
        
        if (temp == *head) {
            *head = temp->next;
        }
        
        free(temp);
    }
   
    
    printf("\n");
}

void freeAdviserCircle(AdviserPtr *head) {
    current = *head;
    AdviserPtr temp;

    if (*head != NULL) {
        do {
            temp = current->next;
            free(current);
            current = temp;
        } while (current != *head);
    }

    *head = NULL;
}

int main() {
    int start, interval;

    while (1){
        printf("Start: ");
        scanf("%d", &start);

        if (start == 0) {
            printf("Exiting the Program");
            break; // Exit the program
        }

        printf("Interval: ");
        scanf("%d", &interval);

        if (start < 1 || start > 13 || interval < 1 || interval > 100) {
            printf("Invalid input. Please enter valid values.\n");
            continue;
        }

        AdviserPtr adviserCircle = createAdviserCircle(ADVISORS);
        selectAdvisers(&adviserCircle, start, interval, 5);
        freeAdviserCircle(&adviserCircle);

    }

    return 0;
}