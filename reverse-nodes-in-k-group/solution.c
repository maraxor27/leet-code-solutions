/**
 * Definition for singly-linked list. */
struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode* advance(struct ListNode* hand , int k) {
    for (int i = 0; i < k; i++) {
        hand = hand->next;
        if (!hand) {
            return 0;
        }
    }
    return hand;
}

void swap(struct ListNode* hand, int k) {
    if (k != 0) {
        swap(hand->next, k - 1);
        hand->next->next = hand;
        printf("%i -> %i\n", hand->next->val, hand->val);
    }
}

// 1 <= k <= n <= 5000
// 0 <= Node.val <= 1000
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode root;
    root.next = head;
    root.val = -1;

    struct ListNode* prev = &root;
    while (1) {
        printf("--starting from: %i\n", head->val);
        struct ListNode* end = advance(head, k-1);
        if (!end) {
            prev->next = head;
            printf("%i -> %i\n", prev->val, head->val);
            printf("end 0\n");
            break;
        } 
        printf("end: %i\n", end->val);
        struct ListNode* end_next = end->next;
        swap(head, k - 1);
        prev->next = end;
        printf("%i -> %i\n", prev->val, end->val);
        if (!end_next) {
            head->next = 0;
            printf("end 1\n");
            break;
        }
        prev = head;
        head = end_next;
    }
    head = root.next;
    printf("r -> %i\n", root.next->val);

    printf("[");
    do {
        printf("%i,", head->val);
    } while (head = head->next);
    printf("]\n");
    
    printf("Done!\n");
    return root.next;
}