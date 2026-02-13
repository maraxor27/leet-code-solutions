/**
 * Definition for singly-linked list. */
struct ListNode {
    int val;
    struct ListNode *next;
};

int length;
int* makeArray(struct ListNode* head, int index) {
    if (!head) {
        length = index;
        return malloc(sizeof(int) * index);
    } else {
        int* buffer = makeArray(head->next, index + 1);
        buffer[index] = head->val;
        return buffer;
    }
}

// 1 <= k <= n <= 5000
// 0 <= Node.val <= 1000
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if (k == 1) {
        return head;
    }

    int step = k - 1; 
    int* buffer = makeArray(head, 0);
    for (int i = 0; i < (length - step); i += k) {
        int tmp = buffer[i];
        buffer[i] = buffer[i + step];
        buffer[i + step] = tmp;
    }

    struct ListNode* hand = head;
    for (int i = 0; i < length; i++) {
        hand->val = buffer[i];
        hand = hand->next;
    }
    free(buffer);

    return head;
}