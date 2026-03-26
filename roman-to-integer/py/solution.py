class Solution:
    roman_lookup_dict = {
        "I": 1,
        "V": 5,
        "X": 10,
        "L": 50,
        "C": 100,
        "D": 500,
        "M": 1000
    }
    def romanToInt(self, s: str) -> int:
        result = 0
        prev = 1000
        for c in s:
            v = self.roman_lookup_dict[c]
            
            if v <= prev:
                result += v
            else:
                result = result - prev + (v - prev)
            
            prev = v

        return result
        
