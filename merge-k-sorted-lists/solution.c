/**
 * Definition for singly-linked list. */
struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    struct ListNode* head = 0;
    struct ListNode* tail = 0;

    int smallest_index;
    struct ListNode* smallest;

    do {
        smallest_index = -1;
        smallest = 0;

        for (int i = 0; i < listsSize; i++) {
            if (!lists[i]) {
                continue;
            }

            if (!smallest) {
                smallest_index = i;
                smallest = lists[i];
                continue;
            }

            if (lists[i]->val < smallest->val) {
                smallest_index = i;
                smallest = lists[i];
            }
        }
        
        if (smallest_index != -1) {
            lists[smallest_index] = lists[smallest_index]->next; 
            if (!head) {
                head = smallest;
                tail = head;
            } else {
                tail->next = smallest;
                tail = smallest;
            }
        }
    } while (smallest);

    if (tail) {
        tail->next = 0;
    }
    return head;
}