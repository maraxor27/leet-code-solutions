class Solution:
    def isPalindrome(self, x: int) -> bool:
        if x < 0:
            return False
        x_s = str(x)

        hl = int(len(x_s) / 2)

        for i in range(0, hl):
            if x_s[i] != x_s[-1-i]:
                return False

        return True
