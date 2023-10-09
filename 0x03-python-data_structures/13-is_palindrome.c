#include <stdio.h>
#include <stdlib.h>

/* Structure for a singly linked list node */
struct listint_t {
    int data;
    struct listint_t* next;
};

/* Function to reverse a linked list */
struct listint_t* reverseList(struct listint_t* head) {
    struct listint_t *prev = NULL, *current = head, *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

/* Function to check if a linked list is a palindrome */
int is_palindrome(struct listint_t** head) {
    struct listint_t *slow = *head, *fast = *head, *secondHalf, *prevSlow = *head;
    int isPalindrome = 1;

    if (*head != NULL && (*head)->next != NULL) {
        /* Move fast pointer to the middle, slow will be at the middle when fast reaches the end */
        while (fast != NULL && fast->next != NULL) {
            fast = fast->next->next;

            /* Keep track of the previous of slow for linked list with odd elements */
            prevSlow = slow;
            slow = slow->next;
        }

        /* If the number of elements is odd, move slow to the next element */
        if (fast != NULL) {
            slow = slow->next;
        }

        /* Reverse the second half of the list */
        secondHalf = reverseList(slow);

        /* Compare the first and second halves */
        while (secondHalf != NULL) {
            if ((*head)->data != secondHalf->data) {
                isPalindrome = 0;
                break;
            }

            *head = (*head)->next;
            secondHalf = secondHalf->next;
        }

        /* Restore the reversed second half */
        reverseList(prevSlow->next);
    }

    return isPalindrome;
}

/* Function to print the linked list */
void printList(struct listint_t* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

/* Function to create a new node */
struct listint_t* newNode(int key) {
    struct listint_t* temp = (struct listint_t*)malloc(sizeof(struct listint_t));
    temp->data = key;
    temp->next = NULL;
    return temp;
}

int main() {
    struct listint_t* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(3);
    head->next->next->next->next = newNode(2);
    head->next->next->next->next->next = newNode(1);

    printf("Linked List: ");
    printList(head);

    if (is_palindrome(&head)) {
        printf("The linked list is a palindrome.\n");
    } else {
        printf("The linked list is not a palindrome.\n");
    }

    return 0;
}
