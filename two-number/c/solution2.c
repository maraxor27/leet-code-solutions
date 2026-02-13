#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int solution_digits = 1;
    struct ListNode *h1 = l1, *h2 = l2;
    while (h1 || h2) {
        if (h1) h1 = h1->next;
        if (h2) h2 = h2->next;
        solution_digits++;
    }
    printf("solution_digits: %d\n", solution_digits);
    printf("sizeof(struct ListNode): %ld\n", sizeof(struct ListNode));
    struct ListNode* solution = malloc(sizeof(struct ListNode) * solution_digits);
    printf("allocated array for all the nodes @ %p\n", solution);

    int carry = 0;
    struct ListNode* hand = solution;
    while(1) {
        printf("hand @ %p\n", hand);
        int sum = carry;
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }
        if (sum > 9) {
            carry = 1;
            sum = sum % 10;
        } else {
            carry = 0;
        }
        hand->val = sum;
        if (l1 || l2 || carry) {
            hand->next = hand + 1;
            hand += 1;
        } else {
            hand->next = NULL;
            break;
        }  
    }
    printf("done!\n");
    unsigned long long* mem = solution;
    for (int i = 0; i < solution_digits; i++) {
        printf("%p: %016x, %016x\n", mem, mem[0], mem[1]);
        mem += 2;
    }
    return solution;
}