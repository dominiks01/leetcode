#include <complex.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

void freeListFromEnd(struct ListNode* head) {
    if (head == NULL) {
        return;
    }
    freeListFromEnd(head->next);
    free(head);
}

struct ListNode* swapPairs(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct ListNode dummy = {0, head};
    struct ListNode* prev = &dummy;
    struct ListNode* current = head;

    while (current != NULL && current->next != NULL) {
        struct ListNode* nextPair = current->next->next;
        struct ListNode* second = current->next;

        second->next = current;
        current->next = nextPair;
        prev->next = second;

        prev = prev->next;
        current = current->next;
    }

    return dummy.next;
}

int main() {

    int arr[] = {1, 2, 3, 4};
    int arr_size = 4;
    struct ListNode* list = malloc(sizeof(struct ListNode));

    list->val = arr[0];
    list->next = NULL;

    struct ListNode* head = list;

    for (int i = 1; i < arr_size; i++) {
        struct ListNode* next = malloc(sizeof(struct ListNode));
        next->next = NULL;
        next->val = arr[i];

        list->next = next;
        list = list->next;
    }

    struct ListNode* result = swapPairs(head);

    while (result != NULL) {
        printf("%i ", result->val);
        result = result->next;
    }

    freeListFromEnd(list);

    return 0;
}