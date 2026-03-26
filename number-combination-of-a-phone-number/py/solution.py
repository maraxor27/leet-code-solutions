class Solution:
    lookup_table = {
        "2": ["a", "b", "c"],
        "3": ["d", "e", "f"],
        "4": ["g", "h", "i"],
        "5": ["j", "k", "l"],
        "6": ["m", "n", "o"],
        "7": ["p", "q", "r", "s"],
        "8": ["t", "u", "v"],
        "9": ["w", "x", "y", "z"]
    }

    def letterCombinations(self, digits: str) -> List[str]:
        results = []
        if len(digits) == 1:
            return self.lookup_table[digits[0]]

        digit = digits[0]
        for letter in self.lookup_table[digit]:
            sub_results = self.letterCombinations(digits[1:])
            results += [letter + sub_result for sub_result in sub_results]
        return results
