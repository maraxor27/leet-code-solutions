# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        if head is None:
            return None

        list_length = 0
        hand = head
        while hand is not None:
            hand = hand.next
            list_length += 1

        print("Length of the linked list:", list_length)

        if n == list_length:
            return head.next

        

        hand = head
        for _ in range(0, list_length - n - 1):
            hand = hand.next
        
        hand.next = hand.next.next

        return head
