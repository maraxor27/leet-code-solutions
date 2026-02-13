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
    int carry = 0;
    struct ListNode* solution = malloc(sizeof(struct ListNode));
    struct ListNode* hand = solution;
    while(1) {
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
            hand->next = malloc(sizeof(struct ListNode));
            hand = hand->next;
        } else {
            hand->next = NULL;
            break;
        }  
    }
    return solution;
}